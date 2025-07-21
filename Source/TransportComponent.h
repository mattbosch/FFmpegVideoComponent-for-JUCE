#pragma once

#include <JuceHeader.h>
#include "cb_ffmpeg/FFmpegVideoListener.h"  // Keep for compatibility
#include "cb_ffmpeg/cb_ffmpeg.h"

class MainComponent;

/*!
 * Transport Component for media playback control
 * 
 * Updated to work with the new cb_ffmpeg::MediaReader architecture
 */
class TransportComponent : public juce::Component,
                          public juce::Button::Listener,
                          public juce::Slider::Listener,
                          public juce::Timer,
                          public FFmpegVideoListener  // Keep for compatibility
{
    friend class MainComponent;
    
protected:
    bool isMinimalized = false;
    
    juce::TextButton openVideoButton;
    juce::TextButton playPauseButton;
    
    juce::TextButton speedNormalButton;
    juce::TextButton speedFasterButton;
    juce::TextButton speedSlowerButton;

    juce::Slider positionSlider;
    juce::Label positionLabel;
    
    // Updated to use new architecture
    cb_ffmpeg::MediaReader* mediaReader_{nullptr};  // Non-owning pointer
    MainComponent* mainComponent_{nullptr};
    
    /*! Update interval for animated graphical elements (i.e. position slider) */
    int updateInterval = 100;
    
    /*! Flag to check, if video was stopped manually */
    bool pausedManually = false;
    bool isDraggingPosition_ = false;
    double currentTime_ = 0.0;
    double duration_ = 0.0;
    double playbackRate_ = 1.0;

public:
    TransportComponent();
    ~TransportComponent() override;
    
    void paint(juce::Graphics& g) override;
    void resized() override;
    
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;
    void sliderDragStarted(juce::Slider* slider) override;
    void sliderDragEnded(juce::Slider* slider) override;

    /*! called every 100 ms to update slider position and time label according to play position */
    void timerCallback() override;
    
    // Updated interface for new architecture
    void setMediaReader(cb_ffmpeg::MediaReader* reader);
    cb_ffmpeg::MediaReader* getMediaReader() { return mediaReader_; }
    
    MainComponent* getMainComponent() { return mainComponent_; }
    void setMainComponent(MainComponent* mainComp) { mainComponent_ = mainComp; }
    
    /*! start the update timer to update the position slider and other sub components */
    void startUpdateTimer();
    
    void startOrPause();
    void stop();
    void play();
    
    void setTime(double time);
    void setPlaybackRate(double rate);
    double getPlaybackRate() const { return playbackRate_; }
    
    /*! FFmpegVideoListener implementation (for compatibility) */
    void positionSecondsChanged(const double pts) override;

private:
    void updatePositionDisplay();
    void updatePlayPauseButton();
    void formatTime(double seconds, juce::String& timeString);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TransportComponent)
};
