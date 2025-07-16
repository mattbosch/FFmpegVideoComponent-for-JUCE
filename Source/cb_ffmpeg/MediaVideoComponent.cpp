#include "MediaVideoComponent.h"

namespace cb
{

MediaVideoComponent::MediaVideoComponent(std::shared_ptr<VideoBuffer> buffer, const MediaReaderConfig& config)
    : videoBuffer(buffer)
    , config(config)
    , lastFrameTime(-1.0)
    , frameRate(30.0)
    , isPlaying(false)
    , scalingMode(ScalingMode::AspectFit)
{
    // Start timer for frame updates
    startTimerHz(static_cast<int>(frameRate));
}

MediaVideoComponent::~MediaVideoComponent()
{
    stopTimer();
}

void MediaVideoComponent::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds();
    
    // Fill background
    g.fillAll(juce::Colours::black);
    
    // Check if we have a current frame
    if (!currentFrame.data.empty())
    {
        paintVideoFrame(g, bounds);
    }
    else
    {
        // No frame available - show placeholder
        g.setColour(juce::Colours::darkgrey);
        g.setFont(juce::Font(16.0f));
        g.drawText("No video frame", bounds, juce::Justification::centred);
    }
}

void MediaVideoComponent::paintVideoFrame(juce::Graphics& g, juce::Rectangle<int> bounds)
{
    if (currentFrame.data.empty())
        return;
    
    // Create JUCE image from frame data
    auto image = createJuceImage();
    if (image.isNull())
        return;
    
    // Calculate scaled rectangle
    auto targetRect = calculateScaledRectangle(
        juce::Rectangle<int>(0, 0, image.getWidth(), image.getHeight()),
        bounds
    );
    
    // Draw the image
    g.drawImageWithin(image, targetRect.getX(), targetRect.getY(), 
                     targetRect.getWidth(), targetRect.getHeight(),
                     juce::RectanglePlacement::centred);
    
    // Draw frame info if enabled
    if (config.enableLogging)
    {
        paintFrameInfo(g, bounds);
    }
}

juce::Image MediaVideoComponent::createJuceImage()
{
    if (currentFrame.data.empty())
        return {};
    
    // Create image based on pixel format
    juce::Image::PixelFormat juceFormat;
    int bytesPerPixel;
    
    switch (currentFrame.format)
    {
        case AV_PIX_FMT_RGB24:
            juceFormat = juce::Image::RGB;
            bytesPerPixel = 3;
            break;
            
        case AV_PIX_FMT_RGBA:
        case AV_PIX_FMT_BGRA:
            juceFormat = juce::Image::ARGB;
            bytesPerPixel = 4;
            break;
            
        default:
            // Unsupported format
            return {};
    }
    
    // Create JUCE image
    juce::Image image(juceFormat, currentFrame.width, currentFrame.height, true);
    
    // Get image data
    juce::Image::BitmapData bitmap(image, juce::Image::BitmapData::writeOnly);
    
    // Copy pixel data
    if (currentFrame.format == AV_PIX_FMT_RGB24)
    {
        copyRGBData(bitmap);
    }
    else if (currentFrame.format == AV_PIX_FMT_RGBA)
    {
        copyRGBAData(bitmap);
    }
    else if (currentFrame.format == AV_PIX_FMT_BGRA)
    {
        copyBGRAData(bitmap);
    }
    
    return image;
}

void MediaVideoComponent::copyRGBData(juce::Image::BitmapData& bitmap)
{
    const uint8_t* srcData = currentFrame.data.data();
    uint8_t* destData = bitmap.data;
    
    int width = currentFrame.width;
    int height = currentFrame.height;
    
    for (int y = 0; y < height; ++y)
    {
        const uint8_t* srcRow = srcData + y * width * 3;
        uint8_t* destRow = destData + y * bitmap.lineStride;
        
        for (int x = 0; x < width; ++x)
        {
            // RGB to ARGB conversion
            destRow[x * 4 + 0] = 255;           // Alpha
            destRow[x * 4 + 1] = srcRow[x * 3 + 0]; // Red
            destRow[x * 4 + 2] = srcRow[x * 3 + 1]; // Green
            destRow[x * 4 + 3] = srcRow[x * 3 + 2]; // Blue
        }
    }
}

void MediaVideoComponent::copyRGBAData(juce::Image::BitmapData& bitmap)
{
    const uint8_t* srcData = currentFrame.data.data();
    uint8_t* destData = bitmap.data;
    
    int width = currentFrame.width;
    int height = currentFrame.height;
    
    for (int y = 0; y < height; ++y)
    {
        const uint8_t* srcRow = srcData + y * width * 4;
        uint8_t* destRow = destData + y * bitmap.lineStride;
        
        for (int x = 0; x < width; ++x)
        {
            // RGBA to ARGB conversion
            destRow[x * 4 + 0] = srcRow[x * 4 + 3]; // Alpha
            destRow[x * 4 + 1] = srcRow[x * 4 + 0]; // Red
            destRow[x * 4 + 2] = srcRow[x * 4 + 1]; // Green
            destRow[x * 4 + 3] = srcRow[x * 4 + 2]; // Blue
        }
    }
}

