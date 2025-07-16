#include "VideoBuffer.h"
#include <algorithm>

namespace cb_ffmpeg {

// ============================================================================
// VideoBuffer Implementation
// ============================================================================

VideoBuffer::VideoBuffer(size_t maxFrames, bool enableFrameDropping)
    : maxFrames_(maxFrames)
    , frameDropping_(enableFrameDropping)
{
}

VideoBuffer::~VideoBuffer() {
    clear();
}

bool VideoBuffer::push(VideoFrame&& frame) {
    if (frame.isEmpty()) {
        return false;
    }
    
    std::lock_guard<std::mutex> lock(bufferMutex_);
    
    // Check if buffer is full
    if (frameQueue_.size() >= maxFrames_.load()) {
        if (frameDropping_.load()) {
            // Drop oldest frames to make room
            makeRoom();
        } else {
            // Buffer full and dropping disabled
            overrunCount_.fetch_add(1);
            return false;
        }
    }
    
    // Insert frame in timestamp order
    auto insertPos = std::upper_bound(frameQueue_.begin(), frameQueue_.end(), frame,
        [](const VideoFrame& a, const VideoFrame& b) {
            return a.timestamp < b.timestamp;
        });
    
    frameQueue_.insert(insertPos, std::move(frame));
    return true;
}

bool VideoBuffer::getFrameAtTime(double currentTime, VideoFrame& frame, double tolerance) {
    std::lock_guard<std::mutex> lock(bufferMutex_);
    
    if (frameQueue_.empty()) {
        return false;
    }
    
    // Find frame closest to current time within tolerance
    auto bestFrame = frameQueue_.end();
    double bestTimeDiff = std::numeric_limits<double>::max();
    
    for (auto it = frameQueue_.begin(); it != frameQueue_.end(); ++it) {
        double timeDiff = std::abs(it->timestamp - currentTime);
        
        if (timeDiff <= tolerance && timeDiff < bestTimeDiff) {
            bestFrame = it;
            bestTimeDiff = timeDiff;
        }
        
        // If frame is too far in the future, stop searching
        if (it->timestamp > currentTime + tolerance) {
            break;
        }
    }
    
    if (bestFrame != frameQueue_.end()) {
        frame = std::move(*bestFrame);
        frameQueue_.erase(bestFrame);
        
        // Drop any frames older than the one we just returned
        dropFramesOlderThan(frame.timestamp);
        
        return true;
    }
    
    return false;
}

bool VideoBuffer::peekNext(VideoFrame& frame) {
    std::lock_guard<std::mutex> lock(bufferMutex_);
    
    if (frameQueue_.empty()) {
        return false;
    }
    
    // Copy the first frame (don't move it)
    frame = frameQueue_.front();
    return true;
}

size_t VideoBuffer::dropFramesOlderThan(double timestamp) {
    std::lock_guard<std::mutex> lock(bufferMutex_);
    return dropOldFramesInternal(timestamp);
}

size_t VideoBuffer::dropToMostRecent() {
    std::lock_guard<std::mutex> lock(bufferMutex_);
    
    if (frameQueue_.empty()) {
        return 0;
    }
    
    size_t droppedCount = frameQueue_.size() - 1;
    
    // Keep only the last frame
    VideoFrame lastFrame = std::move(frameQueue_.back());
    frameQueue_.clear();
    frameQueue_.push_back(std::move(lastFrame));
    
    framesDropped_.fetch_add(droppedCount);
    return droppedCount;
}

void VideoBuffer::clear() {
    std::lock_guard<std::mutex> lock(bufferMutex_);
    frameQueue_.clear();
}

void VideoBuffer::reset(size_t maxFrames, bool enableFrameDropping) {
    std::lock_guard<std::mutex> lock(bufferMutex_);
    
    maxFrames_.store(maxFrames);
    frameDropping_.store(enableFrameDropping);
    
    // If new max is smaller, trim the buffer
    while (frameQueue_.size() > maxFrames) {
        frameQueue_.pop_front();
        framesDropped_.fetch_add(1);
    }
}

double VideoBuffer::getEarliestTimestamp() const {
    std::lock_guard<std::mutex> lock(bufferMutex_);
    return frameQueue_.empty() ? -1.0 : frameQueue_.front().timestamp;
}

double VideoBuffer::getLatestTimestamp() const {
    std::lock_guard<std::mutex> lock(bufferMutex_);
    return frameQueue_.empty() ? -1.0 : frameQueue_.back().timestamp;
}

double VideoBuffer::getBufferDuration() const {
    std::lock_guard<std::mutex> lock(bufferMutex_);
    
    if (frameQueue_.size() < 2) {
        return 0.0;
    }
    
    return frameQueue_.back().timestamp - frameQueue_.front().timestamp;
}

bool VideoBuffer::hasFrameForTime(double timestamp, double tolerance) const {
    std::lock_guard<std::mutex> lock(bufferMutex_);
    
    for (const auto& frame : frameQueue_) {
        if (std::abs(frame.timestamp - timestamp) <= tolerance) {
            return true;
        }
        
        // Stop searching if we've gone too far
        if (frame.timestamp > timestamp + tolerance) {
            break;
        }
    }
    
    return false;
}

size_t VideoBuffer::getFramesInTimeRange(double startTime, double endTime) const {
    std::lock_guard<std::mutex> lock(bufferMutex_);
    
    size_t count = 0;
    for (const auto& frame : frameQueue_) {
        if (frame.timestamp >= startTime && frame.timestamp <= endTime) {
            count++;
        }
    }
    
    return count;
}

void VideoBuffer::resetStatistics() {
    framesDropped_.store(0);
    overrunCount_.store(0);
}

std::deque<VideoFrame>::iterator VideoBuffer::findFrameAtTime(double timestamp, double tolerance) {
    for (auto it = frameQueue_.begin(); it != frameQueue_.end(); ++it) {
        if (std::abs(it->timestamp - timestamp) <= tolerance) {
            return it;
        }
        
        // Stop searching if we've gone too far
        if (it->timestamp > timestamp + tolerance) {
            break;
        }
    }
    
    return frameQueue_.end();
}

size_t VideoBuffer::dropOldFramesInternal(double timestamp) {
    size_t droppedCount = 0;
    
    while (!frameQueue_.empty() && frameQueue_.front().timestamp < timestamp) {
        frameQueue_.pop_front();
        droppedCount++;
    }
    
    if (droppedCount > 0) {
        framesDropped_.fetch_add(droppedCount);
    }
    
    return droppedCount;
}

bool VideoBuffer::shouldDropFrames() const {
    return frameDropping_.load() && frameQueue_.size() >= maxFrames_.load();
}

void VideoBuffer::makeRoom() {
    // Drop oldest frames until we have space
    size_t targetSize = maxFrames_.load() * 3 / 4; // Drop to 75% capacity
    size_t droppedCount = 0;
    
    while (frameQueue_.size() > targetSize && !frameQueue_.empty()) {
        frameQueue_.pop_front();
        droppedCount++;
    }
    
    if (droppedCount > 0) {
        framesDropped_.fetch_add(droppedCount);
    }
}

// ============================================================================
// VideoFramePool Implementation
// ============================================================================

VideoFramePool::VideoFramePool(size_t poolSize, int frameWidth, int frameHeight)
    : maxPoolSize_(poolSize)
    , defaultWidth_(frameWidth)
    , defaultHeight_(frameHeight)
{
    // Pre-allocate some frames
    for (size_t i = 0; i < std::min(poolSize, size_t(4)); ++i) {
        availableFrames_.push_back(createFrame(frameWidth, frameHeight));
    }
}

VideoFramePool::~VideoFramePool() {
    clear();
}

VideoFrame VideoFramePool::getFrame(int width, int height) {
    std::lock_guard<std::mutex> lock(poolMutex_);
    
    // Look for a reusable frame
    for (auto it = availableFrames_.begin(); it != availableFrames_.end(); ++it) {
        if (isFrameReusable(*it, width, height)) {
            VideoFrame frame = std::move(*it);
            availableFrames_.erase(it);
            
            // Reset frame properties but keep the image
            frame.timestamp = 0.0;
            frame.duration = 0.0;
            frame.width = width;
            frame.height = height;
            frame.format = PixelFormat::RGBA;
            frame.isKeyFrame = false;
            frame.isEndOfStream = false;
            
            return frame;
        }
    }
    
    // No reusable frame found, create new one
    return createFrame(width, height);
}

void VideoFramePool::returnFrame(VideoFrame&& frame) {
    if (frame.isEmpty()) {
        return;
    }
    
    std::lock_guard<std::mutex> lock(poolMutex_);
    
    // Only return to pool if we haven't exceeded capacity
    if (availableFrames_.size() < maxPoolSize_) {
        availableFrames_.push_back(std::move(frame));
    }
    // If pool is full, frame will be destroyed automatically
}

void VideoFramePool::resize(size_t newSize) {
    std::lock_guard<std::mutex> lock(poolMutex_);
    
    maxPoolSize_ = newSize;
    
    // Trim pool if it's too large
    while (availableFrames_.size() > newSize) {
        availableFrames_.pop_back();
    }
}

void VideoFramePool::clear() {
    std::lock_guard<std::mutex> lock(poolMutex_);
    availableFrames_.clear();
}

size_t VideoFramePool::getPoolSize() const {
    std::lock_guard<std::mutex> lock(poolMutex_);
    return maxPoolSize_;
}

size_t VideoFramePool::getAvailableFrames() const {
    std::lock_guard<std::mutex> lock(poolMutex_);
    return availableFrames_.size();
}

size_t VideoFramePool::getUsedFrames() const {
    return maxPoolSize_ - getAvailableFrames();
}

VideoFrame VideoFramePool::createFrame(int width, int height) {
    VideoFrame frame;
    frame.width = width;
    frame.height = height;
    frame.format = PixelFormat::RGBA;
    frame.image = juce::Image(juce::Image::ARGB, width, height, true);
    return frame;
}

bool VideoFramePool::isFrameReusable(const VideoFrame& frame, int width, int height) const {
    if (frame.isEmpty()) {
        return false;
    }
    
    // Frame can be reused if dimensions match or are larger
    return frame.image.getWidth() >= width && frame.image.getHeight() >= height;
}

} // namespace cb_ffmpeg 