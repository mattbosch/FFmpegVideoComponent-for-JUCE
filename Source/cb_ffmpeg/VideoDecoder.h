#pragma once

#include "VideoBuffer.h"
#include "MediaReaderTypes.h"
#include "MediaReaderConfig.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <memory>

// FFmpeg includes
extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
#include <libavutil/pixdesc.h>
}

namespace cb_ffmpeg {

/**
 * Video decoder that runs in its own thread
 * 
 * This class handles video stream decoding using FFmpeg APIs and feeds
 * decoded video frames into the VideoBuffer for consumption by the
 * JUCE video component.
 */
class VideoDecoder {
public:
    /**
     * Constructor
     * @param videoBuffer Buffer to write decoded video frames
     * @param framePool Memory pool for efficient frame allocation
     * @param config Configuration for decoding behavior
     */
    VideoDecoder(VideoBuffer& videoBuffer, VideoFramePool& framePool, const MediaReaderConfig& config);
    
    /**
     * Destructor
     */
    ~VideoDecoder();
    
    // Disable copy and assignment
    VideoDecoder(const VideoDecoder&) = delete;
    VideoDecoder& operator=(const VideoDecoder&) = delete;
    
    /**
     * Initialize decoder with format context and stream index
     * @param formatContext FFmpeg format context
     * @param streamIndex Video stream index
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
     * Set target dimensions for output frames
     * @param width Target width (0 = source width)
     * @param height Target height (0 = source height)
     * @param maintainAspectRatio Whether to maintain aspect ratio
     */
    void setOutputDimensions(int width, int height, bool maintainAspectRatio = true);
    
    /**
     * Set target pixel format
     * @param format Target pixel format
     */
    void setOutputFormat(PixelFormat format);
    
    /**
     * Enable/disable hardware decoding
     * @param enable Whether to use hardware decoding
     */
    void setHardwareDecoding(bool enable);
    
    /**
     * Check if hardware decoding is active
     */
    bool isHardwareDecodingActive() const { return hardwareDecodingActive_.load(); }
    
    /**
     * Get last error message
     */
    juce::String getLastError() const;

private:
    // Configuration and state
    const MediaReaderConfig& config_;
    VideoBuffer& videoBuffer_;
    VideoFramePool& framePool_;
    std::atomic<DecoderState> state_{DecoderState::Uninitialized};
    StreamInfo streamInfo_;
    
    // FFmpeg resources
    FFmpegRAII::FormatContextPtr formatContext_;
    FFmpegRAII::CodecContextPtr codecContext_;
    FFmpegRAII::SwsContextPtr swsContext_;
    AVStream* videoStream_{nullptr};
    int streamIndex_{-1};
    
    // Hardware decoding
    std::atomic<bool> hardwareDecodingEnabled_{true};
    std::atomic<bool> hardwareDecodingActive_{false};
    AVBufferRef* hwDeviceContext_{nullptr};
    AVPixelFormat hwPixelFormat_{AV_PIX_FMT_NONE};
    
    // Threading
    std::thread decoderThread_;
    std::atomic<bool> shouldStop_{false};
    std::atomic<bool> shouldSeek_{false};
    std::atomic<double> seekTarget_{0.0};
    std::atomic<SeekMode> seekMode_{SeekMode::Accurate};
    mutable std::mutex decoderMutex_;
    std::condition_variable decoderCondition_;
    
    // Video processing
    std::atomic<double> currentTimestamp_{0.0};
    
    // Output format configuration
    std::atomic<int> outputWidth_{0};
    std::atomic<int> outputHeight_{0};
    std::atomic<bool> maintainAspectRatio_{true};
    std::atomic<PixelFormat> outputFormat_{PixelFormat::RGBA};
    AVPixelFormat targetAVFormat_{AV_PIX_FMT_RGBA};
    
    // Scaling and conversion state
    bool needsScaling_{false};
    bool needsFormatConversion_{false};
    int scaledWidth_{0};
    int scaledHeight_{0};
    
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
     * Initialize hardware decoding
     */
    bool initializeHardwareDecoding();
    
    /**
     * Initialize scaler if needed
     */
    bool initializeScaler();
    
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
     * Calculate frame duration
     */
    double calculateFrameDuration(AVFrame* frame) const;
    
    /**
     * Check if frame needs scaling or format conversion
     */
    bool needsConversion(AVFrame* frame) const;
    
    /**
     * Calculate output dimensions with aspect ratio preservation
     */
    void calculateOutputDimensions(int sourceWidth, int sourceHeight, int& outputWidth, int& outputHeight) const;
    
    /**
     * Convert AVFrame to JUCE Image
     */
    bool convertFrameToImage(AVFrame* frame, VideoFrame& videoFrame);
    
    /**
     * Transfer hardware frame to system memory
     */
    bool transferHardwareFrame(AVFrame* hwFrame, AVFrame* swFrame);
    
    /**
     * Cleanup FFmpeg resources
     */
    void cleanup();
    
    /**
     * Cleanup hardware resources
     */
    void cleanupHardware();
    
    /**
     * Get hardware pixel format callback
     */
    static enum AVPixelFormat getHwFormat(AVCodecContext* ctx, const enum AVPixelFormat* pixFmts);
};

/**
 * Helper class for video format conversion
 */
class VideoFormatConverter {
public:
    /**
     * Convert FFmpeg pixel format to internal format
     */
    static PixelFormat convertPixelFormat(AVPixelFormat avFormat);
    
    /**
     * Convert internal pixel format to FFmpeg format
     */
    static AVPixelFormat convertToAVFormat(PixelFormat format);
    
    /**
     * Get bytes per pixel for format
     */
    static int getBytesPerPixel(AVPixelFormat format);
    static int getBytesPerPixel(PixelFormat format);
    
    /**
     * Convert raw video data to JUCE Image
     */
    static bool convertToJuceImage(
        const uint8_t* data, int width, int height, AVPixelFormat sourceFormat,
        juce::Image& targetImage
    );
    
    /**
     * Scale video frame
     */
    static bool scaleFrame(
        SwsContext* sws,
        const uint8_t* const srcData[], const int srcLinesize[],
        uint8_t* const dstData[], const int dstLinesize[],
        int srcWidth, int srcHeight, int dstWidth, int dstHeight
    );
    
    /**
     * Calculate line sizes for pixel format
     */
    static bool calculateLinesize(int width, AVPixelFormat format, int linesize[4]);
    
    /**
     * Check if format is hardware format
     */
    static bool isHardwareFormat(AVPixelFormat format);
    
    /**
     * Get supported hardware pixel formats
     */
    static std::vector<AVPixelFormat> getSupportedHardwareFormats();
};

/**
 * Hardware decoder helper
 */
class HardwareDecoderHelper {
public:
    /**
     * Initialize hardware device context
     */
    static AVBufferRef* initializeHardwareDevice(AVHWDeviceType type);
    
    /**
     * Get available hardware device types
     */
    static std::vector<AVHWDeviceType> getAvailableHardwareTypes();
    
    /**
     * Check if codec supports hardware decoding
     */
    static bool codecSupportsHardware(const AVCodec* codec, AVHWDeviceType type);
    
    /**
     * Get hardware configuration for codec
     */
    static const AVCodecHWConfig* getHardwareConfig(const AVCodec* codec, AVHWDeviceType type);
    
    /**
     * Get best hardware device type for codec
     */
    static AVHWDeviceType getBestHardwareType(const AVCodec* codec);
};

} // namespace cb_ffmpeg 