void MediaVideoComponent::copyBGRAData(juce::Image::BitmapData& bitmap)
{
    const uint8_t* srcData = currentFrame.data.data();
    uint8_t* destData = bitmap.data;
    
    int width = currentFrame.width;
    int height = currentFrame.height;
    
    for (int y = 0; y < height; ++y)
    {
        const uint8_t* srcRow = srcData + y * width * 4;
        uint8_t* destRow = destData + y * bitmap.lineStride;
        
        for (int x = 0; x < width; ++x)
        {
            // BGRA to ARGB conversion
            destRow[x * 4 + 0] = srcRow[x * 4 + 3]; // Alpha
            destRow[x * 4 + 1] = srcRow[x * 4 + 2]; // Red
            destRow[x * 4 + 2] = srcRow[x * 4 + 1]; // Green
            destRow[x * 4 + 3] = srcRow[x * 4 + 0]; // Blue
        }
    }
}

juce::Rectangle<int> MediaVideoComponent::calculateScaledRectangle(
    juce::Rectangle<int> sourceRect, 
    juce::Rectangle<int> targetRect)
{
    if (sourceRect.isEmpty() || targetRect.isEmpty())
        return {};
    
    float sourceAspect = static_cast<float>(sourceRect.getWidth()) / sourceRect.getHeight();
    float targetAspect = static_cast<float>(targetRect.getWidth()) / targetRect.getHeight();
    
    juce::Rectangle<int> result;
    
    switch (scalingMode)
    {
        case ScalingMode::Stretch:
            result = targetRect;
            break;
            
        case ScalingMode::AspectFit:
            if (sourceAspect > targetAspect)
            {
                // Source is wider - fit to width
                int scaledHeight = static_cast<int>(targetRect.getWidth() / sourceAspect);
                result = juce::Rectangle<int>(
                    targetRect.getX(),
                    targetRect.getY() + (targetRect.getHeight() - scaledHeight) / 2,
                    targetRect.getWidth(),
                    scaledHeight
                );
            }
            else
            {
                // Source is taller - fit to height
                int scaledWidth = static_cast<int>(targetRect.getHeight() * sourceAspect);
                result = juce::Rectangle<int>(
                    targetRect.getX() + (targetRect.getWidth() - scaledWidth) / 2,
                    targetRect.getY(),
                    scaledWidth,
                    targetRect.getHeight()
                );
            }
            break;
            
        case ScalingMode::AspectFill:
            if (sourceAspect > targetAspect)
            {
                // Source is wider - fit to height
                int scaledWidth = static_cast<int>(targetRect.getHeight() * sourceAspect);
                result = juce::Rectangle<int>(
                    targetRect.getX() + (targetRect.getWidth() - scaledWidth) / 2,
                    targetRect.getY(),
                    scaledWidth,
                    targetRect.getHeight()
                );
            }
            else
            {
                // Source is taller - fit to width
                int scaledHeight = static_cast<int>(targetRect.getWidth() / sourceAspect);
                result = juce::Rectangle<int>(
                    targetRect.getX(),
                    targetRect.getY() + (targetRect.getHeight() - scaledHeight) / 2,
                    targetRect.getWidth(),
                    scaledHeight
                );
            }
            break;
    }
    
    return result;
}

void MediaVideoComponent::paintFrameInfo(juce::Graphics& g, juce::Rectangle<int> bounds)
{
    // Draw frame info in top-left corner
    g.setColour(juce::Colours::white.withAlpha(0.8f));
    g.setFont(juce::Font(12.0f));
    
    juce::String info = juce::String::formatted(
        "Frame: %dx%d\nTime: %.2fs\nQueue: %d",
        currentFrame.width,
        currentFrame.height,
        currentFrame.timestamp,
        static_cast<int>(videoBuffer->getQueueSize())
    );
    
    auto textBounds = juce::Rectangle<int>(10, 10, 150, 60);
    
    // Draw background
    g.setColour(juce::Colours::black.withAlpha(0.6f));
    g.fillRect(textBounds.expanded(5));
    
    // Draw text
    g.setColour(juce::Colours::white);
    g.drawText(info, textBounds, juce::Justification::topLeft);
}

void MediaVideoComponent::timerCallback()
{
    if (!isPlaying)
        return;
    
    // Try to get a new frame
    VideoFrame newFrame;
    if (videoBuffer->pop(newFrame))
    {
        // Check if this frame is newer than our current frame
        if (newFrame.timestamp > lastFrameTime)
        {
            currentFrame = std::move(newFrame);
            lastFrameTime = currentFrame.timestamp;
            repaint();
        }
    }
}

void MediaVideoComponent::setPlaying(bool playing)
{
    isPlaying = playing;
    
    if (isPlaying)
    {
        // Reset frame timing
        lastFrameTime = -1.0;
    }
}

bool MediaVideoComponent::getPlaying() const
{
    return isPlaying;
}

void MediaVideoComponent::setFrameRate(double fps)
{
    frameRate = fps;
    if (frameRate > 0)
    {
        stopTimer();
        startTimerHz(static_cast<int>(frameRate));
    }
}

double MediaVideoComponent::getFrameRate() const
{
    return frameRate;
}

void MediaVideoComponent::setScalingMode(ScalingMode mode)
{
    if (scalingMode != mode)
    {
        scalingMode = mode;
        repaint();
    }
}

MediaVideoComponent::ScalingMode MediaVideoComponent::getScalingMode() const
{
    return scalingMode;
}

void MediaVideoComponent::clearFrame()
{
    currentFrame = VideoFrame{};
    lastFrameTime = -1.0;
    repaint();
}

VideoFrame MediaVideoComponent::getCurrentFrame() const
{
    return currentFrame;
}

std::pair<int, int> MediaVideoComponent::getVideoSize() const
{
    if (!currentFrame.data.empty())
        return {currentFrame.width, currentFrame.height};
    
    return {0, 0};
}

void MediaVideoComponent::resized()
{
    // Component was resized - repaint to update scaling
    repaint();
}

} // namespace cb 