#include "MediaAudioSource.h"
#include <algorithm>
#include <cstring>

namespace cb_ffmpeg {

// ============================================================================
// MediaAudioSource Implementation
// ============================================================================

MediaAudioSource::MediaAudioSource(AudioBuffer& audioBuffer, const MediaInfo& mediaInfo)
    : audioBuffer_(audioBuffer)
    , mediaInfo_(mediaInfo)
{
    // Initialize channel mapping to identity
    const StreamInfo* audioStream = mediaInfo_.getAudioStream();
    if (audioStream) {
        outputChannels_ = std::min(audioStream->channels, 32); // Limit to 32 channels
        for (int i = 0; i < outputChannels_; ++i) {
            channelMapping_.push_back(i);
        }
    }
}

MediaAudioSource::~MediaAudioSource() {
    releaseResources();
}

void MediaAudioSource::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    outputSampleRate_ = sampleRate;
    samplesPerBlock_ = samplesPerBlockExpected;
    
    const StreamInfo* audioStream = mediaInfo_.getAudioStream();
    if (audioStream) {
        outputChannels_ = std::min(audioStream->channels, 32);
        
        // Check if we need resampling
        needsResampling_ = (audioStream->sampleRate != static_cast<int>(sampleRate));
        if (needsResampling_) {
            resampleRatio_ = sampleRate / audioStream->sampleRate;
            
            juce::Logger::writeToLog("MediaAudioSource: Sample rate conversion needed - File: " + 
                                    juce::String(audioStream->sampleRate) + " Hz, Output: " + 
                                    juce::String(sampleRate) + " Hz, Ratio: " + 
                                    juce::String(resampleRatio_, 4));
            
            // Reset interpolators
            for (int i = 0; i < outputChannels_; ++i) {
                interpolators_[i].reset();
            }
        } else {
            juce::Logger::writeToLog("MediaAudioSource: No resampling needed - Sample rate: " + juce::String(sampleRate) + " Hz");
        }
        
        updateResamplingConfig();
    }
    
    // Prepare temp buffers
    ensureBufferSizes(outputChannels_, samplesPerBlockExpected);
    
    isPrepared_ = true;
}

void MediaAudioSource::releaseResources() {
    isPrepared_ = false;
    tempBuffer_.setSize(0, 0);
    resampleBuffer_.setSize(0, 0);
    
    // Reset internal frame state
    hasActiveFrame_ = false;
    framePosition_ = 0;
    currentFrame_ = AudioFrame{};
}

void MediaAudioSource::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) {
    juce::Logger::writeToLog("MediaAudioSource: getNextAudioBlock called - " + juce::String(bufferToFill.numSamples) + 
                            " samples, buffer level: " + juce::String(audioBuffer_.getBufferLevel() * 100, 1) + "%");
    
    if (!isPrepared_ || !enabled_.load()) {
        juce::Logger::writeToLog("MediaAudioSource: Not prepared or not enabled");
        bufferToFill.clearActiveBufferRegion();
        return;
    }
    
    if (!hasAudioAvailable()) {
        juce::Logger::writeToLog("MediaAudioSource: No audio available, triggering underrun");
        handleUnderrun();
        bufferToFill.clearActiveBufferRegion();
        return;
    }
    
    int samplesNeeded = bufferToFill.numSamples;
    
    if (needsResampling_)
    {
        // Fill temp buffer with source data
        int sourceSamplesNeeded = static_cast<int>(samplesNeeded / resampleRatio_) + 1;
        const int channels = std::min(bufferToFill.buffer->getNumChannels(), outputChannels_);
        ensureBufferSizes(channels, sourceSamplesNeeded);
        
        int sourceSamplesFilled = fillFromAudioBuffer(tempBuffer_, 0, sourceSamplesNeeded);
        
        if (sourceSamplesFilled > 0) {
            // Resample to output buffer
            ensureBufferSizes(channels, samplesNeeded);
            if (resampleAudio(tempBuffer_, resampleBuffer_)) {
                // Copy resampled data to output
                for (int ch = 0; ch < channels; ++ch) {
                    bufferToFill.buffer->copyFrom(ch, bufferToFill.startSample,
                                                resampleBuffer_, ch, 0, samplesNeeded);
                }
            } else {
                bufferToFill.clearActiveBufferRegion();
                return;
            }
        } else {
            bufferToFill.clearActiveBufferRegion();
            return;
        }
    }
    else
    {
        // Direct copy without resampling
        int samplesFilled = fillFromAudioBuffer(*bufferToFill.buffer, bufferToFill.startSample, samplesNeeded);
        
        // Clear any unfilled samples
        if (samplesFilled < samplesNeeded)
        {
            const int channels = std::min(bufferToFill.buffer->getNumChannels(), outputChannels_);
            for (int ch = 0; ch < channels; ++ch)
            {
                bufferToFill.buffer->clear(ch, bufferToFill.startSample + samplesFilled,
                                         samplesNeeded - samplesFilled);
            }
        }
    }
    
    // Apply gain
    float gain = static_cast<float>(masterGain_.load());
    if (gain != 1.0f) {
        applyGain(*bufferToFill.buffer, gain);
    }
    
    // Apply channel mapping if needed
    if (useChannelMapping_) {
        applyChannelMapping(*bufferToFill.buffer);
    }
    
    // Update position
    double duration = static_cast<double>(samplesNeeded) / outputSampleRate_;
    currentPosition_.store(currentPosition_.load() + duration);
    
    // Update statistics
    samplesProcessed_.fetch_add(samplesNeeded);
}

