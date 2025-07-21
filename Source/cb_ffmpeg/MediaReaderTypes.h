#pragma once

#include "JuceHeader.h"
#include <memory>
#include <atomic>
#include <chrono>

// Forward declare FFmpeg types to avoid including headers here
struct AVFormatContext;
struct AVCodecContext;
struct AVFrame;
struct AVPacket;
struct SwrContext;
struct SwsContext;

namespace cb_ffmpeg {

// Forward declarations
class MediaReader;
class AudioDecoder;
class VideoDecoder;
class ImageLoader;

/**
 * Media type enumeration
 */
enum class MediaType {
    Unknown = 0,
    AudioOnly,
    VideoOnly,
    AudioVideo,
    ImageStill,
    ImageSequence
};

/**
 * Playback state enumeration
 */
enum class PlaybackState {
    Stopped = 0,
    Playing,
    Paused,
    Seeking,
    Loading,
    Error
};

/**
 * Decoder state enumeration
 */
enum class DecoderState {
    Uninitialized = 0,
    Initializing,
    Ready,
    Decoding,
    Seeking,
    EndOfStream,
    Error,
    Destroyed
};

/**
 * Pixel format enumeration for video
 */
enum class PixelFormat {
    Unknown = 0,
    RGB24,
    RGBA,
    BGR24,
    BGRA,
    YUV420P,
    YUV422P,
    YUV444P,
    Gray8,
    Gray16
};

/**
 * Audio sample format enumeration
 */
enum class SampleFormat {
    Unknown = 0,
    UInt8,
    Int16,
    Int32,
    Float32,
    Float64
};

/**
 * Synchronization mode enumeration
 */
enum class SyncMode {
    Internal = 0,    // Audio master clock
    External,        // External timeline control
    Freerun         // No synchronization
};

/**
 * Seek mode enumeration
 */
enum class SeekMode {
    Accurate = 0,    // Frame-accurate seeking (slower)
    Fast,           // Keyframe seeking (faster)
    Backward,       // Always seek to previous keyframe
    Forward         // Always seek to next keyframe
};

/**
 * Media stream information
 */
struct StreamInfo {
    int streamIndex = -1;
    MediaType type = MediaType::Unknown;
    
    // Common properties
    double duration = 0.0;          // Duration in seconds
    int64_t frameCount = 0;         // Total frames/samples
    juce::String codec;             // Codec name
    juce::StringPairArray metadata; // Stream metadata
    
    // Audio-specific properties
    int sampleRate = 0;             // Audio sample rate
    int channels = 0;               // Number of audio channels
    SampleFormat sampleFormat = SampleFormat::Unknown;
    int bitsPerSample = 0;
    int64_t bitRate = 0;            // Bit rate in bits per second
    
    // Video-specific properties
    int width = 0;                  // Video width
    int height = 0;                 // Video height
    double frameRate = 0.0;         // Video frame rate
    PixelFormat pixelFormat = PixelFormat::Unknown;
    bool isInterlaced = false;
    double aspectRatio = 1.0;
};

/**
 * Media file information
 */
struct MediaInfo {
    juce::File file;                // Source file
    MediaType type = MediaType::Unknown;
    double duration = 0.0;          // Total duration in seconds
    int64_t fileSize = 0;           // File size in bytes
    juce::String format;            // Container format
    juce::StringPairArray metadata; // File metadata
    
    // Stream information
    std::vector<StreamInfo> streams;
    int audioStreamIndex = -1;      // Primary audio stream
    int videoStreamIndex = -1;      // Primary video stream
    
    // Computed properties
    bool hasAudio() const { return audioStreamIndex >= 0; }
    bool hasVideo() const { return videoStreamIndex >= 0; }
    bool isImage() const { return type == MediaType::ImageStill || type == MediaType::ImageSequence; }
    
    const StreamInfo* getAudioStream() const {
        return (audioStreamIndex >= 0 && audioStreamIndex < streams.size()) ? 
               &streams[audioStreamIndex] : nullptr;
    }
    
