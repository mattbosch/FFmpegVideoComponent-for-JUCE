#include "TransportComponent.h"
#include "MainComponent.h"

//==============================================================================
TransportComponent::TransportComponent()
{
    addAndMakeVisible(openVideoButton);
    addAndMakeVisible(playPauseButton);
    addAndMakeVisible(speedNormalButton);
    addAndMakeVisible(speedFasterButton);
    addAndMakeVisible(speedSlowerButton);
    addAndMakeVisible(positionSlider);
    addAndMakeVisible(positionLabel);
    
    // Configure buttons
    openVideoButton.setButtonText("Open");
    playPauseButton.setButtonText("Play");
    speedNormalButton.setButtonText("1x");
    speedFasterButton.setButtonText("2x");
    speedSlowerButton.setButtonText("0.5x");
    
    // Configure position controls
    positionSlider.setRange(0.0, 1.0);
    positionSlider.setValue(0.0);
    positionSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    positionSlider.setEnabled(false);
    
    positionLabel.setText("00:00 / 00:00", juce::dontSendNotification);
    positionLabel.setJustificationType(juce::Justification::centred);
    
    // Add listeners
    openVideoButton.addListener(this);
    playPauseButton.addListener(this);
    speedNormalButton.addListener(this);
    speedFasterButton.addListener(this);
    speedSlowerButton.addListener(this);
    positionSlider.addListener(this);
    
    // Initial state
    playPauseButton.setEnabled(false);
    speedNormalButton.setEnabled(false);
    speedFasterButton.setEnabled(false);
    speedSlowerButton.setEnabled(false);
    
    setSize(600, 80);
}

TransportComponent::~TransportComponent()
{
    stopTimer();
}

void TransportComponent::paint(juce::Graphics& g)
{
    // Background
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId).darker(0.1f));
    
    // Border
    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);
}

void TransportComponent::resized()
{
    auto bounds = getLocalBounds().reduced(10);
    
    // Top row: buttons
    auto buttonRow = bounds.removeFromTop(30);
    openVideoButton.setBounds(buttonRow.removeFromLeft(80));
    buttonRow.removeFromLeft(10);
    
    playPauseButton.setBounds(buttonRow.removeFromLeft(60));
    buttonRow.removeFromLeft(10);
    
    speedSlowerButton.setBounds(buttonRow.removeFromLeft(40));
    buttonRow.removeFromLeft(5);
    speedNormalButton.setBounds(buttonRow.removeFromLeft(40));
    buttonRow.removeFromLeft(5);
    speedFasterButton.setBounds(buttonRow.removeFromLeft(40));
    
    bounds.removeFromTop(10);
    
    // Bottom row: position controls
    auto positionRow = bounds.removeFromTop(30);
    positionLabel.setBounds(positionRow.removeFromRight(120));
    positionRow.removeFromRight(10);
    positionSlider.setBounds(positionRow);
}

void TransportComponent::buttonClicked(juce::Button* button)
{
    if (button == &openVideoButton) {
        if (mainComponent_) {
            // Trigger file open in main component
            mainComponent_->openFile();
        }
    }
    else if (button == &playPauseButton) {
        startOrPause();
    }
    else if (button == &speedSlowerButton) {
        setPlaybackRate(0.5);
    }
    else if (button == &speedNormalButton) {
        setPlaybackRate(1.0);
    }
    else if (button == &speedFasterButton) {
        setPlaybackRate(2.0);
    }
}

void TransportComponent::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &positionSlider && isDraggingPosition_) {
        if (mediaReader_ && duration_ > 0.0) {
            double newPosition = positionSlider.getValue() * duration_;
            mediaReader_->seek(newPosition);
            currentTime_ = newPosition;
            updatePositionDisplay();
        }
    }
}

void TransportComponent::sliderDragStarted(juce::Slider* slider)
{
    if (slider == &positionSlider) {
        isDraggingPosition_ = true;
    }
}

void TransportComponent::sliderDragEnded(juce::Slider* slider)
{
    if (slider == &positionSlider) {
        isDraggingPosition_ = false;
    }
}

