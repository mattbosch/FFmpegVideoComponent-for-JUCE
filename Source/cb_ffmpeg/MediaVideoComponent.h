#pragma once

#include "MediaReaderTypes.h"
#include "VideoBuffer.h"
#include <atomic>
#include <mutex>

namespace cb_ffmpeg {

/**
 * JUCE Component that displays video frames from MediaReader's VideoBuffer
 * 
 * This component provides smooth video playback with automatic scaling,
 * aspect ratio preservation, and synchronization with audio playback.
 */
class MediaVideoComponent : public juce::Component, private juce::Timer {
public:
    /**
     * Scaling modes for video display
     */
    enum class ScalingMode {
        Fit,              // Fit entire video in component (black bars if needed)
        Fill,             // Fill entire component (crop if needed)
        Stretch,          // Stretch to fill component (ignore aspect ratio)
        ActualSize        // Display at actual pixel size
    };
    
    /**
     * Constructor
     * @param videoBuffer The video buffer to read from
     * @param mediaInfo Media information for configuration
     */
    MediaVideoComponent(VideoBuffer& videoBuffer, const MediaInfo& mediaInfo);
    
    /**
     * Destructor
     */
    ~MediaVideoComponent() override;
    
    // Disable copy and assignment
    MediaVideoComponent(const MediaVideoComponent&) = delete;
    MediaVideoComponent& operator=(const MediaVideoComponent&) = delete;
    
    // ========================================================================
    // juce::Component Implementation
    // ========================================================================
    
    /**
     * Paint the component
     */
    void paint(juce::Graphics& g) override;
    
    /**
     * Handle component resize
     */
    void resized() override;
    
    /**
     * Handle mouse events
     */
    void mouseDown(const juce::MouseEvent& event) override;
    void mouseDrag(const juce::MouseEvent& event) override;
    void mouseWheelMove(const juce::MouseEvent& event, const juce::MouseWheelDetails& wheel) override;
    
    // ========================================================================
    // Video Display Control
    // ========================================================================
    
    /**
     * Set the current playback position for frame synchronization
     * @param positionInSeconds Current position in seconds
     * @param tolerance Time tolerance for frame selection
     */
    void setCurrentPosition(double positionInSeconds, double tolerance = 0.040);
    
    /**
     * Get the current display position
     * @return Current position in seconds
     */
    double getCurrentPosition() const { return currentPosition_.load(); }
    
    /**
     * Set video scaling mode
     * @param mode Scaling mode to use
     */
    void setScalingMode(ScalingMode mode);
    
    /**
     * Get current scaling mode
     * @return Current scaling mode
     */
    ScalingMode getScalingMode() const { return scalingMode_; }
    
    /**
     * Enable/disable video display
     * @param enabled Whether video should be displayed
     */
    void setEnabled(bool enabled);
    
    /**
     * Check if video display is enabled
     * @return true if enabled, false if disabled
     */
    bool isEnabled() const { return enabled_.load(); }
    
    /**
     * Set refresh rate for video updates
     * @param fps Frames per second for display updates
     */
    void setRefreshRate(double fps);
    
    /**
     * Get current refresh rate
     * @return Refresh rate in FPS
     */
    double getRefreshRate() const { return refreshRate_.load(); }
    
    /**
     * Force immediate repaint with latest frame
     */
    void updateNow();
    
    // ========================================================================
    // Video Information
    // ========================================================================
    
    /**
     * Get original video dimensions
     * @return Rectangle with video width and height
     */
    juce::Rectangle<int> getVideoDimensions() const;
    
    /**
     * Get currently displayed frame timestamp
     * @return Timestamp of current frame in seconds
     */
    double getCurrentFrameTimestamp() const { return currentFrameTimestamp_.load(); }
    
    /**
     * Check if video has frames available
     * @return true if frames are available for display
     */
    bool hasVideoFrames() const;
    
    /**
     * Get current frame as image (for screenshots, etc.)
     * @return Current frame as JUCE Image
     */
    juce::Image getCurrentFrameImage() const;
    
    // ========================================================================
    // Display Statistics
    // ========================================================================
    
    /**
     * Get frames displayed since last reset
     * @return Number of frames displayed
     */
    uint64_t getFramesDisplayed() const { return framesDisplayed_.load(); }
    
    /**
     * Get frames dropped since last reset
     * @return Number of frames dropped for sync
     */
    uint64_t getFramesDropped() const;
    
    /**
     * Get current buffer level
     * @return Buffer level from 0.0 to 1.0
     */
    double getBufferLevel() const;
    
    /**
     * Reset display statistics
     */
    void resetStatistics();
    
    // ========================================================================
    // Advanced Display Options
    // ========================================================================
    
