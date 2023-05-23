#pragma once

#include <JuceHeader.h>

#include "cb_ffmpeg/FFmpegVideoListener.h"

class MainComponent;
class FFMpegVideoComponent;

/*!
 */
class TransportComponent
: public juce::Component
, juce::Button::Listener
, juce::Slider::Listener
, public juce::Timer
, public FFmpegVideoListener
{
    friend class MainComponent;
    friend class FFMpegVideoComponent;
protected:
    bool isMinimalized = false;
    
    juce::TextButton openVideoButton;
    juce::TextButton playPauseButton;
    
    juce::TextButton speedNormalButton;
    juce::TextButton speedFasterButton;
    juce::TextButton speedSlowerButton;

    juce::Slider positionSlider;
    juce::Label positionLabel;
    
    FFMpegVideoComponent* videoScreenComponent;
    MainComponent* mainComponent;
    
    /*! Update interval for animated graphical elements (i.e. position slider) */
    int updateInterval = 100;
    
    /*! Flag to check, if video was stopped manually */
    bool pausedManually = false;

    
public:
    TransportComponent();
    ~TransportComponent() override;
    
    void paint (juce::Graphics& g) override;
    void resized() override;
    
    void buttonClicked (juce::Button* button) override;

    void sliderValueChanged (juce::Slider* slider) override;

    void sliderDragStarted ( juce::Slider* slider) override;

    void sliderDragEnded ( juce::Slider* slider) override;

    void timerCallback() override;
    
    void updateSlider();
    
    FFMpegVideoComponent* getVideoComponent();
    void setVideoComponent (FFMpegVideoComponent* videoScreenComp);
    
    MainComponent* getMainComponent();
    void setMainComponent (MainComponent* mainComp);
    
    /*! start the update timer to update the position slider and other sub components */
    void startUpdateTimer();
    
    void startOrPause();

    void stop();
    void play();
    
    void setTime(double time);
    
    void positionSecondsChanged (const double pts) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TransportComponent)
};