void MediaAudioSource::setCurrentPosition(double positionInSeconds) {
    currentPosition_.store(positionInSeconds);
}

void MediaAudioSource::setChannelMapping(const std::vector<int>& channelMap) {
    std::lock_guard<std::mutex> lock(channelMutex_);
    
    channelMapping_ = channelMap;
    useChannelMapping_ = !channelMap.empty() && channelMap.size() <= 32;
    
    // Validate channel mapping
    if (useChannelMapping_) {
        for (int mapping : channelMap) {
            if (mapping < 0 || mapping >= outputChannels_) {
                useChannelMapping_ = false;
                break;
            }
        }
    }
}

double MediaAudioSource::getBufferLevel() const {
    return audioBuffer_.getBufferLevel();
}

uint64_t MediaAudioSource::getUnderrunCount() const {
    return underrunCount_.load();
}

void MediaAudioSource::resetStatistics() {
    underrunCount_.store(0);
    samplesProcessed_.store(0);
    audioBuffer_.resetStatistics();
}

bool MediaAudioSource::hasAudioAvailable() const {
    return !audioBuffer_.isEmpty();
}

int MediaAudioSource::fillFromAudioBuffer(juce::AudioBuffer<float>& output, int startSample, int numSamples) {
    if (numSamples <= 0) {
        return 0;
    }
    
    int totalSamplesFilled = 0;
    int channels = std::min(output.getNumChannels(), outputChannels_);
    
    while (totalSamplesFilled < numSamples) {
        // Get next frame if needed
        if (!hasActiveFrame_ || framePosition_ >= currentFrame_.numSamples) {
            juce::Logger::writeToLog("MediaAudioSource: Need new frame, attempting pop from buffer...");
            if (!audioBuffer_.pop(currentFrame_)) {
                // No more frames available
                juce::Logger::writeToLog("MediaAudioSource: Failed to pop frame from buffer");
                break;
            }
            
            if (currentFrame_.isEmpty()) {
                juce::Logger::writeToLog("MediaAudioSource: Got empty frame, continuing...");
                continue;
            }
            
            juce::Logger::writeToLog("MediaAudioSource: Successfully got frame with " + juce::String(currentFrame_.numSamples) + 
                                    " samples, " + juce::String(currentFrame_.numChannels) + " channels");
            hasActiveFrame_ = true;
            framePosition_ = 0;
        }
        
        // Calculate how many samples we can copy from current frame
        size_t remainingInFrame = currentFrame_.numSamples - framePosition_;
        int samplesToCopy = std::min(static_cast<int>(remainingInFrame), 
                                   numSamples - totalSamplesFilled);
        
        // Copy samples from frame to output buffer
        int convertedSamples = convertFrameToBuffer(currentFrame_, output, 
                                                  startSample + totalSamplesFilled, 
                                                  samplesToCopy, framePosition_);
        
        if (convertedSamples > 0) {
            totalSamplesFilled += convertedSamples;
            framePosition_ += convertedSamples;
        } else {
            // Conversion failed, mark frame as consumed
            hasActiveFrame_ = false;
            framePosition_ = 0;
        }
    }
    
    return totalSamplesFilled;
}

void MediaAudioSource::applyGain(juce::AudioBuffer<float>& buffer, float gain) {
    if (gain == 1.0f) {
        return;
    }
    
    for (int ch = 0; ch < buffer.getNumChannels(); ++ch) {
        buffer.applyGain(ch, 0, buffer.getNumSamples(), gain);
    }
}

