#include "MediaReader.h"
#include "AudioDecoder.h"
#include "VideoDecoder.h"
#include "MediaAudioSource.h"

namespace cb_ffmpeg
{

MediaReader::MediaReader(const MediaReaderConfig& config)
    : config_(config)
{
}

MediaReader::~MediaReader()
{
    unload();
}

bool MediaReader::loadFile(const juce::File& file)
{
    if (isLoaded())
    {
        unload();
    }

    // Check if FFmpeg is initialized
    if (!isFFmpegInitialized())
    {
        setError("FFmpeg not initialized. Call cb_ffmpeg::initializeModule() first.");
        return false;
    }

    // Basic file validation
    if (!file.exists())
    {
        setError("File does not exist: " + file.getFullPathName());
        return false;
    }

    if (!file.existsAsFile())
    {
        setError("Path is not a file: " + file.getFullPathName());
        return false;
    }

    if (file.getSize() == 0)
    {
        setError("File is empty: " + file.getFullPathName());
        return false;
    }

    // Log the file being opened for debugging
    juce::Logger::writeToLog("Attempting to load file: " + file.getFullPathName());

    // Open the media file
    int ret = avformat_open_input(&formatContext_, file.getFullPathName().toRawUTF8(), nullptr, nullptr);
    if (ret < 0)
    {
        char errbuf[128];
        av_strerror(ret, errbuf, sizeof(errbuf));
        juce::Logger::writeToLog("FFmpeg error opening file: " + juce::String(errbuf));
        setError("Could not open media file: " + juce::String(errbuf));
        return false;
    }

    // Find stream information
    ret = avformat_find_stream_info(formatContext_, nullptr);
    if (ret < 0)
    {
        char errbuf[128];
        av_strerror(ret, errbuf, sizeof(errbuf));
        juce::Logger::writeToLog("FFmpeg error finding stream info: " + juce::String(errbuf));
        setError("Could not find stream information: " + juce::String(errbuf));
        avformat_close_input(&formatContext_);
        return false;
    }

    // Populate MediaInfo
    mediaInfo_.file = file;
    mediaInfo_.duration = (double)formatContext_->duration / AV_TIME_BASE;
    mediaInfo_.format = formatContext_->iformat->name;
    mediaInfo_.type = MediaType::Unknown; // Will be determined below

    // Log file info
    juce::Logger::writeToLog("File loaded successfully. Format: " + mediaInfo_.format + 
                            ", Duration: " + juce::String(mediaInfo_.duration) + " seconds");

    for (unsigned int i = 0; i < formatContext_->nb_streams; ++i)
    {
        AVStream* stream = formatContext_->streams[i];
        if (stream->codecpar->codec_type == AVMEDIA_TYPE_AUDIO && mediaInfo_.audioStreamIndex == -1)
        {
            mediaInfo_.audioStreamIndex = i;
            juce::Logger::writeToLog("Found audio stream at index " + juce::String(i));
        }
        else if (stream->codecpar->codec_type == AVMEDIA_TYPE_VIDEO && mediaInfo_.videoStreamIndex == -1)
        {
            mediaInfo_.videoStreamIndex = i;
            juce::Logger::writeToLog("Found video stream at index " + juce::String(i));
        }
    }

    // Determine media type
    if (mediaInfo_.audioStreamIndex >= 0 && mediaInfo_.videoStreamIndex >= 0)
        mediaInfo_.type = MediaType::AudioVideo;
    else if (mediaInfo_.audioStreamIndex >= 0)
        mediaInfo_.type = MediaType::AudioOnly;
    else if (mediaInfo_.videoStreamIndex >= 0)
        mediaInfo_.type = MediaType::VideoOnly;

    juce::Logger::writeToLog("Media type determined: " + 
                            juce::String(mediaInfo_.hasAudio() ? "Audio " : "") +
                            juce::String(mediaInfo_.hasVideo() ? "Video" : ""));

    // Set up audio decoding pipeline if we have audio
    if (mediaInfo_.hasAudio())
    {
        juce::Logger::writeToLog("MediaReader: Setting up audio decoding pipeline");
        try {
            // Create audio buffer
            audioBuffer_ = std::make_unique<AudioBuffer>(config_.audioBufferSizeMs);
            juce::Logger::writeToLog("MediaReader: AudioBuffer created");
            
            // Create audio decoder
            audioDecoder_ = std::make_unique<AudioDecoder>(*audioBuffer_, config_);
            juce::Logger::writeToLog("MediaReader: AudioDecoder created");
            
            // Initialize decoder with the format context and audio stream
            if (audioDecoder_->initialize(formatContext_, mediaInfo_.audioStreamIndex))
            {
                juce::Logger::writeToLog("MediaReader: AudioDecoder initialized successfully");
                
                // Create media audio source
                mediaAudioSource_ = std::make_unique<MediaAudioSource>(*audioBuffer_, mediaInfo_);
                audioSource_ = mediaAudioSource_.get();
                
                juce::Logger::writeToLog("MediaReader: Audio decoding pipeline created successfully");
            }
            else
            {
                juce::Logger::writeToLog("MediaReader: Failed to initialize audio decoder");
                audioDecoder_.reset();
                audioBuffer_.reset();
            }
        }
        catch (const std::exception& e)
        {
            juce::Logger::writeToLog("MediaReader: Exception creating audio pipeline: " + juce::String(e.what()));
            audioDecoder_.reset();
            audioBuffer_.reset();
            audioSource_ = nullptr;
        }
    }
    else
    {
        juce::Logger::writeToLog("MediaReader: No audio stream found in media file");
    }

    if (callback_)
    {
        callback_->onMediaLoaded(mediaInfo_);
    }

    return true;
}

bool MediaReader::loadFromMemory(const void* data, size_t size, const juce::String& formatHint)
{
    return false;
}

void MediaReader::unload()
{
    // Stop audio decoding if running
    if (audioDecoder_)
    {
        audioDecoder_->stop();
        audioDecoder_.reset();
    }
    
    // Clean up audio components
    audioSource_ = nullptr;
    mediaAudioSource_.reset();
    audioBuffer_.reset();
    
    if (formatContext_)
    {
        avformat_close_input(&formatContext_);
        formatContext_ = nullptr;
    }
    mediaInfo_ = {};
}

void MediaReader::play()
{
    juce::Logger::writeToLog("MediaReader::play() called");
    
    if (audioDecoder_ && audioDecoder_->getState() != DecoderState::Destroyed)
    {
        juce::Logger::writeToLog("MediaReader: AudioDecoder exists, current state: " + juce::String(static_cast<int>(audioDecoder_->getState())));
        
        if (audioDecoder_->getState() == DecoderState::Uninitialized || 
            audioDecoder_->getState() == DecoderState::Ready ||
            audioDecoder_->getState() == DecoderState::EndOfStream)
        {
            juce::Logger::writeToLog("MediaReader: Starting audio decoder");
            if (audioDecoder_->start())
            {
                setPlaybackState(PlaybackState::Playing);
                if (callback_) callback_->onPlaybackStarted();
                juce::Logger::writeToLog("MediaReader: Audio playback started successfully");
            }
            else
            {
                juce::Logger::writeToLog("MediaReader: Failed to start audio decoder");
            }
        }
        else if (getPlaybackState() == PlaybackState::Paused)
        {
            setPlaybackState(PlaybackState::Playing);
            if (callback_) callback_->onPlaybackStarted();
            juce::Logger::writeToLog("MediaReader: Audio playback resumed");
        }
        else
        {
            juce::Logger::writeToLog("MediaReader: AudioDecoder in unexpected state: " + juce::String(static_cast<int>(audioDecoder_->getState())));
        }
    }
    else
    {
        juce::Logger::writeToLog("MediaReader: No AudioDecoder available for playback");
    }
}

void MediaReader::pause()
{
    juce::Logger::writeToLog("MediaReader::pause() called");
    
    if (audioDecoder_ && getPlaybackState() == PlaybackState::Playing)
    {
        setPlaybackState(PlaybackState::Paused);
        if (callback_) callback_->onPlaybackPaused();
        juce::Logger::writeToLog("MediaReader: Audio playback paused");
    }
    else
    {
        juce::Logger::writeToLog("MediaReader: Cannot pause - no decoder or not playing");
    }
}

void MediaReader::stop()
{
    if (audioDecoder_)
    {
        audioDecoder_->stop();
        setPlaybackState(PlaybackState::Stopped);
        if (callback_) callback_->onPlaybackStopped();
        juce::Logger::writeToLog("Audio playback stopped");
    }
}

void MediaReader::seek(double timeInSeconds, SeekMode mode)
{
}

void MediaReader::setLooping(bool shouldLoop)
{
}

double MediaReader::getCurrentPosition() const
{
    if (audioDecoder_)
    {
        return audioDecoder_->getCurrentTimestamp();
    }
    return 0.0;
}

double MediaReader::getProgress() const
{
    return 0.0;
}

void MediaReader::setPlaybackRate(double rate)
{
}

double MediaReader::getPlaybackRate() const
{
    return 1.0;
}

juce::AudioSource* MediaReader::getAudioSource()
{
    // Return the real audio source if we have one
    if (audioSource_)
    {
        return audioSource_;
    }
    
    // Return nullptr if no audio or audio pipeline not set up
    return nullptr;
}

juce::Component* MediaReader::getVideoComponent()
{
    // Create a basic video component if we have video and one doesn't exist yet
    if (mediaInfo_.hasVideo() && !videoComponent_)
    {
        // For now, create a simple placeholder component
        // This prevents null pointer errors in the UI
        class PlaceholderVideoComponent : public juce::Component
        {
        public:
            PlaceholderVideoComponent()
            {
                setSize(640, 480);
            }
            
            void paint(juce::Graphics& g) override
            {
                g.fillAll(juce::Colours::black);
                g.setColour(juce::Colours::white);
                g.setFont(juce::FontOptions(20.0f));
                g.drawText("Video Placeholder", getLocalBounds(), juce::Justification::centred);
            }
        };
        
        static PlaceholderVideoComponent placeholderComponent;
        videoComponent_ = &placeholderComponent;
    }
    
    return videoComponent_;
}

juce::Image MediaReader::getCurrentImage()
{
    return juce::Image();
}

void MediaReader::setConfig(const MediaReaderConfig& config)
{
}

void MediaReader::setCallback(MediaReaderCallback* callback)
{
    callback_ = callback;
}

void MediaReader::setError(const juce::String& error)
{
    std::lock_guard<std::mutex> lock(errorMutex_);
    lastError_ = error;
}

void MediaReader::setPlaybackState(PlaybackState newState)
{
    playbackState_.store(newState);
}

} 