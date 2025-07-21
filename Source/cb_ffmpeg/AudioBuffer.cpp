#include "AudioBuffer.h"
#include <algorithm>
#include <cstring>

namespace cb_ffmpeg {

// ============================================================================
// AudioBuffer Implementation
// ============================================================================

AudioBuffer::AudioBuffer(size_t bufferSizeMs, int sampleRate, int numChannels)
    : bufferSizeMs_(bufferSizeMs)
    , sampleRate_(sampleRate) 
    , numChannels_(numChannels)
{
    reset(bufferSizeMs, sampleRate, numChannels);
}

AudioBuffer::~AudioBuffer() {
    clear();
}

bool AudioBuffer::push(AudioFrame&& frame) {
    if (frame.isEmpty()) {
        return false;
    }
    
    // Check if we have space
    if (getFreeSpaceInternal() == 0) {
        overrunCount_.fetch_add(1);
        return false;
    }
    
    // Get write position
    size_t writePos = writeIndex_.load();
    
    // Move frame into buffer
    ringBuffer_[writePos] = std::move(frame);
    
    // Update write index atomically
    writeIndex_.store(nextIndex(writePos));
    
    return true;
}

bool AudioBuffer::pop(AudioFrame& frame) {
    // Check if we have data
    size_t available = getAvailableFramesInternal();
    if (available == 0) {
        underrunCount_.fetch_add(1);
        juce::Logger::writeToLog("AudioBuffer: pop() failed - no frames available (buffer empty)");
        return false;
    }
    
    // Get read position
    size_t readPos = readIndex_.load();
    
    // Move frame from buffer
    frame = std::move(ringBuffer_[readPos]);
    
    // Update read index atomically
    readIndex_.store(nextIndex(readPos));
    
    juce::Logger::writeToLog("AudioBuffer: pop() success - consumed frame, " + juce::String(available - 1) + 
                            " frames remaining, buffer level now: " + juce::String(getBufferLevel() * 100, 1) + "%");
    
    return true;
}

size_t AudioBuffer::read(float* outputBuffer, size_t numSamples, int numChannels) {
    if (!outputBuffer || numSamples == 0 || numChannels == 0) {
        return 0;
    }
    
    size_t totalSamplesRead = 0;
    size_t totalSamplesNeeded = numSamples * numChannels;
    
    // Ensure internal buffer is large enough
    ensureInternalBufferSize(totalSamplesNeeded);
    
    while (totalSamplesRead < totalSamplesNeeded) {
        // Check if we need a new frame
        if (!hasPartialFrame_.load() || internalBufferPos_.load() >= internalBufferValidSamples_.load()) {
            // Try to get next frame
            AudioFrame nextFrame;
            if (!pop(nextFrame)) {
                // No more frames available
                break;
            }
            
            // Copy frame data to internal buffer
            size_t frameTotalSamples = nextFrame.getTotalSamples();
            if (frameTotalSamples > 0) {
                std::memcpy(internalBuffer_.get(), nextFrame.data.get(), frameTotalSamples * sizeof(float));
                internalBufferValidSamples_.store(frameTotalSamples);
                internalBufferPos_.store(0);
                hasPartialFrame_.store(true);
            }
        }
        
        // Copy from internal buffer to output
        size_t currentPos = internalBufferPos_.load();
        size_t validSamples = internalBufferValidSamples_.load();
        size_t availableSamples = validSamples - currentPos;
        size_t samplesToRead = std::min(availableSamples, totalSamplesNeeded - totalSamplesRead);
        
        if (samplesToRead > 0) {
            std::memcpy(outputBuffer + totalSamplesRead, 
                       internalBuffer_.get() + currentPos, 
                       samplesToRead * sizeof(float));
            
            totalSamplesRead += samplesToRead;
            internalBufferPos_.store(currentPos + samplesToRead);
        }
        
        // Check if we've consumed the entire frame
        if (internalBufferPos_.load() >= internalBufferValidSamples_.load()) {
            hasPartialFrame_.store(false);
        }
    }
    
    // Convert back to samples per channel
    return totalSamplesRead / numChannels;
}

void AudioBuffer::advance(size_t numSamples) {
    if (numSamples == 0) {
        return;
    }
    
    size_t totalSamples = numSamples * numChannels_.load();
    size_t currentPos = internalBufferPos_.load();
    size_t validSamples = internalBufferValidSamples_.load();
    
    // Advance position within current frame
    size_t newPos = std::min(currentPos + totalSamples, validSamples);
    internalBufferPos_.store(newPos);
    
    // Check if we need to advance to next frame
    while (newPos >= validSamples && hasPartialFrame_.load()) {
        size_t remainingSamples = (currentPos + totalSamples) - validSamples;
        
        // Get next frame
        AudioFrame nextFrame;
        if (!pop(nextFrame)) {
            hasPartialFrame_.store(false);
            break;
        }
        
        // Setup new frame in internal buffer
        size_t frameTotalSamples = nextFrame.getTotalSamples();
        if (frameTotalSamples > 0) {
            ensureInternalBufferSize(frameTotalSamples);
            std::memcpy(internalBuffer_.get(), nextFrame.data.get(), frameTotalSamples * sizeof(float));
            internalBufferValidSamples_.store(frameTotalSamples);
            
            // Position within new frame
            newPos = std::min(remainingSamples, frameTotalSamples);
            internalBufferPos_.store(newPos);
            currentPos = 0;
            validSamples = frameTotalSamples;
            
            if (newPos >= frameTotalSamples) {
                hasPartialFrame_.store(false);
            }
        } else {
            hasPartialFrame_.store(false);
            break;
        }
    }
}

void AudioBuffer::clear() {
    // Reset indices
    writeIndex_.store(0);
    readIndex_.store(0);
    
    // Clear ring buffer
    for (auto& frame : ringBuffer_) {
        frame = AudioFrame{}; // Reset to empty frame
    }
    
    // Reset internal buffer state
    internalBufferPos_.store(0);
    internalBufferValidSamples_.store(0);
    hasPartialFrame_.store(false);
}

void AudioBuffer::reset(size_t bufferSizeMs, int sampleRate, int numChannels) {
    // Update configuration
    bufferSizeMs_.store(bufferSizeMs);
    sampleRate_.store(sampleRate);
    numChannels_.store(numChannels);
    
    // Calculate new capacity
    size_t newCapacity = calculateCapacity();
    
    // Resize ring buffer if needed
    if (newCapacity != capacity_.load()) {
        clear();
        ringBuffer_.resize(newCapacity);
        capacity_.store(newCapacity);
    }
    
    // Ensure internal buffer exists
    ensureInternalBufferSize(1024); // Start with reasonable size
}

void AudioBuffer::resetStatistics() {
    underrunCount_.store(0);
    overrunCount_.store(0);
}

size_t AudioBuffer::calculateCapacity() const {
    // Calculate frames needed for the buffer duration
    // Assume average frame size of 1024 samples for calculation
    double bufferDurationSec = bufferSizeMs_.load() / 1000.0;
    int rate = sampleRate_.load();
    
    if (rate <= 0) {
        return 32; // Minimum capacity
    }
    
    size_t samplesNeeded = static_cast<size_t>(bufferDurationSec * rate);
    size_t framesNeeded = (samplesNeeded + 1023) / 1024; // Round up, assume 1024 samples per frame
    
    // Ensure minimum capacity and make it power of 2 for better performance
    size_t capacity = std::max(framesNeeded, size_t(8));
    
    // Round up to next power of 2
    size_t powerOf2 = 1;
    while (powerOf2 < capacity) {
        powerOf2 <<= 1;
    }
    
    return powerOf2;
}

void AudioBuffer::ensureInternalBufferSize(size_t requiredSamples) const {
    size_t currentSize = internalBufferSize_.load();
    
    if (requiredSamples > currentSize) {
        // Allocate larger buffer (round up to next multiple of 1024)
        size_t newSize = ((requiredSamples + 1023) / 1024) * 1024;
        
        auto newBuffer = std::make_unique<float[]>(newSize);
        
        // Copy existing data if any
        if (internalBuffer_ && currentSize > 0) {
            size_t validSamples = std::min(currentSize, internalBufferValidSamples_.load());
            if (validSamples > 0) {
                std::memcpy(newBuffer.get(), internalBuffer_.get(), validSamples * sizeof(float));
            }
        }
        
        // Update buffer
        internalBuffer_ = std::move(newBuffer);
        internalBufferSize_.store(newSize);
    }
}

} // namespace cb_ffmpeg 