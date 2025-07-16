#include "MediaReader.h"
#include <iostream>

namespace cb
{

MediaReader::MediaReader(const MediaReaderConfig& config)
    : config(config)
    , isInitialized(false)
    , hasAudio(false)
    , hasVideo(false)
    , audioStreamIndex(-1)
    , videoStreamIndex(-1)
    , duration(0.0)
    , currentTime(0.0)
    , isPlaying(false)
    , isPaused(false)
    , hasReachedEnd(false)
{
    // Initialize FFmpeg if not already done
    if (!cb::isFFmpegInitialized())
    {
        cb::initializeFFmpeg();
    }
}

MediaReader::~MediaReader()
{
    close();
}

bool MediaReader::open(const std::string& filename)
{
    // Close any existing media
    close();
    
    // Open format context
    AVFormatContext* formatCtxRaw = nullptr;
    if (avformat_open_input(&formatCtxRaw, filename.c_str(), nullptr, nullptr) < 0)
    {
        if (config.enableLogging)
            std::cerr << "MediaReader: Could not open file: " << filename << std::endl;
        return false;
    }
    
    formatCtx = AVFormatContextPtr(formatCtxRaw);
    
    // Find stream info
    if (avformat_find_stream_info(formatCtx.get(), nullptr) < 0)
    {
        if (config.enableLogging)
            std::cerr << "MediaReader: Could not find stream info" << std::endl;
        formatCtx.reset();
        return false;
    }
    
    // Find streams
    if (!findStreams())
    {
        if (config.enableLogging)
            std::cerr << "MediaReader: No valid streams found" << std::endl;
        formatCtx.reset();
        return false;
    }
    
    // Initialize components
    if (!initializeComponents())
    {
        if (config.enableLogging)
            std::cerr << "MediaReader: Failed to initialize components" << std::endl;
        formatCtx.reset();
        return false;
    }
    
    // Calculate duration
    calculateDuration();
    
    currentFilename = filename;
    isInitialized = true;
    
    if (config.enableLogging)
        std::cout << "MediaReader: Successfully opened " << filename << std::endl;
    
    return true;
}

void MediaReader::close()
{
    // Stop playback
    stop();
    
    // Reset state
    isInitialized = false;
    hasAudio = false;
    hasVideo = false;
    audioStreamIndex = -1;
    videoStreamIndex = -1;
    duration = 0.0;
    currentTime = 0.0;
    isPlaying = false;
    isPaused = false;
    hasReachedEnd = false;
    
    // Clean up components
    audioDecoder.reset();
    videoDecoder.reset();
    audioBuffer.reset();
    videoBuffer.reset();
    audioSource.reset();
    videoComponent.reset();
    
    // Close format context
    formatCtx.reset();
    
    currentFilename.clear();
}

bool MediaReader::findStreams()
{
    if (!formatCtx)
        return false;
    
    audioStreamIndex = av_find_best_stream(formatCtx.get(), AVMEDIA_TYPE_AUDIO, -1, -1, nullptr, 0);
    videoStreamIndex = av_find_best_stream(formatCtx.get(), AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
    
    hasAudio = (audioStreamIndex >= 0);
    hasVideo = (videoStreamIndex >= 0);
    
    return hasAudio || hasVideo;
}

bool MediaReader::initializeComponents()
{
    if (!formatCtx)
        return false;
    
    // Initialize audio components
    if (hasAudio)
    {
        audioBuffer = std::make_shared<AudioBuffer>(config.audioConfig);
        audioDecoder = std::make_unique<AudioDecoder>(audioBuffer, config);
        audioSource = std::make_unique<MediaAudioSource>(audioBuffer, config);
        
        if (!audioDecoder->initialize(formatCtx.get(), audioStreamIndex))
        {
            if (config.enableLogging)
                std::cerr << "MediaReader: Failed to initialize audio decoder" << std::endl;
            hasAudio = false;
            audioDecoder.reset();
            audioSource.reset();
            audioBuffer.reset();
        }
    }
    
    // Initialize video components
    if (hasVideo)
    {
        videoBuffer = std::make_shared<VideoBuffer>(config.videoConfig);
        videoDecoder = std::make_unique<VideoDecoder>(videoBuffer, config);
        videoComponent = std::make_unique<MediaVideoComponent>(videoBuffer, config);
        
        if (!videoDecoder->initialize(formatCtx.get(), videoStreamIndex))
        {
            if (config.enableLogging)
                std::cerr << "MediaReader: Failed to initialize video decoder" << std::endl;
            hasVideo = false;
            videoDecoder.reset();
            videoComponent.reset();
            videoBuffer.reset();
        }
    }
    
    return hasAudio || hasVideo;
}

void MediaReader::calculateDuration()
{
    if (!formatCtx)
    {
        duration = 0.0;
        return;
    }
    
    if (formatCtx->duration != AV_NOPTS_VALUE)
    {
        duration = formatCtx->duration / static_cast<double>(AV_TIME_BASE);
    }
    else
    {
        // Try to estimate from streams
        duration = 0.0;
        for (unsigned int i = 0; i < formatCtx->nb_streams; ++i)
        {
            AVStream* stream = formatCtx->streams[i];
            if (stream->duration != AV_NOPTS_VALUE)
            {
                double streamDuration = stream->duration * av_q2d(stream->time_base);
                duration = std::max(duration, streamDuration);
            }
        }
    }
}

void MediaReader::play()
{
    if (!isInitialized || isPlaying)
        return;
    
    isPlaying = true;
    isPaused = false;
    hasReachedEnd = false;
    
    // Start decoders
    if (audioDecoder)
        audioDecoder->start();
    
    if (videoDecoder)
        videoDecoder->start();
    
    // Update components
    if (audioSource)
        audioSource->setPlaying(true);
    
    if (videoComponent)
        videoComponent->setPlaying(true);
    
    if (config.enableLogging)
        std::cout << "MediaReader: Started playback" << std::endl;
}

void MediaReader::pause()
{
    if (!isInitialized || !isPlaying || isPaused)
        return;
    
    isPaused = true;
    
    // Pause decoders
    if (audioDecoder)
        audioDecoder->pause();
    
    if (videoDecoder)
        videoDecoder->pause();
    
    // Update components
    if (audioSource)
        audioSource->setPlaying(false);
    
    if (videoComponent)
        videoComponent->setPlaying(false);
    
    if (config.enableLogging)
        std::cout << "MediaReader: Paused playback" << std::endl;
}

void MediaReader::resume()
{
    if (!isInitialized || !isPlaying || !isPaused)
        return;
    
    isPaused = false;
    
    // Resume decoders
    if (audioDecoder)
        audioDecoder->resume();
    
    if (videoDecoder)
        videoDecoder->resume();
    
    // Update components
    if (audioSource)
        audioSource->setPlaying(true);
    
    if (videoComponent)
        videoComponent->setPlaying(true);
    
    if (config.enableLogging)
        std::cout << "MediaReader: Resumed playback" << std::endl;
}

void MediaReader::stop()
{
    if (!isInitialized)
        return;
    
    isPlaying = false;
    isPaused = false;
    hasReachedEnd = false;
    
    // Stop decoders
    if (audioDecoder)
        audioDecoder->stop();
    
    if (videoDecoder)
        videoDecoder->stop();
    
    // Update components
    if (audioSource)
        audioSource->setPlaying(false);
    
    if (videoComponent)
    {
        videoComponent->setPlaying(false);
        videoComponent->clearFrame();
    }
    
    // Reset time
    currentTime = 0.0;
    
    if (config.enableLogging)
        std::cout << "MediaReader: Stopped playback" << std::endl;
}

void MediaReader::seek(double timeInSeconds)
{
    if (!isInitialized)
        return;
    
    // Clamp time to valid range
    timeInSeconds = std::max(0.0, std::min(timeInSeconds, duration));
    
    // Seek decoders
    if (audioDecoder)
        audioDecoder->seek(timeInSeconds);
    
    if (videoDecoder)
        videoDecoder->seek(timeInSeconds);
    
    // Update current time
    currentTime = timeInSeconds;
    hasReachedEnd = false;
    
    if (config.enableLogging)
        std::cout << "MediaReader: Seeked to " << timeInSeconds << "s" << std::endl;
}

double MediaReader::getCurrentTime() const
{
    if (!isInitialized)
        return 0.0;
    
    // Get time from most accurate source
    if (audioDecoder)
        return audioDecoder->getCurrentTime();
    else if (videoDecoder)
        return videoDecoder->getCurrentTime();
    
    return currentTime;
}

double MediaReader::getDuration() const
{
    return duration;
}

bool MediaReader::getIsInitialized() const
{
    return isInitialized;
}

bool MediaReader::getIsPlaying() const
{
    return isPlaying && !isPaused;
}

bool MediaReader::getIsPaused() const
{
    return isPaused;
}

bool MediaReader::getHasAudio() const
{
    return hasAudio;
}

bool MediaReader::getHasVideo() const
{
    return hasVideo;
}

bool MediaReader::hasReachedEndOfFile() const
{
    if (!isInitialized)
        return false;
    
    // Check if all active decoders have finished
    bool audioFinished = !hasAudio || (audioDecoder && audioDecoder->isFinished());
    bool videoFinished = !hasVideo || (videoDecoder && videoDecoder->isFinished());
    
    return audioFinished && videoFinished;
}

MediaAudioSource* MediaReader::getAudioSource() const
{
    return audioSource.get();
}

MediaVideoComponent* MediaReader::getVideoComponent() const
{
    return videoComponent.get();
}

MediaReaderStats MediaReader::getStats() const
{
    MediaReaderStats stats;
    
    if (!isInitialized)
        return stats;
    
    stats.filename = currentFilename;
    stats.hasAudio = hasAudio;
    stats.hasVideo = hasVideo;
    stats.duration = duration;
    stats.currentTime = getCurrentTime();
    stats.isPlaying = getIsPlaying();
    stats.isPaused = getIsPaused();
    
    // Audio stats
    if (audioBuffer)
    {
        auto audioStats = audioBuffer->getStats();
        stats.audioStats.bufferSize = audioStats.bufferSize;
        stats.audioStats.currentSize = audioStats.currentSize;
        stats.audioStats.totalPushed = audioStats.totalFramesPushed;
        stats.audioStats.totalPopped = audioStats.totalFramesPopped;
        stats.audioStats.underruns = audioStats.underruns;
        stats.audioStats.overruns = audioStats.overruns;
    }
    
    // Video stats
    if (videoBuffer)
    {
        stats.videoStats.queueSize = videoBuffer->getQueueSize();
        stats.videoStats.maxQueueSize = config.videoConfig.maxQueueSize;
        stats.videoStats.droppedFrames = videoBuffer->getDroppedFrameCount();
    }
    
    return stats;
}

std::vector<MediaStreamInfo> MediaReader::getStreamInfo() const
{
    std::vector<MediaStreamInfo> streams;
    
    if (!formatCtx)
        return streams;
    
    for (unsigned int i = 0; i < formatCtx->nb_streams; ++i)
    {
        AVStream* stream = formatCtx->streams[i];
        MediaStreamInfo info;
        
        info.index = i;
        info.type = static_cast<MediaType>(stream->codecpar->codec_type);
        info.codecName = avcodec_get_name(stream->codecpar->codec_id);
        
        if (stream->duration != AV_NOPTS_VALUE)
            info.duration = stream->duration * av_q2d(stream->time_base);
        else
            info.duration = duration;
        
        if (info.type == MediaType::Audio)
        {
            info.audioInfo.sampleRate = stream->codecpar->sample_rate;
            info.audioInfo.channels = stream->codecpar->ch_layout.nb_channels;
            info.audioInfo.bitrate = stream->codecpar->bit_rate;
        }
        else if (info.type == MediaType::Video)
        {
            info.videoInfo.width = stream->codecpar->width;
            info.videoInfo.height = stream->codecpar->height;
            info.videoInfo.bitrate = stream->codecpar->bit_rate;
            
            if (stream->avg_frame_rate.num > 0 && stream->avg_frame_rate.den > 0)
                info.videoInfo.frameRate = av_q2d(stream->avg_frame_rate);
            else
                info.videoInfo.frameRate = 0.0;
        }
        
        streams.push_back(info);
    }
    
    return streams;
}

void MediaReader::setLooping(bool shouldLoop)
{
    config.enableLooping = shouldLoop;
}

bool MediaReader::getLooping() const
{
    return config.enableLooping;
}

void MediaReader::setVolume(float volume)
{
    if (audioSource)
        audioSource->setVolume(volume);
}

float MediaReader::getVolume() const
{
    if (audioSource)
        return audioSource->getVolume();
    
    return 1.0f;
}

std::string MediaReader::getCurrentFilename() const
{
    return currentFilename;
}

// Factory functions
std::unique_ptr<MediaReader> createMediaReader(const MediaReaderConfig& config)
{
    return std::make_unique<MediaReader>(config);
}

std::unique_ptr<MediaReader> createAudioOnlyReader()
{
    auto config = MediaReaderConfig::createAudioOnlyConfig();
    return createMediaReader(config);
}

std::unique_ptr<MediaReader> createVideoOnlyReader()
{
    auto config = MediaReaderConfig::createVideoOnlyConfig();
    return createMediaReader(config);
}

std::unique_ptr<MediaReader> createHighPerformanceReader()
{
    auto config = MediaReaderConfig::createHighPerformanceConfig();
    return createMediaReader(config);
}

std::unique_ptr<MediaReader> createLowLatencyReader()
{
    auto config = MediaReaderConfig::createLowLatencyConfig();
    return createMediaReader(config);
}

} // namespace cb 