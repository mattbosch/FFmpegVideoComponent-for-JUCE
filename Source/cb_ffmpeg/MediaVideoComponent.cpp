#include "MediaVideoComponent.h"

namespace cb_ffmpeg
{

MediaVideoComponent::MediaVideoComponent(VideoBuffer& videoBuffer, const MediaInfo& mediaInfo)
    : videoBuffer_(videoBuffer), mediaInfo_(mediaInfo)
{
}

MediaVideoComponent::~MediaVideoComponent()
{
}

void MediaVideoComponent::paint(juce::Graphics& g)
{
}

void MediaVideoComponent::resized()
{
    calculateVideoRect();
}

void MediaVideoComponent::mouseDown(const juce::MouseEvent& event)
{
    // TODO: Implement mouse down interaction
}

void MediaVideoComponent::mouseDrag(const juce::MouseEvent& event)
{
    // TODO: Implement mouse drag interaction
}

void MediaVideoComponent::mouseWheelMove(const juce::MouseEvent& event, const juce::MouseWheelDetails& wheel)
{
    // TODO: Implement mouse wheel interaction
}

void MediaVideoComponent::setCurrentPosition(double positionInSeconds, double tolerance)
{
}

void MediaVideoComponent::setScalingMode(ScalingMode mode)
{
}

void MediaVideoComponent::setEnabled(bool enabled)
{
}

void MediaVideoComponent::setRefreshRate(double fps)
{
}

void MediaVideoComponent::updateNow()
{
}

juce::Rectangle<int> MediaVideoComponent::getVideoDimensions() const
{
    return juce::Rectangle<int>();
}

juce::Image MediaVideoComponent::getCurrentFrameImage() const
{
    return juce::Image();
}

uint64_t MediaVideoComponent::getFramesDropped() const
{
    return 0;
}

double MediaVideoComponent::getBufferLevel() const
{
    return 0.0;
}

void MediaVideoComponent::resetStatistics()
{
}

void MediaVideoComponent::setZoomFactor(double zoomFactor)
{
}

void MediaVideoComponent::timerCallback()
{
    if (enabled_.load())
    {
        updateCurrentFrame();
        updateNow();
    }
}

bool MediaVideoComponent::updateCurrentFrame()
{
    return false;
}

void MediaVideoComponent::calculateVideoRect()
{
}

} 