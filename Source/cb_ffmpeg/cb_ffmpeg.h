#pragma once

#include "JuceHeader.h"

/**
 * CB FFmpeg Universal Media Reader Module
 * 
 * A comprehensive, thread-safe media reader built on FFmpeg that provides
 * universal support for audio, video, and image files with seamless JUCE
 * integration.
 * 
 * Features:
 * - Universal media format support (audio, video, images)
 * - Thread-safe asynchronous decoding
 * - Lock-free FIFO buffers for smooth playback
 * - Audio/video synchronization
 * - External timeline synchronization
 * - Hardware-accelerated decoding
 * - Memory-efficient frame pooling
 * - Comprehensive configuration options
 * - Real-time performance monitoring
 * 
 * Usage:
 * ```cpp
 * #include "cb_ffmpeg/cb_ffmpeg.h"
 * 
 * // Basic usage
 * auto mediaReader = std::make_unique<cb_ffmpeg::MediaReader>();
 * if (mediaReader->loadFile(mediaFile)) {
 *     auto* audioSource = mediaReader->getAudioSource();
 *     auto* videoComponent = mediaReader->getVideoComponent();
 *     mediaReader->play();
 * }
 * 
 * // Advanced configuration
 * auto config = cb_ffmpeg::MediaReaderConfig::createHighQualityConfig();
 * config.enableHardwareDecoding = true;
 * config.audioBufferSizeMs = 1000;
 * auto mediaReader = std::make_unique<cb_ffmpeg::MediaReader>(config);
 * ```
 */

// Core components
#include "MediaReaderTypes.h"
#include "MediaReaderConfig.h"
#include "MediaReader.h"

// Buffer system
#include "AudioBuffer.h"
#include "VideoBuffer.h"

// Decoder threads
#include "AudioDecoder.h"
#include "VideoDecoder.h"

// JUCE integration
#include "MediaAudioSource.h"
#include "MediaVideoComponent.h"

namespace cb_ffmpeg {

/**
 * Module version information
 */
struct ModuleInfo {
    static constexpr const char* name = "CB FFmpeg Media Reader";
    static constexpr const char* version = "1.0.0";
    static constexpr const char* description = "Universal media reader with FFmpeg backend";
    static constexpr const char* author = "CB Audio";
    static constexpr int versionMajor = 1;
    static constexpr int versionMinor = 0;
    static constexpr int versionPatch = 0;
};

/**
 * Initialize the module (call once at startup)
 * This initializes FFmpeg libraries and sets up global configuration
 */
bool initializeModule();

/**
 * Shutdown the module (call once at shutdown)
 * This cleans up FFmpeg libraries and global resources
 */
void shutdownModule();

/**
 * Get module information
 */
const ModuleInfo& getModuleInfo();

/**
 * Get list of supported audio formats
 */
juce::StringArray getSupportedAudioFormats();

/**
 * Get list of supported video formats
 */
juce::StringArray getSupportedVideoFormats();

/**
 * Get list of supported image formats
 */
juce::StringArray getSupportedImageFormats();

/**
 * Check if a file format is supported
 * @param fileExtension File extension (e.g., "mp4", "wav")
 * @return true if format is supported
 */
bool isFormatSupported(const juce::String& fileExtension);

/**
 * Get FFmpeg version information
 */
juce::String getFFmpegVersion();

/**
 * Check if hardware decoding is available
 * @return true if hardware decoding is supported
 */
bool isHardwareDecodingAvailable();

/**
 * Get available hardware decoder types
 */
juce::StringArray getAvailableHardwareDecoders();

/**
 * Utility functions for common tasks
 */
namespace Utils {
    
    /**
     * Create a MediaReader with optimal settings for audio-only playback
     */
    std::unique_ptr<MediaReader> createAudioOnlyReader();
    
    /**
     * Create a MediaReader with optimal settings for video playback
     */
    std::unique_ptr<MediaReader> createVideoReader();
    
    /**
     * Create a MediaReader with optimal settings for image viewing
     */
    std::unique_ptr<MediaReader> createImageViewer();
    
    /**
     * Detect media type from file
     * @param file File to analyze
     * @return Detected media type
     */
    MediaType detectMediaType(const juce::File& file);
    
