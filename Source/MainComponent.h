#pragma once

#include "JuceHeader.h"
#include "PlayerComponent.h"

//==============================================================================
/*
    Universal Media Player using cb_ffmpeg::MediaReader
    
    A comprehensive media player that demonstrates all features of the new
    cb_ffmpeg architecture including:
    - Universal media format support (audio, video, images)
    - Hardware-accelerated video decoding
    - Thread-safe asynchronous playback
    - Real-time audio/video synchronization
    - Professional transport controls
*/
class MainComponent : public juce::Component,
                     public juce::Timer,
                     public juce::Button::Listener,
                     public juce::Slider::Listener,
                     public juce::FileDragAndDropTarget
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;
    
    //==============================================================================
    // juce::Component
    void paint(juce::Graphics&) override;
    void resized() override;
    
    // juce::Timer (for UI updates)
    void timerCallback() override;
    
    // juce::Button::Listener
    void buttonClicked(juce::Button* button) override;
    
    // juce::Slider::Listener
    void sliderValueChanged(juce::Slider* slider) override;
    void sliderDragStarted(juce::Slider* slider) override;
    void sliderDragEnded(juce::Slider* slider) override;
    
    // juce::FileDragAndDropTarget
    bool isInterestedInFileDrag(const juce::StringArray& files) override;
    void fileDragEnter(const juce::StringArray& files, int x, int y) override;
    void fileDragExit(const juce::StringArray& files) override;
    void filesDropped(const juce::StringArray& files, int x, int y) override;
    
    // Public interface for external controls
    void openFile();

private:
    //==============================================================================
    // Media System
    juce::AudioDeviceManager audioDeviceManager_;
    PlayerComponent playerComponent;

    // UI Layout Groups
    juce::GroupComponent transportGroup_{"", "Transport Controls"};
    juce::GroupComponent configGroup_{"", "Configuration"};
    juce::GroupComponent infoGroup_{"", "Media Information"};
    
    // Transport Controls
    juce::TextButton openButton_{"Open Media File"};
    juce::TextButton playPauseButton_{"Play"};
    juce::TextButton stopButton_{"Stop"};
    juce::ToggleButton loopButton_{"Loop"};
    
    // Position and Volume Controls
    juce::Slider positionSlider_;
    juce::Label positionLabel_{"", "00:00 / 00:00"};
    juce::Slider volumeSlider_;
    juce::Label volumeLabel_{"", "Volume"};
    juce::ToggleButton muteButton_{"Mute"};
    
    // Configuration Controls
    juce::ComboBox configPresetBox_;
    juce::ToggleButton hardwareDecodingButton_{"Hardware Decoding"};
    juce::ToggleButton debugLoggingButton_{"Debug Logging"};
    juce::Slider audioBufferSlider_;
    juce::Label audioBufferLabel_{"", "Audio Buffer (ms)"};
    
    // Information Display
    juce::TextEditor infoDisplay_;
    
    // State Management
    bool isDraggingPosition_{false};
    bool isDragHover_{false};
    juce::String currentFilename_;
    
    //==============================================================================
    // Helper Methods
    void initializeAudio();
    void shutdownAudio();
    void setupUI();
    void loadMediaFile(const juce::File& file);
    void updatePositionDisplay();
    void updatePlayPauseButton();
    void updateMediaInfo();
    void formatTime(double seconds, juce::String& timeString);
    bool isMediaFileSupported(const juce::File& file);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
