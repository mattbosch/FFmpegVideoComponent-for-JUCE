#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Initialize the cb_ffmpeg module
    if (!cb_ffmpeg::initializeModule()) {
        DBG("Failed to initialize cb_ffmpeg module");
        jassertfalse;
    }
    
    // Create MediaReader with high-quality configuration
    config_ = cb_ffmpeg::MediaReaderConfig::createHighQualityConfig();
    config_.audioBufferSizeMs = 500;  // 500ms audio buffer
    config_.enableHardwareDecoding = true;
    config_.enableDebugLogging = true;
    
    mediaReader_ = std::make_unique<cb_ffmpeg::MediaReader>(config_);
    
    setupUI();
    
    // Enable keyboard focus for file drag-and-drop
    setWantsKeyboardFocus(true);
    
    // Start UI update timer
    startTimerHz(30); // 30 FPS UI updates
    
    setSize(1000, 700);
}

MainComponent::~MainComponent()
{
    stopTimer();
    
    // Stop playback and cleanup
    if (mediaReader_) {
        mediaReader_->stop();
        mediaReader_.reset();
    }
    
    // Shutdown the module
    cb_ffmpeg::shutdownModule();
}

//==============================================================================
// juce::Component Implementation

void MainComponent::paint(juce::Graphics& g)
{
    // Background gradient
    auto bounds = getLocalBounds();
    juce::ColourGradient gradient = juce::ColourGradient::vertical(
        juce::Colours::darkgrey.darker(0.4f), 0.0f,
        juce::Colours::black, static_cast<float>(getHeight())
    );
    g.setGradientFill(gradient);
    g.fillRect(bounds);
    
    // Title
    g.setColour(juce::Colours::white.withAlpha(0.8f));
    g.setFont(juce::Font(20.0f, juce::Font::bold));
    g.drawText("CB FFmpeg Universal Media Player", 
               bounds.removeFromTop(60), 
               juce::Justification::centred, true);
    
    // Draw video area border if no video component
    if (!videoDisplay_ && isMediaLoaded_) {
        auto videoArea = bounds.reduced(10).removeFromTop(bounds.getHeight() - 150);
        g.setColour(juce::Colours::darkgrey);
        g.drawRect(videoArea, 2);
        
        g.setColour(juce::Colours::white.withAlpha(0.5f));
        g.setFont(16.0f);
        g.drawText("Audio Only", videoArea, juce::Justification::centred, true);
    }
}

void MainComponent::resized()
{
    auto bounds = getLocalBounds().reduced(10);
    
    // Title area
    bounds.removeFromTop(60);
    
    // Video display area (takes most of the space)
    auto videoArea = bounds.removeFromTop(bounds.getHeight() - 120);
    if (videoDisplay_) {
        videoDisplay_->setBounds(videoArea);
    }
    
    bounds.removeFromTop(10); // spacing
    
    // Control panel
    auto controlPanel = bounds.removeFromTop(100);
    
    // Top row: File operations and playback controls
    auto topRow = controlPanel.removeFromTop(35);
    openButton_.setBounds(topRow.removeFromLeft(120));
    topRow.removeFromLeft(10);
    playPauseButton_.setBounds(topRow.removeFromLeft(80));
    topRow.removeFromLeft(5);
    stopButton_.setBounds(topRow.removeFromLeft(60));
    topRow.removeFromLeft(20);
    loopButton_.setBounds(topRow.removeFromLeft(60));
    topRow.removeFromLeft(10);
    muteButton_.setBounds(topRow.removeFromLeft(60));
    
    controlPanel.removeFromTop(10); // spacing
    
    // Position slider and label
    auto positionRow = controlPanel.removeFromTop(25);
    positionSlider_.setBounds(positionRow.removeFromLeft(positionRow.getWidth() - 150));
    positionRow.removeFromLeft(10);
    positionLabel_.setBounds(positionRow);
    
    controlPanel.removeFromTop(5); // spacing
    
    // Volume controls
    auto volumeRow = controlPanel.removeFromTop(25);
    volumeLabel_.setBounds(volumeRow.removeFromLeft(60));
    volumeRow.removeFromLeft(10);
    volumeSlider_.setBounds(volumeRow.removeFromLeft(200));
}