    /**
     * Get media information without loading full decoder
     * @param file File to analyze
     * @return Basic media information
     */
    MediaInfo getQuickMediaInfo(const juce::File& file);
    
    /**
     * Convert time to string with appropriate precision
     * @param timeInSeconds Time in seconds
     * @param showMilliseconds Whether to show milliseconds
     * @return Formatted time string (e.g., "1:23.456")
     */
    juce::String formatTime(double timeInSeconds, bool showMilliseconds = false);
    
    /**
     * Convert file size to human-readable string
     * @param sizeInBytes File size in bytes
     * @return Formatted size string (e.g., "1.2 MB")
     */
    juce::String formatFileSize(int64_t sizeInBytes);
    
    /**
     * Get optimal buffer size for given audio configuration
     * @param sampleRate Sample rate
     * @param channels Number of channels
     * @param latencyMs Desired latency in milliseconds
     * @return Recommended buffer size in samples
     */
    int getOptimalAudioBufferSize(int sampleRate, int channels, double latencyMs);
    
    /**
     * Get optimal video buffer size for given configuration
     * @param frameRate Video frame rate
     * @param latencyMs Desired latency in milliseconds
     * @return Recommended buffer size in frames
     */
    int getOptimalVideoBufferSize(double frameRate, double latencyMs);
}

/**
 * Factory class for creating pre-configured MediaReader instances
 */
class MediaReaderFactory {
public:
    /**
     * Create MediaReader optimized for real-time audio applications
     */
    static std::unique_ptr<MediaReader> createRealtimeAudioReader();
    
    /**
     * Create MediaReader optimized for high-quality offline processing
     */
    static std::unique_ptr<MediaReader> createHighQualityReader();
    
    /**
     * Create MediaReader optimized for memory-constrained environments
     */
    static std::unique_ptr<MediaReader> createMemoryEfficientReader();
    
    /**
     * Create MediaReader with custom configuration
     */
    static std::unique_ptr<MediaReader> createCustomReader(const MediaReaderConfig& config);
    
    /**
     * Create MediaReader auto-configured based on media file
     */
    static std::unique_ptr<MediaReader> createOptimalReader(const juce::File& mediaFile);
};

/**
 * Global settings and debugging
 */
namespace Debug {
    
    /**
     * Enable/disable global debug logging
     */
    void setDebugLogging(bool enabled);
    
    /**
     * Check if debug logging is enabled
     */
    bool isDebugLoggingEnabled();
    
    /**
     * Enable/disable performance metrics logging
     */
    void setPerformanceLogging(bool enabled);
    
    /**
     * Get global performance statistics
     */
    juce::String getGlobalPerformanceStats();
    
    /**
     * Reset global performance statistics
     */
    void resetGlobalStats();
}

} // namespace cb_ffmpeg

/**
 * Convenience macros for common operations
 */
#define CB_FFMPEG_LOAD_AUDIO(reader, file) \
    ((reader)->loadFile(file) && (reader)->hasAudio())

#define CB_FFMPEG_LOAD_VIDEO(reader, file) \
    ((reader)->loadFile(file) && (reader)->hasVideo())

#define CB_FFMPEG_LOAD_IMAGE(reader, file) \
    ((reader)->loadFile(file) && (reader)->isImage())

#define CB_FFMPEG_CHECK_SUPPORT(file) \
    cb_ffmpeg::isFormatSupported((file).getFileExtension().toLowerCase())

/**
 * Version check macros
 */
#define CB_FFMPEG_VERSION_MAJOR cb_ffmpeg::ModuleInfo::versionMajor
#define CB_FFMPEG_VERSION_MINOR cb_ffmpeg::ModuleInfo::versionMinor
#define CB_FFMPEG_VERSION_PATCH cb_ffmpeg::ModuleInfo::versionPatch

#define CB_FFMPEG_VERSION_CHECK(major, minor, patch) \
    (CB_FFMPEG_VERSION_MAJOR > (major) || \
     (CB_FFMPEG_VERSION_MAJOR == (major) && CB_FFMPEG_VERSION_MINOR > (minor)) || \
     (CB_FFMPEG_VERSION_MAJOR == (major) && CB_FFMPEG_VERSION_MINOR == (minor) && CB_FFMPEG_VERSION_PATCH >= (patch))) 