void TransportComponent::timerCallback()
{
    if (!mediaReader_) {
        return;
    }
    
    // Update current time
    currentTime_ = mediaReader_->getCurrentPosition();
    duration_ = mediaReader_->getDuration();
    
    // Update position slider (but not if user is dragging it)
    if (!isDraggingPosition_ && duration_ > 0.0) {
        double progress = currentTime_ / duration_;
        positionSlider.setValue(progress, juce::dontSendNotification);
    }
    
    updatePositionDisplay();
    
    // Update button states based on MediaReader state
    bool isPlaying = mediaReader_->isPlaying();
    playPauseButton.setButtonText(isPlaying ? "Pause" : "Play");
    
    // Enable/disable controls based on media loaded state
    bool hasMedia = mediaReader_->isLoaded();
    playPauseButton.setEnabled(hasMedia);
    speedNormalButton.setEnabled(hasMedia);
    speedFasterButton.setEnabled(hasMedia);
    speedSlowerButton.setEnabled(hasMedia);
    positionSlider.setEnabled(hasMedia);
    
    // Call legacy listener method for compatibility
    positionSecondsChanged(currentTime_);
}

void TransportComponent::setMediaReader(cb_ffmpeg::MediaReader* reader)
{
    mediaReader_ = reader;
    
    if (mediaReader_) {
        duration_ = mediaReader_->getDuration();
        currentTime_ = mediaReader_->getCurrentPosition();
        
        // Reset position slider
        positionSlider.setRange(0.0, 1.0);
        positionSlider.setValue(0.0);
        
        updatePositionDisplay();
        updatePlayPauseButton();
    }
}

void TransportComponent::startUpdateTimer()
{
    startTimerHz(static_cast<int>(1000.0 / updateInterval));
}

void TransportComponent::startOrPause()
{
    if (!mediaReader_) {
        return;
    }
    
    if (mediaReader_->isPlaying()) {
        mediaReader_->pause();
        pausedManually = true;
    } else {
        mediaReader_->play();
        pausedManually = false;
    }
    
    updatePlayPauseButton();
}

void TransportComponent::stop()
{
    if (mediaReader_) {
        mediaReader_->stop();
        currentTime_ = 0.0;
        positionSlider.setValue(0.0, juce::dontSendNotification);
        updatePlayPauseButton();
        updatePositionDisplay();
    }
}

void TransportComponent::play()
{
    if (mediaReader_) {
        mediaReader_->play();
        pausedManually = false;
        updatePlayPauseButton();
    }
}

void TransportComponent::setTime(double time)
{
    if (mediaReader_) {
        mediaReader_->seek(time);
        currentTime_ = time;
        
        if (duration_ > 0.0) {
            double progress = time / duration_;
            positionSlider.setValue(progress, juce::dontSendNotification);
        }
        
        updatePositionDisplay();
    }
}

void TransportComponent::setPlaybackRate(double rate)
{
    playbackRate_ = rate;
    
    if (mediaReader_) {
        mediaReader_->setPlaybackRate(rate);
    }
    
    // Update button states to show current rate
    speedSlowerButton.setToggleState(rate == 0.5, juce::dontSendNotification);
    speedNormalButton.setToggleState(rate == 1.0, juce::dontSendNotification);
    speedFasterButton.setToggleState(rate == 2.0, juce::dontSendNotification);
}

void TransportComponent::positionSecondsChanged(const double pts)
{
    // Legacy callback method - implementation can be empty
    // or forward to other components if needed
    juce::ignoreUnused(pts);
}

void TransportComponent::updatePositionDisplay()
{
    juce::String currentTimeStr, durationStr;
    formatTime(currentTime_, currentTimeStr);
    formatTime(duration_, durationStr);
    
    positionLabel.setText(currentTimeStr + " / " + durationStr, juce::dontSendNotification);
}

void TransportComponent::updatePlayPauseButton()
{
    if (mediaReader_) {
        bool isPlaying = mediaReader_->isPlaying();
        playPauseButton.setButtonText(isPlaying ? "Pause" : "Play");
    } else {
        playPauseButton.setButtonText("Play");
    }
}

void TransportComponent::formatTime(double seconds, juce::String& timeString)
{
    int totalSeconds = static_cast<int>(seconds);
    int hours = totalSeconds / 3600;
    int minutes = (totalSeconds % 3600) / 60;
    int secs = totalSeconds % 60;
    
    if (hours > 0) {
        timeString = juce::String::formatted("%d:%02d:%02d", hours, minutes, secs);
    } else {
        timeString = juce::String::formatted("%02d:%02d", minutes, secs);
    }
}



