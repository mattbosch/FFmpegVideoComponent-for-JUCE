#pragma once

#include "MediaReaderTypes.h"
#include "AudioBuffer.h"
#include <atomic>
#include <mutex>

namespace cb_ffmpeg {

/**
 * JUCE AudioSource implementation that reads from MediaReader's AudioBuffer
 * 
 * This class provides the bridge between the MediaReader's audio decoding
 * system and JUCE's audio playback system, handling sample rate conversion,
 * channel mapping, and smooth audio delivery.
 */
class MediaAudioSource : public juce::AudioSource {
public:
    /**
     * Constructor
     * @param audioBuffer The audio buffer to read from
     * @param mediaInfo Media information for configuration
     */
    MediaAudioSource(AudioBuffer& audioBuffer, const MediaInfo& mediaInfo);
    
    /**
     * Destructor
     */
    ~MediaAudioSource() override;
    
    // Disable copy and assignment
    MediaAudioSource(const MediaAudioSource&) = delete;
    MediaAudioSource& operator=(const MediaAudioSource&) = delete;
    
    // ========================================================================
    // juce::AudioSource Implementation
    // ========================================================================
    
    /**
     * Called before playback starts to prepare the source
     */
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    
    /**
     * Called when playback stops to release resources
     */
    void releaseResources() override;
    
    /**
     * Main audio callback - fills the output buffer with audio data
     */
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    
    // ========================================================================
    // MediaAudioSource Specific Methods
    // ========================================================================
    
    /**
     * Set the current playback position (for sync purposes)
     * @param positionInSeconds Current position in seconds
     */
    void setCurrentPosition(double positionInSeconds);
    
    /**
     * Get the current playback position
     * @return Current position in seconds
     */
    double getCurrentPosition() const { return currentPosition_.load(); }
    
    /**
     * Set master gain
     * @param gainValue Gain multiplier (1.0 = unity)
     */
    void setGain(double gainValue) { masterGain_.store(gainValue); }
    
    /**
     * Get master gain
     * @return Current gain multiplier
     */
    double getGain() const { return masterGain_.load(); }
    
    /**
     * Enable/disable audio output
     * @param enabled Whether audio should be output
     */
    void setEnabled(bool enabled) { enabled_.store(enabled); }
    
    /**
     * Check if audio output is enabled
     * @return true if enabled, false if muted
     */
    bool isEnabled() const { return enabled_.load(); }
    
    /**
     * Set channel mapping for multi-channel audio
     * @param channelMap Array mapping input channels to output channels
     */
    void setChannelMapping(const std::vector<int>& channelMap);
    
    /**
     * Get current buffer level
     * @return Buffer level from 0.0 to 1.0
     */
    double getBufferLevel() const;
    
    /**
     * Get number of underruns since last reset
     * @return Number of buffer underruns
     */
    uint64_t getUnderrunCount() const;
    
    /**
     * Reset statistics
     */
    void resetStatistics();
    
    /**
     * Check if audio is currently available
     * @return true if audio data is available for playback
     */
    bool hasAudioAvailable() const;

private:
    // References and configuration
    AudioBuffer& audioBuffer_;
    const MediaInfo& mediaInfo_;
    
    // JUCE audio configuration
    double outputSampleRate_{44100.0};
    int outputChannels_{2};
    int samplesPerBlock_{512};
    bool isPrepared_{false};
    
    // Playback state
    std::atomic<double> currentPosition_{0.0};
    std::atomic<double> masterGain_{1.0};
    std::atomic<bool> enabled_{true};
    
    // Channel mapping
    mutable std::mutex channelMutex_;
    std::vector<int> channelMapping_;
    bool useChannelMapping_{false};
    
    // Internal audio processing
    juce::AudioBuffer<float> tempBuffer_;
    juce::AudioBuffer<float> resampleBuffer_;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource_;
    
    // Sample rate conversion
    bool needsResampling_{false};
    double resampleRatio_{1.0};
    juce::LagrangeInterpolator interpolators_[32]; // Support up to 32 channels
    
    // Statistics
    mutable std::atomic<uint64_t> underrunCount_{0};
    mutable std::atomic<uint64_t> samplesProcessed_{0};
    
    // Internal buffer for partial frame handling
    AudioFrame currentFrame_;
    size_t framePosition_{0};
    bool hasActiveFrame_{false};
    
    /**
     * Fill output buffer from audio buffer
     * @param output Output buffer to fill
     * @param startSample Start sample index
     * @param numSamples Number of samples to fill
     * @return Number of samples actually filled
     */
    int fillFromAudioBuffer(juce::AudioBuffer<float>& output, int startSample, int numSamples);
    
    /**
     * Apply gain to audio buffer
     * @param buffer Buffer to apply gain to
     * @param gain Gain value to apply
     */
    void applyGain(juce::AudioBuffer<float>& buffer, float gain);
    
    /**
     * Apply channel mapping to audio buffer
     * @param buffer Buffer to remap
     */
    void applyChannelMapping(juce::AudioBuffer<float>& buffer);
    
    /**
     * Resample audio data if needed
     * @param input Input buffer
     * @param output Output buffer
     * @return true if successful
     */
    bool resampleAudio(const juce::AudioBuffer<float>& input, juce::AudioBuffer<float>& output);
    
    /**
     * Handle buffer underrun
     */
    void handleUnderrun();
    
    /**
     * Convert MediaReader AudioFrame to JUCE buffer
     * @param frame Input audio frame
     * @param output Output JUCE buffer
     * @param startSample Start sample in output buffer
     * @param numSamples Number of samples to convert
     * @param frameOffset Offset in the input frame
     * @return Number of samples actually converted
     */
    int convertFrameToBuffer(const AudioFrame& frame, juce::AudioBuffer<float>& output, 
                            int startSample, int numSamples, size_t frameOffset = 0);
    
    /**
     * Check if sample rate conversion is needed
     */
    bool needsSampleRateConversion() const;
    
    /**
     * Update resampling configuration
     */
    void updateResamplingConfig();
    
    /**
     * Ensure temp buffers are properly sized
     */
    void ensureBufferSizes(int numChannels, int numSamples);
};

/**
 * Audio source that handles silence when no media is loaded
 */
class SilenceAudioSource : public juce::AudioSource {
public:
    SilenceAudioSource() = default;
    ~SilenceAudioSource() override = default;
    
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override {
        juce::ignoreUnused(samplesPerBlockExpected, sampleRate);
    }
    
    void releaseResources() override {}
    
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override {
        bufferToFill.clearActiveBufferRegion();
    }
};

} // namespace cb_ffmpeg 