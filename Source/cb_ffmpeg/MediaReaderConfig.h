#pragma once

#include <cstddef>
#include <juce_core/juce_core.h>

namespace cb_ffmpeg {

/**
 * Configuration structure for MediaReader behavior and performance tuning
 */
struct MediaReaderConfig {
    // Buffer Configuration
    size_t audioBufferSizeMs = 500;          // Audio buffer duration in milliseconds
    size_t videoBufferFrames = 30;           // Number of video frames to buffer
    size_t maxDecodeAhead = 1000;            // Maximum decode ahead time in ms
    size_t imageMemoryPool = 10;             // Number of images to keep in memory pool
    
    // Synchronization Settings
    bool enableAVSync = true;                // Enable audio/video synchronization
    double syncToleranceMs = 40.0;           // AV sync tolerance in milliseconds
    double maxSyncCorrectionMs = 100.0;      // Maximum correction applied per sync
    bool allowFrameDropping = true;          // Allow dropping video frames for sync
    bool allowAudioStretching = false;       // Allow minor audio rate adjustment
    
    // Video Configuration
    int maxVideoWidth = 1920;               // Maximum video width to decode
    int maxVideoHeight = 1080;              // Maximum video height to decode
    bool enableHardwareDecoding = true;     // Use GPU acceleration when available
    bool maintainAspectRatio = true;        // Maintain aspect ratio during scaling
    int videoQuality = 0;                   // Video quality hint (0=auto, 1=low, 2=medium, 3=high)
    
    // Audio Configuration
    int targetSampleRate = 44100;           // Target sample rate for audio output
    int targetChannels = 2;                 // Target number of audio channels
    double audioGain = 1.0;                 // Audio gain multiplier (1.0 = unity)
    bool enableAudioResampling = true;      // Enable automatic audio resampling
    
    // Threading Configuration
    int audioDecoderThreadPriority = 8;     // Audio decoder thread priority (1-10)
    int videoDecoderThreadPriority = 5;     // Video decoder thread priority (1-10)
    int backgroundThreadPriority = 3;       // Background/loading thread priority (1-10)
    bool useMultiThreadedDecoding = true;   // Enable multi-threaded FFmpeg decoding
    
    // Performance Tuning
    size_t ioBufferSize = 32768;            // File I/O buffer size in bytes
    bool enablePreloading = true;           // Preload next sections for smooth playback
    double preloadThresholdPercent = 75.0;  // Start preloading when buffer is X% full
    bool enableMemoryMapping = true;        // Use memory mapping for large files
    
    // Debugging and Logging
    bool enableDebugLogging = false;        // Enable detailed debug output
    bool logPerformanceMetrics = false;     // Log performance metrics
    bool validateSyncAccuracy = false;      // Validate sync accuracy (performance cost)
    
    // Format-Specific Settings
    struct {
        bool preferBuiltinDecoders = false; // Prefer built-in over FFmpeg for common formats
        int jpegQuality = 95;               // JPEG decode quality (0-100)
        bool enableProgressiveJPEG = true;  // Support progressive JPEG loading
    } imageSettings;
    
    struct {
        bool enableGaplessPlayback = true;  // Enable gapless audio playback
        double fadeInDurationMs = 0.0;      // Fade-in duration for audio start
        double fadeOutDurationMs = 0.0;     // Fade-out duration for audio end
    } audioSettings;
    
    struct {
        bool enableDeinterlacing = true;    // Enable deinterlacing for interlaced video
        int deinterlaceMode = 0;            // Deinterlacing mode (0=auto, 1=linear, 2=adaptive)
        bool enableColorCorrection = false; // Enable basic color correction
    } videoSettings;
    
    /**
     * Validates configuration values and adjusts invalid ones to safe defaults
     * @return true if all values were valid, false if adjustments were made
     */
    bool validate() {
        bool wasValid = true;
        
        // Clamp buffer sizes to reasonable ranges
        if (audioBufferSizeMs < 50 || audioBufferSizeMs > 5000) {
            audioBufferSizeMs = juce::jlimit(size_t(50), size_t(5000), audioBufferSizeMs);
            wasValid = false;
        }
        
        if (videoBufferFrames < 5 || videoBufferFrames > 200) {
            videoBufferFrames = juce::jlimit(size_t(5), size_t(200), videoBufferFrames);
            wasValid = false;
        }
        
        // Validate sync settings
        if (syncToleranceMs < 1.0 || syncToleranceMs > 500.0) {
            syncToleranceMs = juce::jlimit(1.0, 500.0, syncToleranceMs);
            wasValid = false;
        }
        
        // Validate video dimensions
        if (maxVideoWidth < 128 || maxVideoWidth > 7680) {
            maxVideoWidth = juce::jlimit(128, 7680, maxVideoWidth);
            wasValid = false;
        }
        
        if (maxVideoHeight < 128 || maxVideoHeight > 4320) {
            maxVideoHeight = juce::jlimit(128, 4320, maxVideoHeight);
            wasValid = false;
        }
        
        // Validate audio settings
        if (targetSampleRate < 8000 || targetSampleRate > 192000) {
            targetSampleRate = juce::jlimit(8000, 192000, targetSampleRate);
            wasValid = false;
        }
        
        if (targetChannels < 1 || targetChannels > 32) {
            targetChannels = juce::jlimit(1, 32, targetChannels);
            wasValid = false;
        }
        
        if (audioGain < 0.0 || audioGain > 10.0) {
            audioGain = juce::jlimit(0.0, 10.0, audioGain);
            wasValid = false;
        }
        
        // Validate thread priorities
        audioDecoderThreadPriority = juce::jlimit(1, 10, audioDecoderThreadPriority);
        videoDecoderThreadPriority = juce::jlimit(1, 10, videoDecoderThreadPriority);
        backgroundThreadPriority = juce::jlimit(1, 10, backgroundThreadPriority);
        
        return wasValid;
    }
    
    /**
     * Creates a high-performance configuration optimized for low latency
     */
    static MediaReaderConfig createLowLatencyConfig() {
        MediaReaderConfig config;
        config.audioBufferSizeMs = 100;
        config.videoBufferFrames = 10;
        config.maxDecodeAhead = 200;
        config.syncToleranceMs = 20.0;
        config.audioDecoderThreadPriority = 10;
        config.videoDecoderThreadPriority = 8;
        config.enablePreloading = false;
        return config;
    }
    
    /**
     * Creates a high-quality configuration optimized for best quality
     */
    static MediaReaderConfig createHighQualityConfig() {
        MediaReaderConfig config;
        config.audioBufferSizeMs = 1000;
        config.videoBufferFrames = 60;
        config.maxDecodeAhead = 2000;
        config.syncToleranceMs = 10.0;
        config.maxVideoWidth = 3840;
        config.maxVideoHeight = 2160;
        config.videoQuality = 3;
        config.targetSampleRate = 96000;
        config.enableHardwareDecoding = true;
        config.useMultiThreadedDecoding = true;
        return config;
    }
    
    /**
     * Creates a memory-efficient configuration for resource-constrained environments
     */
    static MediaReaderConfig createMemoryEfficientConfig() {
        MediaReaderConfig config;
        config.audioBufferSizeMs = 250;
        config.videoBufferFrames = 15;
        config.maxDecodeAhead = 500;
        config.imageMemoryPool = 3;
        config.maxVideoWidth = 1280;
        config.maxVideoHeight = 720;
        config.ioBufferSize = 16384;
        config.enablePreloading = false;
        config.enableMemoryMapping = false;
        return config;
    }
};

} // namespace cb_ffmpeg 