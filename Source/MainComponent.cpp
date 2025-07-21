#include "MainComponent.h"

MainComponent::MainComponent()
{
    setupUI();
    initializeAudio();
    startTimerHz(30);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    
    if (isDragHover_)
    {
        g.setColour(juce::Colours::white.withAlpha(0.3f));
        g.fillAll();
        g.setColour(juce::Colours::white);
        g.drawRect(getLocalBounds(), 2.0f);
        g.setFont(juce::FontOptions(24.0f));
        g.drawText("Drop Media File Here", getLocalBounds(), juce::Justification::centred);
    }
}

void MainComponent::resized()
{
    auto bounds = getLocalBounds().reduced(10);
    
    auto topArea = bounds.removeFromTop(120);
    transportGroup_.setBounds(topArea.removeFromLeft(topArea.getWidth() / 2));
    infoGroup_.setBounds(topArea);
    
    bounds.removeFromTop(10);
    
    playerComponent.setBounds(bounds);
    
    // Layout transport controls within transportGroup_
    auto transportBounds = transportGroup_.getLocalBounds().reduced(10);
    transportBounds.removeFromTop(20); // Space for group title
    
    // First row: buttons
    auto buttonRow = transportBounds.removeFromTop(30);
    openButton_.setBounds(buttonRow.removeFromLeft(80));
    buttonRow.removeFromLeft(5);
    playPauseButton_.setBounds(buttonRow.removeFromLeft(60));
    buttonRow.removeFromLeft(5);
    stopButton_.setBounds(buttonRow.removeFromLeft(50));
    buttonRow.removeFromLeft(10);
    muteButton_.setBounds(buttonRow.removeFromRight(60));
    
    transportBounds.removeFromTop(10);
    
    // Second row: position slider and label
    auto sliderRow = transportBounds.removeFromTop(25);
    positionLabel_.setBounds(sliderRow.removeFromRight(100));
    sliderRow.removeFromRight(10);
    positionSlider_.setBounds(sliderRow);
    
    transportBounds.removeFromTop(5);
    
    // Third row: volume slider
    auto volumeRow = transportBounds.removeFromTop(25);
    volumeRow.removeFromLeft(50); // Some spacing
    volumeSlider_.setBounds(volumeRow.removeFromLeft(150));
    
    // Layout info display within infoGroup_
    auto infoBounds = infoGroup_.getLocalBounds().reduced(10);
    infoBounds.removeFromTop(20); // Space for group title
    infoDisplay_.setBounds(infoBounds);
}

void MainComponent::timerCallback()
{
    if (!isDraggingPosition_)
    {
        updatePositionDisplay();
    }
    updatePlayPauseButton();
}

void MainComponent::buttonClicked(juce::Button* button)
{
    if (button == &openButton_)
    {
        juce::FileChooser chooser("Select a media file to play...", {},
                                  "*.mp4;*.mov;*.avi;*.mkv;*.webm;*.mp3;*.wav;*.flac;*.aac;*.ogg;*.jpg;*.jpeg;*.png;.gif");
        if (chooser.browseForFileToOpen())
        {
            loadMediaFile(chooser.getResult());
        }
    }
    else if (button == &playPauseButton_)
    {
        playerComponent.togglePlayPause();
    }
    else if (button == &stopButton_)
    {
        playerComponent.stopPlayback();
    }
    else if (button == &muteButton_)
    {
        bool newMutedState = !playerComponent.isMuted();
        playerComponent.setMuted(newMutedState);
        muteButton_.setToggleState(newMutedState, juce::dontSendNotification);
        muteButton_.setButtonText(newMutedState ? "Unmute" : "Mute");
    }
}

void MainComponent::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volumeSlider_)
    {
        playerComponent.setVolume(volumeSlider_.getValue());
    }
    else if (slider == &positionSlider_)
    {
        // Position slider handled in drag ended for seeking
    }
}

void MainComponent::sliderDragStarted(juce::Slider* slider)
{
    if (slider == &positionSlider_)
    {
        isDraggingPosition_ = true;
    }
}

void MainComponent::sliderDragEnded(juce::Slider* slider)
{
    if (slider == &positionSlider_)
    {
        if (playerComponent.isMediaLoaded() && playerComponent.getDuration() > 0)
        {
            double newPosition = (positionSlider_.getValue() / 100.0) * playerComponent.getDuration();
            // TODO: Implement seeking in MediaReader
            // playerComponent.seek(newPosition);
            juce::Logger::writeToLog("Seek requested to: " + juce::String(newPosition) + "s (not yet implemented in MediaReader)");
        }
        isDraggingPosition_ = false;
    }
}

bool MainComponent::isInterestedInFileDrag(const juce::StringArray& files)
{
    if (files.size() == 1)
    {
        return isMediaFileSupported(juce::File(files[0]));
    }
    return false;
}

void MainComponent::fileDragEnter(const juce::StringArray& files, int x, int y)
{
    isDragHover_ = true;
    repaint();
}

void MainComponent::fileDragExit(const juce::StringArray& files)
{
    isDragHover_ = false;
    repaint();
}

void MainComponent::filesDropped(const juce::StringArray& files, int x, int y)
{
    isDragHover_ = false;
    if (files.size() == 1)
    {
        loadMediaFile(juce::File(files[0]));
    }
    repaint();
}

void MainComponent::openFile()
{
    juce::FileChooser chooser("Select a media file to open...",
                              juce::File(),
                              "*.mp4;*.mov;*.avi;*.mp3;*.wav;*.flac");
    
    if (chooser.browseForFileToOpen())
    {
        juce::File file = chooser.getResult();
        if (file.exists())
        {
            loadMediaFile(file);
        }
    }
}

