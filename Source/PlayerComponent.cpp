#include "PlayerComponent.h"

PlayerComponent::PlayerComponent()
{
    videoPlaceholder_.setJustificationType(juce::Justification::centred);
    videoPlaceholder_.setFont(juce::FontOptions(16.0f));
    videoPlaceholder_.setColour(juce::Label::backgroundColourId, juce::Colours::black);
    videoPlaceholder_.setColour(juce::Label::textColourId, juce::Colours::white);
    addAndMakeVisible(videoPlaceholder_);
    
    config_.enableHardwareDecoding = true;
    config_.enableDebugLogging = true;
    config_.audioBufferSizeMs = 2000;  // Increase buffer size significantly
    config_.targetSampleRate = 44100;  // Match audio device sample rate
    config_.targetChannels = 2;        // Match audio device channels
    
    mediaReader_ = std::make_unique<cb_ffmpeg::MediaReader>(config_);
    mediaReader_->setCallback(this);

    startTimerHz(30);
}

PlayerComponent::~PlayerComponent()
{
    stopTimer();
    mediaReader_->setCallback(nullptr);
    mediaReader_.reset();
}

void PlayerComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void PlayerComponent::resized()
{
    if (videoComponent_)
    {
        videoComponent_->setBounds(getLocalBounds());
        videoPlaceholder_.setVisible(false);
    }
    else
    {
        videoPlaceholder_.setBounds(getLocalBounds());
        videoPlaceholder_.setVisible(true);
    }
}

void PlayerComponent::audioDeviceAboutToStart(juce::AudioIODevice* device)
{
    // Prepare audio processing
    if (device)
    {
        sampleRate_ = device->getCurrentSampleRate();
        bufferSize_ = device->getCurrentBufferSizeSamples();
        
        juce::Logger::writeToLog("PlayerComponent: Audio device starting - Sample rate: " + 
                                juce::String(sampleRate_) + " Hz, Buffer size: " + 
                                juce::String(bufferSize_) + " samples");
        
        // Prepare audio source if we have one
        prepareAudioSource();
    }
}

void PlayerComponent::audioDeviceStopped()
{
    // Clean up audio processing
    releaseAudioSource();
}

void PlayerComponent::audioDeviceIOCallbackWithContext(const float* const* inputChannelData,
                                                       int numInputChannels,
                                                       float* const* outputChannelData,
                                                       int numOutputChannels,
                                                       int numSamples,
                                                       const juce::AudioIODeviceCallbackContext& context)
{
    // Clear output buffers first
    for (int channel = 0; channel < numOutputChannels; ++channel)
    {
        if (outputChannelData[channel])
            juce::FloatVectorOperations::clear(outputChannelData[channel], numSamples);
    }
    
    // Fill with audio data from media reader if playing and audio source is available
    juce::Logger::writeToLog("PlayerComponent: Audio callback - mediaReader_: " + juce::String(mediaReader_ ? "yes" : "no") +
                            ", isPlaying_: " + juce::String(isPlaying_ ? "yes" : "no") +
                            ", currentAudioSource_: " + juce::String(currentAudioSource_ ? "yes" : "no") +
                            ", audioSourcePrepared_: " + juce::String(audioSourcePrepared_ ? "yes" : "no"));
    
    if (mediaReader_ && isPlaying_ && currentAudioSource_ && audioSourcePrepared_)
    {
        juce::Logger::writeToLog("PlayerComponent: Audio callback requesting " + juce::String(numSamples) + 
                                " samples from audio source");
        
        juce::AudioSourceChannelInfo channelInfo;
        
        // Create a temporary buffer for the audio source
        juce::AudioBuffer<float> tempBuffer(numOutputChannels, numSamples);
        tempBuffer.clear();
        
        channelInfo.buffer = &tempBuffer;
        channelInfo.startSample = 0;
        channelInfo.numSamples = numSamples;
        
        // Get audio data from the MediaReader's audio source
        currentAudioSource_->getNextAudioBlock(channelInfo);
        
        // Copy to output buffers
        for (int channel = 0; channel < numOutputChannels; ++channel)
        {
            if (outputChannelData[channel] && channel < tempBuffer.getNumChannels())
            {
                juce::FloatVectorOperations::copy(outputChannelData[channel], 
                                                 tempBuffer.getReadPointer(channel), 
                                                 numSamples);
            }
        }
    }
}

bool PlayerComponent::loadMediaFile(const juce::File& file)
{
    resetPlayerState();
    
    bool success = mediaReader_->loadFile(file);
    if (success)
    {
        // The onMediaLoaded callback will be called which will set the final state
        // But we can set basic state here too for immediate UI feedback
        isMediaLoaded_ = true;
    }
    
    return success;
}