    const StreamInfo* getVideoStream() const {
        return (videoStreamIndex >= 0 && videoStreamIndex < streams.size()) ? 
               &streams[videoStreamIndex] : nullptr;
    }
};

/**
 * Audio frame data structure
 */
struct AudioFrame {
    std::unique_ptr<float[]> data;   // Interleaved audio data
    size_t numSamples = 0;           // Number of samples per channel
    int numChannels = 0;             // Number of channels
    int sampleRate = 0;              // Sample rate
    double timestamp = 0.0;          // Presentation timestamp in seconds
    bool isEndOfStream = false;      // End of stream marker
    
    // Constructor
    AudioFrame() = default;
    AudioFrame(size_t samples, int channels, int rate, double time) 
        : numSamples(samples), numChannels(channels), sampleRate(rate), timestamp(time) {
        data = std::make_unique<float[]>(samples * channels);
    }
    
    // Move constructor
    AudioFrame(AudioFrame&& other) noexcept 
        : data(std::move(other.data)), numSamples(other.numSamples), 
          numChannels(other.numChannels), sampleRate(other.sampleRate),
          timestamp(other.timestamp), isEndOfStream(other.isEndOfStream) {}
    
    // Move assignment
    AudioFrame& operator=(AudioFrame&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            numSamples = other.numSamples;
            numChannels = other.numChannels;
            sampleRate = other.sampleRate;
            timestamp = other.timestamp;
            isEndOfStream = other.isEndOfStream;
        }
        return *this;
    }
    
    // Disable copy
    AudioFrame(const AudioFrame&) = delete;
    AudioFrame& operator=(const AudioFrame&) = delete;
    
    // Utility methods
    size_t getTotalSamples() const { return numSamples * numChannels; }
    size_t getSizeInBytes() const { return getTotalSamples() * sizeof(float); }
    bool isEmpty() const { return numSamples == 0 || numChannels == 0 || !data; }
};

/**
 * Video frame data structure
 */
struct VideoFrame {
    juce::Image image;               // JUCE image data
    double timestamp = 0.0;          // Presentation timestamp in seconds
    double duration = 0.0;           // Frame duration in seconds
    int width = 0;                   // Frame width
    int height = 0;                  // Frame height
    PixelFormat format = PixelFormat::RGBA;
    bool isKeyFrame = false;         // Is this a keyframe?
    bool isEndOfStream = false;      // End of stream marker
    
    // Constructor
    VideoFrame() = default;
    VideoFrame(int w, int h, double time, double dur = 0.0) 
        : timestamp(time), duration(dur), width(w), height(h) {
        image = juce::Image(juce::Image::ARGB, w, h, true);
    }
    
    // Utility methods
    bool isEmpty() const { return !image.isValid() || width <= 0 || height <= 0; }
    size_t getSizeInBytes() const { return image.getWidth() * image.getHeight() * 4; }
};

/**
 * Decoder statistics for monitoring and debugging
 */
struct DecoderStats {
    std::atomic<uint64_t> framesDecoded{0};     // Total frames decoded
    std::atomic<uint64_t> framesDropped{0};     // Frames dropped for sync
    std::atomic<uint64_t> bufferUnderruns{0};   // Buffer underrun events
    std::atomic<uint64_t> bufferOverruns{0};    // Buffer overrun events
    std::atomic<double> averageDecodeTime{0.0}; // Average decode time per frame
    std::atomic<double> currentBufferLevel{0.0}; // Current buffer fill level (0-1)
    std::atomic<double> syncOffset{0.0};        // Current sync offset in ms
    
    void reset() {
        framesDecoded = 0;
        framesDropped = 0;
        bufferUnderruns = 0;
        bufferOverruns = 0;
        averageDecodeTime = 0.0;
        currentBufferLevel = 0.0;
        syncOffset = 0.0;
    }
    
    // Create a copyable snapshot of the stats
    struct Snapshot {
        uint64_t framesDecoded;
        uint64_t framesDropped;
        uint64_t bufferUnderruns;
        uint64_t bufferOverruns;
        double averageDecodeTime;
        double currentBufferLevel;
        double syncOffset;
        
