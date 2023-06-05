#pragma once

#include <JuceHeader.h>

#include "cb_ffmpeg/FFmpegVideoListener.h"
#include "cb_ffmpeg/FFmpegVideoComponent.h"

#include "TransportComponent.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;
    
    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    std::unique_ptr<FFmpegVideoComponent> ffmpegVideoComponent;
    std::unique_ptr<TransportComponent> transportComponent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