void PlayerComponent::togglePlayPause()
{
    juce::Logger::writeToLog("PlayerComponent::togglePlayPause called");
    
    if (!isMediaLoaded_) {
        juce::Logger::writeToLog("No media loaded, cannot toggle playback");
        return;
    }
    
    juce::Logger::writeToLog("Media is loaded, current playing state: " + juce::String(isPlaying_ ? "true" : "false"));
    
    if (isPlaying_)
    {
        juce::Logger::writeToLog("Calling mediaReader_->pause()");
        mediaReader_->pause();
    }
    else
    {
        juce::Logger::writeToLog("Calling mediaReader_->play()");
        mediaReader_->play();
    }
}

void PlayerComponent::stopPlayback()
{
    if (mediaReader_)
    {
        mediaReader_->stop();
    }
}

void PlayerComponent::seek(double timeInSeconds)
{
    juce::Logger::writeToLog("PlayerComponent::seek() called - Target: " + juce::String(timeInSeconds) + " seconds");
    
    if (mediaReader_ && isMediaLoaded_)
    {
        mediaReader_->seek(timeInSeconds);
        currentTime_ = timeInSeconds; // Update local cache immediately for UI responsiveness
        juce::Logger::writeToLog("PlayerComponent: Seek request forwarded to MediaReader");
    }
    else
    {
        juce::Logger::writeToLog("PlayerComponent: Cannot seek - no media loaded or no MediaReader");
    }
}

double PlayerComponent::getCurrentTime() const
{
    return currentTime_;
}

double PlayerComponent::getDuration() const
{
    return duration_;
}

bool PlayerComponent::isPlaying() const
{
    return isPlaying_;
}

bool PlayerComponent::isMediaLoaded() const
{
    return isMediaLoaded_;
}

void PlayerComponent::timerCallback()
{
    if (isMediaLoaded_ && isPlaying_)
    {
        currentTime_ = mediaReader_->getCurrentPosition();
    }
}

void PlayerComponent::onMediaLoaded(const cb_ffmpeg::MediaInfo& info)
{
    juce::Logger::writeToLog("PlayerComponent::onMediaLoaded called - Duration: " + juce::String(info.duration) + 
                            ", Type: " + juce::String(info.hasAudio() ? "Audio " : "") + 
                            juce::String(info.hasVideo() ? "Video" : ""));
    
    // Log audio stream info if available
    if (info.hasAudio())
    {
        const auto* audioStream = info.getAudioStream();
        if (audioStream)
        {
            juce::Logger::writeToLog("Audio stream - Sample rate: " + juce::String(audioStream->sampleRate) + 
                                    " Hz, Channels: " + juce::String(audioStream->channels) +
                                    ", Format: " + audioStream->codec);
        }
    }
    
    currentMediaInfo_ = info;
    duration_ = info.duration;
    isMediaLoaded_ = true;
    
    // Clean up any previous components
    if (audioInfoComponent_)
    {
        removeChildComponent(audioInfoComponent_.get());
        audioInfoComponent_.reset();
    }
    
    if (videoComponent_ && videoComponent_ != audioInfoComponent_.get())
    {
        removeChildComponent(videoComponent_);
        videoComponent_ = nullptr;
    }
    
    // Get audio source from MediaReader if media has audio
    if (info.hasAudio() && mediaReader_)
    {
        currentAudioSource_ = mediaReader_->getAudioSource();
        prepareAudioSource();
    }
    
    // Set up video component if we have video
    if (info.hasVideo())
    {
        videoComponent_ = mediaReader_->getVideoComponent();
        if (videoComponent_)
        {
            addAndMakeVisible(*videoComponent_);
        }
    }
    else if (info.hasAudio())
    {
        // For audio-only files, create a simple info display
        class AudioInfoComponent : public juce::Component
        {
        public:
            AudioInfoComponent(const cb_ffmpeg::MediaInfo& mediaInfo)
                : mediaInfo_(mediaInfo)
            {
                setSize(400, 200);
            }
            
            void paint(juce::Graphics& g) override
            {
                g.fillAll(juce::Colours::darkgrey);
                g.setColour(juce::Colours::white);
                
                auto bounds = getLocalBounds().reduced(20);
                
                g.setFont(juce::FontOptions(24.0f));
                g.drawText("🎵 Audio File", bounds.removeFromTop(40), juce::Justification::centred);
                
                g.setFont(juce::FontOptions(16.0f));
                
                juce::String fileName = mediaInfo_.file.getFileName();
                g.drawText("File: " + fileName, bounds.removeFromTop(25), juce::Justification::left);
                
                if (mediaInfo_.duration > 0)
                {
                    int mins = (int)(mediaInfo_.duration / 60);
                    int secs = (int)mediaInfo_.duration % 60;
                    juce::String durationStr = juce::String::formatted("%d:%02d", mins, secs);
                    g.drawText("Duration: " + durationStr, bounds.removeFromTop(25), juce::Justification::left);
                }
                
                g.drawText("Format: " + mediaInfo_.format, bounds.removeFromTop(25), juce::Justification::left);
                
                bounds.removeFromTop(20);
                g.setFont(juce::FontOptions(14.0f));
                g.setColour(juce::Colours::lightgrey);
                g.drawText("Ready to play", bounds, juce::Justification::centred);
            }
        
        private:
            cb_ffmpeg::MediaInfo mediaInfo_;
        };
        
        audioInfoComponent_ = std::make_unique<AudioInfoComponent>(info);
        videoComponent_ = audioInfoComponent_.get();
        addAndMakeVisible(*audioInfoComponent_);
    }
    
    resized();
}

