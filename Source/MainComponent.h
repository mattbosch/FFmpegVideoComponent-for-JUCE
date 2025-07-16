#pragma once

#include <juce_core/juce_core.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include "cb_ffmpeg/cb_ffmpeg.h"

//==============================================================================
/*
    Modern MainComponent using the new cb_ffmpeg::MediaReader architecture
    Supports universal media playback (audio, video, images) with thread-safe
    asynchronous decoding and professional-grade performance.
*/
class MainComponent : public juce::Component,
                     public juce::AudioSource,
                     public juce::Timer,
                     public juce::Button::Listener,
                     public juce::Slider::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;
    
    //==============================================================================
    // juce::Component
    void paint(juce::Graphics&) override;
    void resized() override;
    
    // juce::AudioSource
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    
    // juce::Timer (for UI updates)
    void timerCallback() override;
    
    // juce::Button::Listener
    void buttonClicked(juce::Button* button) override;
    
    // juce::Slider::Listener
    void sliderValueChanged(juce::Slider* slider) override;

private:
    //==============================================================================
    // Media System
    std::unique_ptr<cb_ffmpeg::MediaReader> mediaReader_;
    cb_ffmpeg::MediaReaderConfig config_;
    
    // UI Components
    juce::TextButton openButton_{"Open Media File"};
    juce::TextButton playPauseButton_{"Play"};
    juce::TextButton stopButton_{"Stop"};
    
    juce::Slider positionSlider_;
    juce::Label positionLabel_{"Position", "00:00 / 00:00"};
    
    juce::Slider volumeSlider_;
    juce::Label volumeLabel_{"Volume", "Volume"};
    
    juce::ToggleButton loopButton_{"Loop"};
    juce::ToggleButton muteButton_{"Mute"};
    
    // Video display area
    std::unique_ptr<juce::Component> videoDisplay_;
    
    // State
    bool isMediaLoaded_{false};
    bool isPlaying_{false};
    bool isDraggingPosition_{false};
    double currentTime_{0.0};
    double duration_{0.0};
    
    // Helper methods
    void openMediaFile();
    void togglePlayPause();
    void stopPlayback();
    void updatePositionDisplay();
    void updatePlayPauseButton();
    void handleMediaStateChange();
    void setupUI();
    void formatTime(double seconds, juce::String& timeString);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
