#pragma once

#include "MediaReaderTypes.h"
#include <atomic>
#include <vector>
#include <memory>
#include <deque>
#include <mutex>

namespace cb_ffmpeg {

/**
 * Thread-safe FIFO buffer for video frames with timestamp management
 * 
 * Unlike the audio buffer, video frames can vary significantly in size and
 * need timestamp-based synchronization, so this uses a different approach
 * with proper frame dropping and sync capabilities.
 */
class VideoBuffer {
public:
    /**
     * Constructor
     * @param maxFrames Maximum number of frames to buffer
     * @param enableFrameDropping Whether to allow frame dropping for sync
     */
    VideoBuffer(size_t maxFrames = 30, bool enableFrameDropping = true);
    
    /**
     * Destructor
     */
    ~VideoBuffer();
    
    // Disable copy and assignment
    VideoBuffer(const VideoBuffer&) = delete;
    VideoBuffer& operator=(const VideoBuffer&) = delete;
    
    /**
     * Push a video frame into the buffer (called by decoder thread)
     * @param frame Video frame to push (will be moved)
     * @return true if successful, false if buffer is full
     */
    bool push(VideoFrame&& frame);
    
    /**
     * Get the next frame that should be displayed at the given timestamp
     * @param currentTime Current playback time in seconds
     * @param frame Reference to store the frame
     * @param tolerance Time tolerance for frame selection in seconds
     * @return true if frame found, false if no suitable frame
     */
    bool getFrameAtTime(double currentTime, VideoFrame& frame, double tolerance = 0.040);
    
    /**
     * Peek at the next frame without removing it
     * @param frame Reference to store the frame
     * @return true if frame available, false if buffer empty
     */
    bool peekNext(VideoFrame& frame);
    
    /**
     * Get the timestamp of the next frame
     * @return timestamp in seconds, or -1.0 if no frame available
     */
    double getNextFrameTimestamp() const;
    
    /**
     * Drop frames older than the given timestamp
     * @param timestamp Timestamp in seconds
     * @return Number of frames dropped
     */
    size_t dropFramesOlderThan(double timestamp);
    
    /**
     * Drop all frames except the most recent
     * @return Number of frames dropped
     */
    size_t dropToMostRecent();
    
    /**
     * Clear all buffered frames
     */
    void clear();
    
    /**
     * Reset buffer configuration
     * @param maxFrames New maximum number of frames
     * @param enableFrameDropping Whether to enable frame dropping
     */
    void reset(size_t maxFrames, bool enableFrameDropping);
    
    /**
     * Buffer statistics
     */
    double getBufferLevel() const;        // 0.0 to 1.0
    size_t getFrameCount() const;         // Number of frames currently buffered
    size_t getMaxFrames() const;          // Maximum buffer capacity
    bool isEmpty() const;
    bool isFull() const;
    
    /**
     * Frame timing information
     */
    double getEarliestTimestamp() const;  // Timestamp of oldest frame
    double getLatestTimestamp() const;    // Timestamp of newest frame
    double getBufferDuration() const;     // Time span of buffered frames
    
    /**
     * Synchronization helpers
     */
    bool hasFrameForTime(double timestamp, double tolerance = 0.040) const;
    size_t getFramesInTimeRange(double startTime, double endTime) const;
    
    /**
     * Configuration
     */
    void setFrameDropping(bool enable) { frameDropping_.store(enable); }
    bool isFrameDroppingEnabled() const { return frameDropping_.load(); }
    
    /**
     * Statistics
     */
    uint64_t getFramesDropped() const { return framesDropped_.load(); }
    uint64_t getOverrunCount() const { return overrunCount_.load(); }
    void resetStatistics();

private:
    // Configuration
    std::atomic<size_t> maxFrames_{30};
    std::atomic<bool> frameDropping_{true};
    
    // Frame storage
    mutable std::mutex bufferMutex_;
    std::deque<VideoFrame> frameQueue_;
    
    // Statistics
    mutable std::atomic<uint64_t> framesDropped_{0};
    mutable std::atomic<uint64_t> overrunCount_{0};
    
    /**
     * Internal helper to find frame at specific time (requires lock)
     */
    std::deque<VideoFrame>::iterator findFrameAtTime(double timestamp, double tolerance);
    
    /**
     * Internal helper to drop old frames (requires lock)
     */
    size_t dropOldFramesInternal(double timestamp);
    
    /**
     * Internal helper to check if buffer should drop frames
     */
    bool shouldDropFrames() const;
    
    /**
     * Internal helper to make room for new frame
     */
    void makeRoom();
};

/**
 * Video frame memory pool for efficient allocation
 * 
 * This class manages a pool of pre-allocated video frames to avoid
 * frequent allocation/deallocation during playback.
 */
class VideoFramePool {
public:
    /**
     * Constructor
     * @param poolSize Initial pool size
     * @param frameWidth Default frame width
     * @param frameHeight Default frame height
     */
    VideoFramePool(size_t poolSize = 10, int frameWidth = 1920, int frameHeight = 1080);
    
    /**
     * Destructor
     */
    ~VideoFramePool();
    
    // Disable copy and assignment
    VideoFramePool(const VideoFramePool&) = delete;
    VideoFramePool& operator=(const VideoFramePool&) = delete;
    
    /**
     * Get a frame from the pool
     * @param width Required frame width
     * @param height Required frame height
     * @return VideoFrame ready for use
     */
    VideoFrame getFrame(int width, int height);
    
    /**
     * Return a frame to the pool
     * @param frame Frame to return (will be moved)
     */
    void returnFrame(VideoFrame&& frame);
    
    /**
     * Resize the pool
     * @param newSize New pool size
     */
    void resize(size_t newSize);
    
    /**
     * Clear all frames in the pool
     */
    void clear();
    
    /**
     * Pool statistics
     */
    size_t getPoolSize() const;
    size_t getAvailableFrames() const;
    size_t getUsedFrames() const;

private:
    mutable std::mutex poolMutex_;
    std::vector<VideoFrame> availableFrames_;
    size_t maxPoolSize_;
    int defaultWidth_;
    int defaultHeight_;
    
    /**
     * Create a new frame with the specified dimensions
     */
    VideoFrame createFrame(int width, int height);
    
    /**
     * Check if a frame is suitable for reuse
     */
    bool isFrameReusable(const VideoFrame& frame, int width, int height) const;
};

/**
 * Inline implementations for performance-critical methods
 */

inline double VideoBuffer::getBufferLevel() const {
    std::lock_guard<std::mutex> lock(bufferMutex_);
    size_t max = maxFrames_.load();
    return max > 0 ? static_cast<double>(frameQueue_.size()) / max : 0.0;
}

inline size_t VideoBuffer::getFrameCount() const {
    std::lock_guard<std::mutex> lock(bufferMutex_);
    return frameQueue_.size();
}

inline size_t VideoBuffer::getMaxFrames() const {
    return maxFrames_.load();
}

inline bool VideoBuffer::isEmpty() const {
    std::lock_guard<std::mutex> lock(bufferMutex_);
    return frameQueue_.empty();
}

inline bool VideoBuffer::isFull() const {
    std::lock_guard<std::mutex> lock(bufferMutex_);
    return frameQueue_.size() >= maxFrames_.load();
}

inline double VideoBuffer::getNextFrameTimestamp() const {
    std::lock_guard<std::mutex> lock(bufferMutex_);
    return frameQueue_.empty() ? -1.0 : frameQueue_.front().timestamp;
}

} // namespace cb_ffmpeg 