void MediaAudioSource::applyChannelMapping(juce::AudioBuffer<float>& buffer) {
    std::lock_guard<std::mutex> lock(channelMutex_);
    
    if (!useChannelMapping_ || channelMapping_.empty()) {
        return;
    }
    
    // Create temporary buffer for remapped channels
    juce::AudioBuffer<float> tempBuffer(static_cast<int>(channelMapping_.size()), buffer.getNumSamples());
    
    // Apply channel mapping
    for (size_t outputCh = 0; outputCh < channelMapping_.size(); ++outputCh) {
        int inputCh = channelMapping_[outputCh];
        if (inputCh >= 0 && inputCh < buffer.getNumChannels()) {
            tempBuffer.copyFrom(static_cast<int>(outputCh), 0, buffer, inputCh, 0, buffer.getNumSamples());
        } else {
            tempBuffer.clear(static_cast<int>(outputCh), 0, buffer.getNumSamples());
        }
    }
    
    // Copy back to original buffer
    int channelsToCopy = std::min(buffer.getNumChannels(), tempBuffer.getNumChannels());
    for (int ch = 0; ch < channelsToCopy; ++ch) {
        buffer.copyFrom(ch, 0, tempBuffer, ch, 0, buffer.getNumSamples());
    }
}

bool MediaAudioSource::resampleAudio(const juce::AudioBuffer<float>& input, juce::AudioBuffer<float>& output) {
    if (!needsResampling_ || resampleRatio_ <= 0.0) {
        return false;
    }
    
    int inputSamples = input.getNumSamples();
    int outputSamples = output.getNumSamples();
    int channels = std::min(input.getNumChannels(), output.getNumChannels());
    
    // Use JUCE's LagrangeInterpolator for resampling
    for (int ch = 0; ch < channels; ++ch) {
        const float* inputData = input.getReadPointer(ch);
        float* outputData = output.getWritePointer(ch);
        
        interpolators_[ch].process(resampleRatio_, inputData, outputData, outputSamples, inputSamples, 0);
    }
    
    return true;
}

void MediaAudioSource::handleUnderrun() {
    underrunCount_.fetch_add(1);
    
    // Reset active frame state on underrun
    hasActiveFrame_ = false;
    framePosition_ = 0;
}

int MediaAudioSource::convertFrameToBuffer(const AudioFrame& frame, juce::AudioBuffer<float>& output, 
                                         int startSample, int numSamples, size_t frameOffset) {
    if (frame.isEmpty() || !frame.data || numSamples <= 0) {
        return 0;
    }
    
    int channels = std::min(output.getNumChannels(), frame.numChannels);
    int samplesToCopy = std::min(numSamples, static_cast<int>(frame.numSamples - frameOffset));
    
    if (samplesToCopy <= 0 || channels <= 0) {
        return 0;
    }
    
    // Copy interleaved audio data to JUCE buffer
    const float* sourceData = frame.data.get() + (frameOffset * frame.numChannels);
    
    for (int ch = 0; ch < channels; ++ch) {
        float* destData = output.getWritePointer(ch, startSample);
        
        // De-interleave channel data
        for (int sample = 0; sample < samplesToCopy; ++sample) {
            destData[sample] = sourceData[sample * frame.numChannels + ch];
        }
    }
    
    return samplesToCopy;
}

bool MediaAudioSource::needsSampleRateConversion() const {
    const StreamInfo* audioStream = mediaInfo_.getAudioStream();
    if (!audioStream) {
        return false;
    }
    
    return audioStream->sampleRate != static_cast<int>(outputSampleRate_);
}

void MediaAudioSource::updateResamplingConfig() {
    const StreamInfo* audioStream = mediaInfo_.getAudioStream();
    if (!audioStream) {
        needsResampling_ = false;
        return;
    }
    
    needsResampling_ = needsSampleRateConversion();
    
    if (needsResampling_) {
        resampleRatio_ = outputSampleRate_ / audioStream->sampleRate;
        
        // Reset interpolators for clean resampling
        for (int i = 0; i < outputChannels_; ++i) {
            interpolators_[i].reset();
        }
    }
}

void MediaAudioSource::ensureBufferSizes(int numChannels, int numSamples) {
    // Ensure temp buffer is large enough
    if (tempBuffer_.getNumChannels() < numChannels || tempBuffer_.getNumSamples() < numSamples) {
        tempBuffer_.setSize(numChannels, numSamples, false, true, true);
    }
    
    // Ensure resample buffer is large enough
    if (resampleBuffer_.getNumChannels() < numChannels || resampleBuffer_.getNumSamples() < numSamples) {
        resampleBuffer_.setSize(numChannels, numSamples, false, true, true);
    }
}

} // namespace cb_ffmpeg 