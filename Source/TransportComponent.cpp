#include "TransportComponent.h"

#include "MainComponent.h"
#include "cb_ffmpeg/FFmpegVideoComponent.h"
#include "cb_strings/StringHelper.h"



TransportComponent::TransportComponent()
: openVideoButton("Open...")
, playPauseButton("Play/Pause")
, speedNormalButton("normal speed")
, speedFasterButton("+")
, speedSlowerButton("-")
, positionSlider ("PositionSlider")
, positionLabel ("transportPositionLabel")
{
    setName("TransportComponent");
    
    addMouseListener(this, true);
    
    addAndMakeVisible(&openVideoButton);
    openVideoButton.setEnabled(true);
    
    addAndMakeVisible(&playPauseButton);
    playPauseButton.setEnabled(true);
    
    addAndMakeVisible(&speedNormalButton);
    speedNormalButton.setEnabled(true);
    addAndMakeVisible(&speedSlowerButton);
    speedSlowerButton.setEnabled(true);
    addAndMakeVisible(&speedFasterButton);
    speedFasterButton.setEnabled(true);
    
    positionSlider.setRange(0.0, 1.0);
    positionSlider.setName("PositionSlider");
    positionSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    positionSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 80, 80);//, true, 80, 80);
    
    positionLabel.setText("00:00 / 00:00", juce::dontSendNotification);
    positionLabel.setJustificationType(juce::Justification::centred);
    
    addAndMakeVisible(&positionSlider);
    addAndMakeVisible(&positionLabel);
    
    playPauseButton.addListener(this);
    openVideoButton.addListener(this);
    
    speedNormalButton.addListener(this);
    speedSlowerButton.addListener(this);
    speedFasterButton.addListener(this);
    
    positionSlider.addListener(this);
}

TransportComponent::~TransportComponent()
{

}

FFMpegVideoComponent* TransportComponent::getVideoComponent()
{
    return videoScreenComponent;
}

void TransportComponent::setVideoComponent (FFMpegVideoComponent* videoScreenComp)
{
    videoScreenComponent = videoScreenComp;
}


MainComponent* TransportComponent::getMainComponent()
{
    return mainComponent;
}

void TransportComponent::setMainComponent (MainComponent* mainComp)
{
    mainComponent = mainComp;
}


void TransportComponent::startUpdateTimer()
{
    startTimer(updateInterval);
}

void TransportComponent::paint (juce::Graphics& g)
{
    juce::Rectangle<int> background = getLocalBounds();
    juce::ColourGradient cg = juce::ColourGradient::horizontal(juce::Colours::grey.darker(1.0), 0.0, juce::Colours::grey.darker(20.0), getWidth());

    g.setGradientFill(cg);
    g.fillRect(background);
    
    g.setFont (juce::Font (16.0f));
    g.setColour (juce::Colours::whitesmoke.withAlpha(0.5f));
}

void TransportComponent::resized()
{
    auto currentBounds = getLocalBounds();
    int margin = 5;
    auto buttonBounds = currentBounds;
    
    buttonBounds.reduce(margin, margin);
    
    //place components from Left
    buttonBounds.removeFromLeft(margin);
    
    openVideoButton.setVisible(true);
    openVideoButton.setBounds( buttonBounds.removeFromLeft(80));
    buttonBounds.removeFromLeft(margin);
    
    playPauseButton.setVisible(true);
    playPauseButton.setBounds( buttonBounds.removeFromLeft(80));
    buttonBounds.removeFromLeft(margin);
    
    speedSlowerButton.setVisible(true);
    speedSlowerButton.setBounds( buttonBounds.removeFromLeft(40));
    buttonBounds.removeFromLeft(margin);
    
    speedNormalButton.setVisible(true);
    speedNormalButton.setBounds( buttonBounds.removeFromLeft(80));
    buttonBounds.removeFromLeft(margin);
    
    speedFasterButton.setVisible(true);
    speedFasterButton.setBounds( buttonBounds.removeFromLeft(40));
    buttonBounds.removeFromLeft(margin);

    buttonBounds.removeFromRight(margin);
    positionLabel.setBounds(buttonBounds.removeFromRight(80));
    buttonBounds.removeFromRight(margin);

    positionSlider.setBounds(buttonBounds);
}

void TransportComponent::buttonClicked (juce::Button* button)
{
    if (button == &playPauseButton ){
        startOrPause();
    }
    else if (button == &openVideoButton ){
        juce::FileChooser chooser ("Open Video File");
        if (chooser.browseForFileToOpen()) {
            juce::File video = chooser.getResult();
            videoScreenComponent->load(video);
        }
    }
    else if (button == &speedNormalButton){
        DBG("playback speed: 1.0");
        videoScreenComponent->setPlaySpeed(1.0);
    }
    else if (button == &speedSlowerButton){
        double newSpeed = videoScreenComponent->getPlaySpeed() - 0.2;
        DBG("playback speed slower: " + juce::String(newSpeed));
        videoScreenComponent->setPlaySpeed(newSpeed);
    }
    else if (button == &speedFasterButton){
        double newSpeed = videoScreenComponent->getPlaySpeed() + 0.2;
        DBG("playback speed faster: " + juce::String(newSpeed));
        videoScreenComponent->setPlaySpeed(newSpeed);
    }
}

void TransportComponent::timerCallback()
{
    repaint();
}

void TransportComponent::updateSlider()
{

}

void TransportComponent::sliderValueChanged (juce::Slider* slider)
{
    if (slider == &positionSlider)
    {
        videoScreenComponent->setPlayPosition(slider->getValue() * videoScreenComponent->getVideoDuration());
    }
}

void TransportComponent::sliderDragStarted ( juce::Slider* slider)
{
#if JUCE_MAC
#pragma unused(slider)
#endif
}

void TransportComponent::sliderDragEnded ( juce::Slider* slider)
{
#if JUCE_MAC
#pragma unused(slider)
#endif
}

void TransportComponent::startOrPause() {
    
    if (videoScreenComponent->isVideoOpen())
    {
        if ( videoScreenComponent->isPlaying() )
        {
            videoScreenComponent->stop();
        }
        else
        {
            videoScreenComponent->play();
        }
        resized();
    }
    
}

void TransportComponent::stop() {

}

void TransportComponent::play() {

}

void TransportComponent::positionSecondsChanged (const double pts)
{
//    DBG("position update:" + juce::String(pts));
    auto lambda = [pts, this]()
    {
        positionLabel.setText(StringHelper::convertSecondsToTimeString(pts, false), juce::dontSendNotification);
        positionSlider.setValue( pts / videoScreenComponent->getVideoDuration(), juce::dontSendNotification);
    };
    juce::MessageManager::callAsync(lambda);
}