void MainComponent::initializeAudio()
{
    juce::AudioDeviceManager::AudioDeviceSetup setup;
    setup.outputChannels = 2;
    setup.sampleRate = 44100.0; // Match MediaReader default sample rate
    setup.bufferSize = 512;     // Set a reasonable buffer size
    
    auto err = audioDeviceManager_.initialise(0, 2, nullptr, true, {}, &setup);
    if (err.isNotEmpty())
    {
        juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::WarningIcon, "Audio Init Error", err);
    }
    else
    {
        audioDeviceManager_.addAudioCallback(&playerComponent);
        juce::Logger::writeToLog("MainComponent: Audio initialized at " + juce::String(setup.sampleRate) + " Hz");
    }
}

void MainComponent::shutdownAudio()
{
    audioDeviceManager_.removeAudioCallback(&playerComponent);
    audioDeviceManager_.closeAudioDevice();
}

void MainComponent::setupUI()
{
    addAndMakeVisible(playerComponent);

    // Create and add groups
    addAndMakeVisible(transportGroup_);
    addAndMakeVisible(infoGroup_);

    // Transport Controls - add to transportGroup
    transportGroup_.addAndMakeVisible(openButton_);
    openButton_.addListener(this);
    
    transportGroup_.addAndMakeVisible(playPauseButton_);
    playPauseButton_.addListener(this);
    playPauseButton_.setEnabled(false);
    
    transportGroup_.addAndMakeVisible(stopButton_);
    stopButton_.addListener(this);
    stopButton_.setEnabled(false);
    
    transportGroup_.addAndMakeVisible(positionSlider_);
    positionSlider_.addListener(this);
    positionSlider_.setRange(0, 100, 0);
    positionSlider_.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    positionSlider_.setEnabled(false);

    transportGroup_.addAndMakeVisible(positionLabel_);
    
    transportGroup_.addAndMakeVisible(volumeSlider_);
    volumeSlider_.addListener(this);
    volumeSlider_.setRange(0, 1, 0.01);
    volumeSlider_.setValue(0.7);
    
    transportGroup_.addAndMakeVisible(muteButton_);
    muteButton_.addListener(this);
    muteButton_.setClickingTogglesState(true);
    muteButton_.setButtonText("Mute");

    // Info Display - add to infoGroup
    infoGroup_.addAndMakeVisible(infoDisplay_);
    infoDisplay_.setMultiLine(true);
    infoDisplay_.setReadOnly(true);
    infoDisplay_.setFont(juce::FontOptions(14.0f));
    
    setSize(800, 600);
}

void MainComponent::loadMediaFile(const juce::File& file)
{
    if (playerComponent.loadMediaFile(file))
    {
        currentFilename_ = file.getFileName();
        playPauseButton_.setEnabled(true);
        stopButton_.setEnabled(true);
        positionSlider_.setEnabled(true);
        positionSlider_.setRange(0, playerComponent.getDuration(), 0.1);
        
        // Apply current volume settings
        playerComponent.setVolume(volumeSlider_.getValue());
        playerComponent.setMuted(muteButton_.getToggleState());
        
        updateMediaInfo();
        
        // Show a brief notification that the file was loaded
        juce::String message = "Loaded: " + file.getFileName();
        if (playerComponent.getDuration() > 0)
        {
            message += " (" + juce::String(playerComponent.getDuration(), 1) + "s)";
        }
        juce::Logger::writeToLog("UI: " + message);
    }
    else
    {
        juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::WarningIcon, "Error", "Could not load media file.");
    }
}

void MainComponent::updatePositionDisplay()
{
    double currentTime = playerComponent.getCurrentTime();
    double duration = playerComponent.getDuration();
    positionSlider_.setValue(currentTime, juce::dontSendNotification);
    
    juce::String timeStr;
    formatTime(currentTime, timeStr);
    timeStr += " / ";
    formatTime(duration, timeStr);
    positionLabel_.setText(timeStr, juce::dontSendNotification);
}

void MainComponent::updatePlayPauseButton()
{
    playPauseButton_.setButtonText(playerComponent.isPlaying() ? "Pause" : "Play");
}

void MainComponent::formatTime(double seconds, juce::String& timeString)
{
    int totalSeconds = static_cast<int>(round(seconds));
    int mins = totalSeconds / 60;
    int secs = totalSeconds % 60;
    timeString = juce::String::formatted("%02d:%02d", mins, secs);
}

bool MainComponent::isMediaFileSupported(const juce::File& file)
{
    // A rough check. PlayerComponent's MediaReader will do the real one.
    return file.hasFileExtension(".mp4;.mov;.avi;.mkv;.webm;.mp3;.wav;.flac;.aac;.ogg;.jpg;.jpeg;.png;.gif");
}

void MainComponent::updateMediaInfo()
{
    if (playerComponent.isMediaLoaded())
    {
        juce::String info = "File: " + currentFilename_ + "\n";
        
        double duration = playerComponent.getDuration();
        if (duration > 0)
        {
            int mins = (int)(duration / 60);
            int secs = (int)duration % 60;
            info += "Duration: " + juce::String::formatted("%d:%02d", mins, secs) + "\n";
        }
        
        info += "Status: Ready to play";
        
        infoDisplay_.setText(info);
    }
    else
    {
        infoDisplay_.setText("No media file loaded\n\nDrag and drop a media file or click 'Open Media File'");
    }
}


