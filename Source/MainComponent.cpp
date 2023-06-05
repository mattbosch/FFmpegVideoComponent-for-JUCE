#include "MainComponent.h"


MainComponent::MainComponent()
{
    setWantsKeyboardFocus (true);

    ffmpegVideoComponent = std::unique_ptr<FFmpegVideoComponent> ( new FFmpegVideoComponent () );
    addAndMakeVisible(ffmpegVideoComponent.get());
    
    transportComponent = std::unique_ptr<TransportComponent> ( new TransportComponent () );
    transportComponent->setMainComponent(this);
    transportComponent->setVideoComponent(ffmpegVideoComponent.get());
    ffmpegVideoComponent->getVideoReader()->addVideoListener(transportComponent.get());
    addAndMakeVisible(transportComponent.get());
    
    ffmpegVideoComponent->onPlaybackStarted = [this](){
        DBG("onPlaybackStarted: callback");
    };
    
    ffmpegVideoComponent->onPlaybackStopped = [this](){
        DBG("onPlaybackStarted: onPlaybackStopped");
    };

    setSize (800, 600);
}

MainComponent::~MainComponent()
{

}

void MainComponent::paint (juce::Graphics& g)
{
    juce::Rectangle<int> background = getLocalBounds();
    juce::ColourGradient cg = juce::ColourGradient::horizontal(juce::Colours::green.darker(1.0), 0.0, juce::Colours::green.darker(20.0), getWidth());

    g.setGradientFill(cg);
    g.fillRect(background);
    
    g.setFont (juce::Font (16.0f));
    g.setColour (juce::Colours::whitesmoke.withAlpha(0.5f));
    g.drawText ("Simple Juce FFmpeg Video Player", getLocalBounds().removeFromTop(50), juce::Justification::centredTop, true);
}

void MainComponent::resized()
{
    auto currentBounds = getLocalBounds();
    auto buttonBounds = currentBounds;
    
    transportComponent->setVisible(true);
    transportComponent->setBounds( buttonBounds.removeFromBottom(40) );
    ffmpegVideoComponent->setVisible(true);
    ffmpegVideoComponent->setBounds (buttonBounds);

}