        Snapshot() = default;
        Snapshot(const DecoderStats& stats) :
            framesDecoded(stats.framesDecoded.load()),
            framesDropped(stats.framesDropped.load()),
            bufferUnderruns(stats.bufferUnderruns.load()),
            bufferOverruns(stats.bufferOverruns.load()),
            averageDecodeTime(stats.averageDecodeTime.load()),
            currentBufferLevel(stats.currentBufferLevel.load()),
            syncOffset(stats.syncOffset.load())
        {}
    };
    
    Snapshot getSnapshot() const {
        return Snapshot(*this);
    }
};

/**
 * Sync information for audio/video synchronization
 */
struct SyncInfo {
    double masterClock = 0.0;        // Master clock time in seconds
    double audioClock = 0.0;         // Audio clock time in seconds
    double videoClock = 0.0;         // Video clock time in seconds
    double externalClock = 0.0;      // External clock time in seconds
    SyncMode mode = SyncMode::Internal;
    double tolerance = 0.040;        // Sync tolerance in seconds
    bool isInSync = true;            // Are streams in sync?
    double offset = 0.0;             // Current offset in seconds
};

/**
 * External synchronization interface
 */
class ExternalSyncInterface {
public:
    virtual ~ExternalSyncInterface() = default;
    
    // Clock control
    virtual void setPosition(double timeInSeconds) = 0;
    virtual double getCurrentPosition() const = 0;
    virtual void setPlaybackRate(double rate) = 0;
    virtual double getPlaybackRate() const = 0;
    
    // State notifications
    virtual void onPlaybackStarted() {}
    virtual void onPlaybackStopped() {}
    virtual void onSeekCompleted(double newPosition) {}
};

/**
 * Callback interface for media events
 */
class MediaReaderCallback {
public:
    virtual ~MediaReaderCallback() = default;
    
    // Playback events
    virtual void onPlaybackStarted() {}
    virtual void onPlaybackStopped() {}
    virtual void onPlaybackPaused() {}
    virtual void onSeekStarted(double targetTime) {}
    virtual void onSeekCompleted(double actualTime) {}
    virtual void onEndOfMedia() {}
    
    // Error events
    virtual void onError(const juce::String& errorMessage) {}
    virtual void onDecoderError(const juce::String& decoderName, const juce::String& error) {}
    
    // Information events
    virtual void onMediaLoaded(const MediaInfo& info) {}
    virtual void onBufferLevelChanged(double audioLevel, double videoLevel) {}
    virtual void onSyncStatusChanged(const SyncInfo& syncInfo) {}
};

/**
 * Time utilities
 */
namespace TimeUtils {
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = Clock::time_point;
    using Duration = Clock::duration;
    
    inline TimePoint now() { return Clock::now(); }
    
    inline double toSeconds(const Duration& duration) {
        return std::chrono::duration_cast<std::chrono::duration<double>>(duration).count();
    }
    
    inline Duration fromSeconds(double seconds) {
        return std::chrono::duration_cast<Duration>(std::chrono::duration<double>(seconds));
    }
    
    inline int64_t toMilliseconds(const Duration& duration) {
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }
}

/**
 * FFmpeg resource RAII wrappers
 */
namespace FFmpegRAII {
    
    struct FormatContextDeleter {
        void operator()(AVFormatContext* ctx) const;
    };
    
    struct CodecContextDeleter {
        void operator()(AVCodecContext* ctx) const;
    };
    
    struct FrameDeleter {
        void operator()(AVFrame* frame) const;
    };
    
    struct PacketDeleter {
        void operator()(AVPacket* packet) const;
    };
    
    struct SwrContextDeleter {
        void operator()(SwrContext* ctx) const;
    };
    
    struct SwsContextDeleter {
        void operator()(SwsContext* ctx) const;
    };
    
    using FormatContextPtr = std::unique_ptr<AVFormatContext, FormatContextDeleter>;
    using CodecContextPtr = std::unique_ptr<AVCodecContext, CodecContextDeleter>;
    using FramePtr = std::unique_ptr<AVFrame, FrameDeleter>;
    using PacketPtr = std::unique_ptr<AVPacket, PacketDeleter>;
    using SwrContextPtr = std::unique_ptr<SwrContext, SwrContextDeleter>;
    using SwsContextPtr = std::unique_ptr<SwsContext, SwsContextDeleter>;
}

} // namespace cb_ffmpeg 