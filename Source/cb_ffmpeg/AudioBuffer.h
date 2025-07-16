#pragma once

#include "MediaReaderTypes.h"
#include <atomic>
#include <vector>
#include <memory>

namespace cb_ffmpeg {

/**
 * Thread-safe lock-free FIFO buffer for audio frames
 * 
 * This buffer uses a lock-free ring buffer design to allow one writer thread
 * (audio decoder) and one reader thread (JUCE audio callback) to operate
 * without blocking each other.
 */
class AudioBuffer {
public:
    /**
     * Constructor
     * @param bufferSizeMs Buffer size in milliseconds
     * @param sampleRate Sample rate for size calculation
     * @param numChannels Number of audio channels
     */
    AudioBuffer(size_t bufferSizeMs = 500, int sampleRate = 44100, int numChannels = 2);
    
    /**
     * Destructor
     */
    ~AudioBuffer();
    
    // Disable copy and assignment
    AudioBuffer(const AudioBuffer&) = delete;
    AudioBuffer& operator=(const AudioBuffer&) = delete;
    
    /**
     * Push an audio frame into the buffer (called by decoder thread)
     * @param frame Audio frame to push (will be moved)
     * @return true if successful, false if buffer is full
     */
    bool push(AudioFrame&& frame);
    
    /**
     * Pop an audio frame from the buffer (called by audio thread)
     * @param frame Reference to store the popped frame
     * @return true if successful, false if buffer is empty
     */
    bool pop(AudioFrame& frame);
    
    /**
     * Read audio data without removing it from buffer
     * @param outputBuffer Pointer to output buffer
     * @param numSamples Number of samples to read per channel
     * @param numChannels Number of channels
     * @return Number of samples actually read per channel
     */
    size_t read(float* outputBuffer, size_t numSamples, int numChannels);
    
    /**
     * Advance read position after reading data
     * @param numSamples Number of samples to advance per channel
     */
    void advance(size_t numSamples);
    
    /**
     * Clear all buffered data
     */
    void clear();
    
    /**
     * Reset buffer configuration
     * @param bufferSizeMs New buffer size in milliseconds
     * @param sampleRate New sample rate
     * @param numChannels New number of channels
     */
    void reset(size_t bufferSizeMs, int sampleRate, int numChannels);
    
    /**
     * Get current buffer statistics
     */
    double getBufferLevel() const;        // 0.0 to 1.0
    size_t getAvailableFrames() const;    // Number of frames available to read
    size_t getFreeSpace() const;          // Number of frames that can be written
    size_t getCapacity() const;           // Total buffer capacity in frames
    bool isEmpty() const;
    bool isFull() const;
    
    /**
     * Get buffer configuration
     */
    int getSampleRate() const { return sampleRate_; }
    int getNumChannels() const { return numChannels_; }
    size_t getBufferSizeMs() const { return bufferSizeMs_; }
    
    /**
     * Get underrun/overrun statistics
     */
    uint64_t getUnderrunCount() const { return underrunCount_.load(); }
    uint64_t getOverrunCount() const { return overrunCount_.load(); }
    void resetStatistics();

private:
    // Buffer configuration
    std::atomic<size_t> bufferSizeMs_{500};
    std::atomic<int> sampleRate_{44100};
    std::atomic<int> numChannels_{2};
    
    // Ring buffer data
    std::vector<AudioFrame> ringBuffer_;
    std::atomic<size_t> capacity_{0};
    std::atomic<size_t> writeIndex_{0};
    std::atomic<size_t> readIndex_{0};
    
    // Statistics
    mutable std::atomic<uint64_t> underrunCount_{0};
    mutable std::atomic<uint64_t> overrunCount_{0};
    
    // Internal buffer for partial frame reading
    mutable std::unique_ptr<float[]> internalBuffer_;
    mutable std::atomic<size_t> internalBufferSize_{0};
    mutable std::atomic<size_t> internalBufferPos_{0};
    mutable std::atomic<size_t> internalBufferValidSamples_{0};
    mutable std::atomic<bool> hasPartialFrame_{false};
    
    /**
     * Calculate buffer capacity based on configuration
     */
    size_t calculateCapacity() const;
    
    /**
     * Ensure internal buffer is large enough
     */
    void ensureInternalBufferSize(size_t requiredSamples) const;
    
    /**
     * Get next index in ring buffer
     */
    size_t nextIndex(size_t index) const {
        return (index + 1) % capacity_.load();
    }
    
    /**
     * Get available frames for reading (lock-free)
     */
    size_t getAvailableFramesInternal() const {
        size_t write = writeIndex_.load();
        size_t read = readIndex_.load();
        size_t cap = capacity_.load();
        
        if (write >= read) {
            return write - read;
        } else {
            return cap - read + write;
        }
    }
    
    /**
     * Get free space for writing (lock-free)
     */
    size_t getFreeSpaceInternal() const {
        size_t cap = capacity_.load();
        size_t available = getAvailableFramesInternal();
        return cap > available ? cap - available - 1 : 0; // -1 to distinguish full from empty
    }
};

/**
 * Inline implementations for performance-critical methods
 */

inline double AudioBuffer::getBufferLevel() const {
    size_t available = getAvailableFrames();
    size_t cap = getCapacity();
    return cap > 0 ? static_cast<double>(available) / cap : 0.0;
}

inline size_t AudioBuffer::getAvailableFrames() const {
    return getAvailableFramesInternal();
}

inline size_t AudioBuffer::getFreeSpace() const {
    return getFreeSpaceInternal();
}

inline size_t AudioBuffer::getCapacity() const {
    return capacity_.load();
}

inline bool AudioBuffer::isEmpty() const {
    return getAvailableFrames() == 0;
}

inline bool AudioBuffer::isFull() const {
    return getFreeSpace() == 0;
}

} // namespace cb_ffmpeg 