    /**
     * Set background color when video doesn't fill component
     * @param color Background color
     */
    void setBackgroundColor(juce::Colour color) { backgroundColor_ = color; }
    
    /**
     * Get background color
     * @return Current background color
     */
    juce::Colour getBackgroundColor() const { return backgroundColor_; }
    
    /**
     * Enable/disable smoothing for scaled video
     * @param enabled Whether to use smooth scaling
     */
    void setSmoothScaling(bool enabled) { smoothScaling_ = enabled; }
    
    /**
     * Check if smooth scaling is enabled
     * @return true if smooth scaling is enabled
     */
    bool isSmoothScaling() const { return smoothScaling_; }
    
    /**
     * Set custom zoom level (for ActualSize mode)
     * @param zoomFactor Zoom factor (1.0 = 100%)
     */
    void setZoomFactor(double zoomFactor);
    
    /**
     * Get current zoom factor
     * @return Current zoom factor
     */
    double getZoomFactor() const { return zoomFactor_.load(); }

private:
    // References and configuration
    VideoBuffer& videoBuffer_;
    const MediaInfo& mediaInfo_;
    
    // Display state
    std::atomic<double> currentPosition_{0.0};
    std::atomic<double> currentFrameTimestamp_{-1.0};
    std::atomic<bool> enabled_{true};
    std::atomic<double> refreshRate_{30.0};
    std::atomic<double> zoomFactor_{1.0};
    
    // Display settings
    ScalingMode scalingMode_{ScalingMode::Fit};
    juce::Colour backgroundColor_{juce::Colours::black};
    bool smoothScaling_{true};
    double tolerance_{0.040};
    
    // Current frame and rendering
    mutable std::mutex frameMutex_;
    VideoFrame currentFrame_;
    bool hasCurrentFrame_{false};
    juce::Rectangle<float> videoRect_;
    juce::AffineTransform transform_;
    
    // Statistics
    std::atomic<uint64_t> framesDisplayed_{0};
    TimeUtils::TimePoint lastFrameTime_;
    
    // Mouse interaction (for panning in ActualSize mode)
    juce::Point<float> panOffset_{0.0f, 0.0f};
    juce::Point<int> lastMousePosition_;
    bool isDragging_{false};
    
    // ========================================================================
    // juce::Timer Implementation
    // ========================================================================
    
    /**
     * Timer callback for regular frame updates
     */
    void timerCallback() override;
    
    // ========================================================================
    // Internal Methods
    // ========================================================================
    
    /**
     * Update current frame from video buffer
     * @return true if new frame was obtained
     */
    bool updateCurrentFrame();
    
    /**
     * Calculate video rectangle for current scaling mode
     */
    void calculateVideoRect();
    
    /**
     * Calculate transform for video rendering
     */
    void calculateTransform();
    
    /**
     * Draw the current video frame
     * @param g Graphics context to draw with
     */
    void drawVideoFrame(juce::Graphics& g);
    
    /**
     * Draw overlay information (debug mode)
     * @param g Graphics context to draw with
     */
    void drawOverlay(juce::Graphics& g);
    
    /**
     * Handle zoom gesture
     * @param zoomDelta Zoom change amount
     * @param centerPoint Center point for zoom
     */
    void handleZoom(float zoomDelta, juce::Point<float> centerPoint);
    
    /**
     * Handle pan gesture
     * @param delta Pan offset change
     */
    void handlePan(juce::Point<float> delta);
    
    /**
     * Constrain pan offset to reasonable bounds
     */
    void constrainPanOffset();
    
    /**
     * Convert component coordinates to video coordinates
     * @param componentPoint Point in component space
     * @return Point in video space
     */
    juce::Point<float> componentToVideoCoordinates(juce::Point<float> componentPoint) const;
    
    /**
     * Convert video coordinates to component coordinates
     * @param videoPoint Point in video space
     * @return Point in component space
     */
    juce::Point<float> videoToComponentCoordinates(juce::Point<float> videoPoint) const;
    
    /**
     * Update timer interval based on refresh rate
     */
    void updateTimerInterval();
    
    /**
     * Get video stream info from media info
     */
    const StreamInfo* getVideoStreamInfo() const;
};

/**
 * Simple component that shows a message when no video is available
 */
class NoVideoComponent : public juce::Component {
public:
    NoVideoComponent(const juce::String& message = "No video available");
    ~NoVideoComponent() override = default;
    
    void paint(juce::Graphics& g) override;
    void setMessage(const juce::String& message);
    
private:
    juce::String message_;
    juce::Colour textColor_{juce::Colours::white};
    juce::Colour backgroundColor_{juce::Colours::black};
};

} // namespace cb_ffmpeg 