void PlayerComponent::onPlaybackStarted()
{
    juce::Logger::writeToLog("PlayerComponent::onPlaybackStarted() called - setting isPlaying_ = true");
    isPlaying_ = true;
}

void PlayerComponent::onPlaybackStopped()
{
    isPlaying_ = false;
    currentTime_ = 0.0;
}

void PlayerComponent::onPlaybackPaused()
{
    isPlaying_ = false;
}

void PlayerComponent::onEndOfMedia()
{
    juce::Logger::writeToLog("PlayerComponent::onEndOfMedia() called");
    currentTime_ = duration_; // Set to end
}

void PlayerComponent::onSeekStarted(double targetTime)
{
    juce::Logger::writeToLog("PlayerComponent::onSeekStarted() called - Target: " + juce::String(targetTime) + "s");
    // Could show seeking indicator in UI if needed
}

void PlayerComponent::onSeekCompleted(double actualTime)
{
    juce::Logger::writeToLog("PlayerComponent::onSeekCompleted() called - Actual: " + juce::String(actualTime) + "s");
    currentTime_ = actualTime; // Update position to actual seek result
}

void PlayerComponent::onError(const juce::String& errorMessage)
{
    juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::WarningIcon, "Player Error", errorMessage);
    resetPlayerState();
}

void PlayerComponent::resetPlayerState()
{
    isPlaying_ = false;
    isMediaLoaded_ = false;
    currentTime_ = 0.0;
    duration_ = 0.0;
    
    // Release audio source
    releaseAudioSource();
    currentAudioSource_ = nullptr;
    
    if (audioInfoComponent_)
    {
        removeChildComponent(audioInfoComponent_.get());
        audioInfoComponent_.reset();
    }
    
    if (videoComponent_ && videoComponent_ != audioInfoComponent_.get())
    {
        removeChildComponent(videoComponent_);
        videoComponent_ = nullptr;
    }
    
    resized();
}

void PlayerComponent::prepareAudioSource()
{
    if (currentAudioSource_ && !audioSourcePrepared_ && sampleRate_ > 0 && bufferSize_ > 0)
    {
        currentAudioSource_->prepareToPlay(bufferSize_, sampleRate_);
        audioSourcePrepared_ = true;
        
        // Apply current volume and mute settings
        if (auto* mediaAudioSource = dynamic_cast<cb_ffmpeg::MediaAudioSource*>(currentAudioSource_))
        {
            double gainValue = isMuted_ ? 0.0 : currentVolume_;
            mediaAudioSource->setGain(gainValue);
        }
        
        juce::Logger::writeToLog("PlayerComponent: Audio source prepared");
    }
}

void PlayerComponent::releaseAudioSource()
{
    if (currentAudioSource_ && audioSourcePrepared_)
    {
        currentAudioSource_->releaseResources();
        audioSourcePrepared_ = false;
        juce::Logger::writeToLog("PlayerComponent: Audio source released");
    }
}

void PlayerComponent::setVolume(double volume)
{
    currentVolume_ = juce::jlimit(0.0, 1.0, volume);
    
    // Apply to audio source if available
    if (currentAudioSource_)
    {
        // Try to cast to MediaAudioSource to access gain control
        if (auto* mediaAudioSource = dynamic_cast<cb_ffmpeg::MediaAudioSource*>(currentAudioSource_))
        {
            double gainValue = isMuted_ ? 0.0 : currentVolume_;
            mediaAudioSource->setGain(gainValue);
        }
    }
}

double PlayerComponent::getVolume() const
{
    return currentVolume_;
}

void PlayerComponent::setMuted(bool muted)
{
    isMuted_ = muted;
    
    // Apply to audio source if available
    if (currentAudioSource_)
    {
        // Try to cast to MediaAudioSource to access mute control
        if (auto* mediaAudioSource = dynamic_cast<cb_ffmpeg::MediaAudioSource*>(currentAudioSource_))
        {
            double gainValue = isMuted_ ? 0.0 : currentVolume_;
            mediaAudioSource->setGain(gainValue);
        }
    }
}

bool PlayerComponent::isMuted() const
{
    return isMuted_;
} 