//==============================================================================
// juce::AudioSource Implementation

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    if (mediaReader_ && mediaReader_->hasAudio()) {
        auto* audioSource = mediaReader_->getAudioSource();
        if (audioSource) {
            audioSource->prepareToPlay(samplesPerBlockExpected, sampleRate);
        }
    }
}

void MainComponent::releaseResources()
{
    if (mediaReader_ && mediaReader_->hasAudio()) {
        auto* audioSource = mediaReader_->getAudioSource();
        if (audioSource) {
            audioSource->releaseResources();
        }
    }
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (mediaReader_ && mediaReader_->hasAudio() && isPlaying_) {
        auto* audioSource = mediaReader_->getAudioSource();
        if (audioSource) {
            audioSource->getNextAudioBlock(bufferToFill);
            return;
        }
    }
    
    // No audio or not playing - output silence
    bufferToFill.clearActiveBufferRegion();
}

//==============================================================================
// Timer Callback for UI Updates

void MainComponent::timerCallback()
{
    if (!mediaReader_ || !isMediaLoaded_)
        return;
    
    // Update playback position
    currentTime_ = mediaReader_->getCurrentPosition();
    
    // Update position slider (but not if user is dragging it)
    if (!isDraggingPosition_) {
        positionSlider_.setValue(currentTime_, juce::dontSendNotification);
    }
    
    updatePositionDisplay();
    
    // Check for end of playback (check if current position is close to duration)
    if (isPlaying_ && currentTime_ >= (duration_ - 0.1)) {  // 0.1 second tolerance
        if (loopButton_.getToggleState()) {
            // Loop playback
            mediaReader_->seek(0.0);
        } else {
            // Stop at end
            stopPlayback();
        }
    }
    
    // Update video position if we have video
    if (videoDisplay_ && mediaReader_->hasVideo()) {
        // Video component updates itself based on the buffer
        repaint(); // Trigger video frame updates
    }
}

//==============================================================================
// Button Listener

void MainComponent::buttonClicked(juce::Button* button)
{
    if (button == &openButton_) {
        openMediaFile();
    }
    else if (button == &playPauseButton_) {
        togglePlayPause();
    }
    else if (button == &stopButton_) {
        stopPlayback();
    }
    else if (button == &loopButton_) {
        // Loop state is handled in timerCallback
    }
    else if (button == &muteButton_) {
        bool shouldMute = muteButton_.getToggleState();
        if (mediaReader_ && mediaReader_->hasAudio()) {
            auto* audioSource = dynamic_cast<cb_ffmpeg::MediaAudioSource*>(mediaReader_->getAudioSource());
            if (audioSource) {
                audioSource->setGain(shouldMute ? 0.0 : volumeSlider_.getValue());
            }
        }
    }
}

//==============================================================================
// Slider Listener

void MainComponent::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &positionSlider_) {
        if (isDraggingPosition_ && mediaReader_ && isMediaLoaded_) {
            double newPosition = positionSlider_.getValue();
            mediaReader_->seek(newPosition);
            currentTime_ = newPosition;
            updatePositionDisplay();
        }
    }
    else if (slider == &volumeSlider_) {
        if (mediaReader_ && mediaReader_->hasAudio() && !muteButton_.getToggleState()) {
            auto* audioSource = dynamic_cast<cb_ffmpeg::MediaAudioSource*>(mediaReader_->getAudioSource());
            if (audioSource) {
                audioSource->setGain(volumeSlider_.getValue());
            }
        }
    }
}

//==============================================================================
// Private Helper Methods

void MainComponent::setupUI()
{
    // Configure buttons
    addAndMakeVisible(openButton_);
    addAndMakeVisible(playPauseButton_);
    addAndMakeVisible(stopButton_);
    addAndMakeVisible(loopButton_);
    addAndMakeVisible(muteButton_);
    
    openButton_.addListener(this);
    playPauseButton_.addListener(this);
    stopButton_.addListener(this);
    loopButton_.addListener(this);
    muteButton_.addListener(this);
    
    // Configure sliders
    addAndMakeVisible(positionSlider_);
    addAndMakeVisible(volumeSlider_);
    
    positionSlider_.setRange(0.0, 100.0);
    positionSlider_.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    positionSlider_.addListener(this);
    
    // Add mouse listeners to track dragging
    positionSlider_.onDragStart = [this]() { isDraggingPosition_ = true; };
    positionSlider_.onDragEnd = [this]() { isDraggingPosition_ = false; };
    
    volumeSlider_.setRange(0.0, 1.0);
    volumeSlider_.setValue(0.7);
    volumeSlider_.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    volumeSlider_.addListener(this);
    
    // Configure labels
    addAndMakeVisible(positionLabel_);
    addAndMakeVisible(volumeLabel_);
    
    // Initial button states
    playPauseButton_.setEnabled(false);
    stopButton_.setEnabled(false);
    positionSlider_.setEnabled(false);
}

