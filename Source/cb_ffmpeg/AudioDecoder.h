#pragma once

#include "MediaReaderTypes.h"
#include "MediaReaderConfig.h"
#include "AudioBuffer.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <memory>

// FFmpeg includes
extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswresample/swresample.h>
#include <libavutil/opt.h>
}

namespace cb_ffmpeg {

/**
 * Audio decoder that runs in its own thread
 * 
 * This class handles audio stream decoding using FFmpeg APIs and feeds
 * decoded audio frames into the AudioBuffer for consumption by the
 * JUCE audio callback.
 */
class AudioDecoder {
public:
    /**
     * Constructor
     * @param audioBuffer Buffer to write decoded audio frames
     * @param config Configuration for decoding behavior
     */
    AudioDecoder(AudioBuffer& audioBuffer, const MediaReaderConfig& config);
    
    /**
     * Destructor
     */
    ~AudioDecoder();
    
    // Disable copy and assignment
    AudioDecoder(const AudioDecoder&) = delete;
    AudioDecoder& operator=(const AudioDecoder&) = delete;
    
    /**
     * Initialize decoder with format context and stream index
     * @param formatContext FFmpeg format context
     * @param streamIndex Audio stream index
     * @return true if successful, false on error
     */
    bool initialize(AVFormatContext* formatContext, int streamIndex);
    
    /**
     * Start the decoder thread
     * @return true if successful, false on error
     */
    bool start();
    
    /**
     * Stop the decoder thread
     */
    void stop();
    
    /**
     * Request seek to specific time
     * @param timeInSeconds Target time in seconds
     * @param mode Seek mode
     */
    void seek(double timeInSeconds, SeekMode mode = SeekMode::Accurate);
    
    /**
     * Flush decoder state (clear buffers, reset)
     */
    void flush();
    
    /**
     * Get current decoder state
     */
    DecoderState getState() const { return state_.load(); }
    
    /**
     * Check if decoder is running
     */
    bool isRunning() const { return decoderThread_.joinable() && state_.load() != DecoderState::Destroyed; }
    
    /**
     * Get decoder statistics
     */
    DecoderStats::Snapshot getStats() const { return stats_.getSnapshot(); }
    
    /**
     * Reset statistics
     */
    void resetStats() { stats_.reset(); }
    
    /**
     * Get stream information
     */
    const StreamInfo& getStreamInfo() const { return streamInfo_; }
    
    /**
     * Get current timestamp being decoded
     */
    double getCurrentTimestamp() const { return currentTimestamp_.load(); }
    
    /**
     * Set target playback rate (for time-stretching)
     * @param rate Playback rate (0.1 to 4.0)
     */
    void setPlaybackRate(double rate);
    
    /**
     * Set audio gain
     * @param gain Gain multiplier (1.0 = unity)
     */
    void setGain(double gain) { gain_.store(gain); }
    
    /**
     * Get last error message
     */
    juce::String getLastError() const;

private:
    // Configuration and state
    const MediaReaderConfig& config_;
    AudioBuffer& audioBuffer_;
    std::atomic<DecoderState> state_{DecoderState::Uninitialized};
    StreamInfo streamInfo_;
    
    // FFmpeg resources
    AVFormatContext* formatContext_{nullptr}; // Not owned by this class
    AVCodecContext* codecContext_{nullptr};
    SwrContext* swrContext_{nullptr};
    AVStream* audioStream_{nullptr};
    int streamIndex_{-1};
    
    // Threading
    std::thread decoderThread_;
    std::atomic<bool> shouldStop_{false};
    std::atomic<bool> shouldSeek_{false};
    std::atomic<double> seekTarget_{0.0};
    std::atomic<SeekMode> seekMode_{SeekMode::Accurate};
    mutable std::mutex decoderMutex_;
    std::condition_variable decoderCondition_;
    
    // Audio processing
    std::atomic<double> currentTimestamp_{0.0};
    std::atomic<double> playbackRate_{1.0};
    std::atomic<double> gain_{1.0};
    
    // Resampler state
    bool needsResampling_{false};
    int targetSampleRate_{44100};
    int targetChannels_{2};
    AVSampleFormat targetFormat_{AV_SAMPLE_FMT_FLT};
    
    // Statistics
    mutable DecoderStats stats_;
    
    // Error handling
    mutable std::mutex errorMutex_;
    juce::String lastError_;
    
    // Performance timing
    TimeUtils::TimePoint lastDecodeTime_;
    std::atomic<double> averageDecodeTime_{0.0};
    
    /**
     * Main decoder thread loop
     */
    void decoderLoop();
    
    /**
     * Initialize codec context
     */
    bool initializeCodec();
    
    /**
     * Initialize resampler if needed
     */
    bool initializeResampler();
    
    /**
     * Decode a single packet
     */
    bool decodePacket(AVPacket* packet);
    
    /**
     * Process decoded frame
     */
    bool processFrame(AVFrame* frame);
    
    /**
     * Convert frame to target format and write to buffer
     */
    bool convertAndWriteFrame(AVFrame* frame);
    
    /**
     * Perform seek operation
     */
    void performSeek();
    
    /**
     * Handle end of stream
     */
    void handleEndOfStream();
    
    /**
     * Update statistics
     */
    void updateStats();
    
    /**
     * Set error message
     */
    void setError(const juce::String& error);
    
    /**
     * Calculate presentation timestamp
     */
    double calculatePTS(AVFrame* frame) const;
    
    /**
     * Apply audio gain to frame
     */
    void applyGain(float* audioData, size_t numSamples, double gainValue) const;
    
    /**
     * Check if format needs resampling
     */
    bool needsFormatConversion(AVFrame* frame) const;
    
    /**
     * Get optimal buffer size for current format
     */
    size_t getOptimalBufferSize() const;
    
    /**
     * Cleanup FFmpeg resources
     */
    void cleanup();
};

/**
 * Helper class for audio format conversion
 */
class AudioFormatConverter {
public:
    /**
     * Convert FFmpeg sample format to JUCE-compatible format
     */
    static SampleFormat convertSampleFormat(AVSampleFormat avFormat);
    
    /**
     * Convert JUCE sample format to FFmpeg format
     */
    static AVSampleFormat convertToAVFormat(SampleFormat format);
    
    /**
     * Get bytes per sample for format
     */
    static int getBytesPerSample(AVSampleFormat format);
    static int getBytesPerSample(SampleFormat format);
    
    /**
     * Convert audio data between formats
     */
    static bool convertAudioData(
        const uint8_t* input, int inputSamples, AVSampleFormat inputFormat, int inputChannels,
        float* output, int outputSamples, int outputChannels,
        double gain = 1.0
    );
    
    /**
     * Resample audio data
     */
    static bool resampleAudio(
        SwrContext* swr,
        const uint8_t** input, int inputSamples,
        uint8_t** output, int outputSamples
    );
    
    /**
     * Calculate resampled output size
     */
    static int calculateResampledSize(int inputSamples, int inputRate, int outputRate);
};

} // namespace cb_ffmpeg 