void MainComponent::openMediaFile()
{
    juce::FileChooser chooser("Select Media File", 
                             juce::File{}, 
                             "*.mp4;*.mov;*.avi;*.mkv;*.webm;*.mp3;*.wav;*.flac;*.aac;*.ogg;*.m4a;*.jpg;*.png;*.bmp;*.tiff");
    
    if (chooser.browseForFileToOpen()) {
        auto file = chooser.getResult();
        
        // Stop current playback
        if (isPlaying_) {
            stopPlayback();
        }
        
        // Load new file
        if (mediaReader_->loadFile(file)) {
            isMediaLoaded_ = true;
            duration_ = mediaReader_->getDuration();
            
            // Configure UI for the loaded media
            positionSlider_.setRange(0.0, duration_);
            positionSlider_.setValue(0.0);
            positionSlider_.setEnabled(true);
            
            playPauseButton_.setEnabled(true);
            stopButton_.setEnabled(true);
            
            // Setup video display if video is present
            if (mediaReader_->hasVideo()) {
                videoDisplay_ = std::unique_ptr<juce::Component>(mediaReader_->getVideoComponent());
                if (videoDisplay_) {
                    addAndMakeVisible(*videoDisplay_);
                }
            } else {
                videoDisplay_.reset();
            }
            
            // Update volume if audio is present
            if (mediaReader_->hasAudio()) {
                auto* audioSource = dynamic_cast<cb_ffmpeg::MediaAudioSource*>(mediaReader_->getAudioSource());
                if (audioSource) {
                    audioSource->setGain(volumeSlider_.getValue());
                }
            }
            
            updatePositionDisplay();
            resized(); // Reposition components
            
            DBG("Loaded media file: " << file.getFileName());
            DBG("Duration: " << duration_ << " seconds");
            DBG("Has audio: " << (mediaReader_->hasAudio() ? "Yes" : "No"));
            DBG("Has video: " << (mediaReader_->hasVideo() ? "Yes" : "No"));
        }
        else {
            juce::AlertWindow::showMessageBox(juce::AlertWindow::WarningIcon,
                                            "Error",
                                            "Failed to load media file: " + file.getFileName(),
                                            "OK");
        }
    }
}

void MainComponent::togglePlayPause()
{
    if (!mediaReader_ || !isMediaLoaded_)
        return;
    
    if (isPlaying_) {
        mediaReader_->pause();
        isPlaying_ = false;
    } else {
        mediaReader_->play();
        isPlaying_ = true;
    }
    
    updatePlayPauseButton();
}

void MainComponent::stopPlayback()
{
    if (!mediaReader_ || !isMediaLoaded_)
        return;
    
    mediaReader_->stop();
    isPlaying_ = false;
    currentTime_ = 0.0;
    positionSlider_.setValue(0.0, juce::dontSendNotification);
    
    updatePlayPauseButton();
    updatePositionDisplay();
}

void MainComponent::updatePositionDisplay()
{
    juce::String currentTimeStr, durationStr;
    formatTime(currentTime_, currentTimeStr);
    formatTime(duration_, durationStr);
    
    positionLabel_.setText(currentTimeStr + " / " + durationStr, juce::dontSendNotification);
}

void MainComponent::updatePlayPauseButton()
{
    playPauseButton_.setButtonText(isPlaying_ ? "Pause" : "Play");
}

void MainComponent::handleMediaStateChange()
{
    // This could be called from callbacks if needed
    // For now, state changes are handled in timerCallback
}

void MainComponent::formatTime(double seconds, juce::String& timeString)
{
    int totalSeconds = static_cast<int>(seconds);
    int minutes = totalSeconds / 60;
    int secs = totalSeconds % 60;
    
    timeString = juce::String::formatted("%02d:%02d", minutes, secs);
}


