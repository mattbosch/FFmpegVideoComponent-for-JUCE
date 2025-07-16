#include "cb_ffmpeg.h"
#include "MediaReaderTypes.h"
#include <atomic>
#include <mutex>

// FFmpeg includes for version info
extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
#include <libavutil/hwcontext.h>
}

namespace cb_ffmpeg {

// ============================================================================
// Global Module State
// ============================================================================

namespace {
    std::atomic<bool> g_moduleInitialized{false};
    std::mutex g_moduleMutex;
    std::atomic<bool> g_debugLogging{false};
    std::atomic<bool> g_performanceLogging{false};
    
    // Global statistics
    std::atomic<uint64_t> g_totalFramesDecoded{0};
    std::atomic<uint64_t> g_totalUnderruns{0};
    std::atomic<uint64_t> g_totalOverruns{0};
}

// ============================================================================
// Module Initialization/Shutdown
// ============================================================================

bool initializeModule() {
    std::lock_guard<std::mutex> lock(g_moduleMutex);
    
    if (g_moduleInitialized.load()) {
        return true;
    }
    
    // Initialize FFmpeg
    if (!initializeFFmpeg()) {
        return false;
    }
    
    g_moduleInitialized.store(true);
    
    if (g_debugLogging.load()) {
        DBG("CB FFmpeg module initialized successfully");
    }
    
    return true;
}

void shutdownModule() {
    std::lock_guard<std::mutex> lock(g_moduleMutex);
    
    if (!g_moduleInitialized.load()) {
        return;
    }
    
    if (g_debugLogging.load()) {
        DBG("Shutting down CB FFmpeg module");
    }
    
    // Shutdown FFmpeg
    shutdownFFmpeg();
    
    g_moduleInitialized.store(false);
}

const ModuleInfo& getModuleInfo() {
    static ModuleInfo info;
    return info;
}

// ============================================================================
// Format Support Information
// ============================================================================

juce::StringArray getSupportedAudioFormats() {
    if (!isFFmpegInitialized()) {
        return {};
    }
    
    static juce::StringArray audioFormats;
    static bool initialized = false;
    
    if (!initialized) {
        // Common audio file extensions
        audioFormats.addArray({"mp3", "wav", "flac", "aac", "ogg", "m4a", "wma", "aiff", "au"});
        
        // Add formats from FFmpeg
        juce::StringArray ffmpegFormats = getSupportedFormats();
        for (const auto& format : ffmpegFormats) {
            // Filter for common audio formats
            if (format.equalsIgnoreCase("mp3") || format.equalsIgnoreCase("wav") ||
                format.equalsIgnoreCase("flac") || format.equalsIgnoreCase("aac") ||
                format.equalsIgnoreCase("ogg") || format.equalsIgnoreCase("m4a")) {
                audioFormats.addIfNotAlreadyThere(format.toLowerCase());
            }
        }
        
        initialized = true;
    }
    
    return audioFormats;
}

juce::StringArray getSupportedVideoFormats() {
    if (!isFFmpegInitialized()) {
        return {};
    }
    
    static juce::StringArray videoFormats;
    static bool initialized = false;
    
    if (!initialized) {
        // Common video file extensions
        videoFormats.addArray({"mp4", "mov", "avi", "mkv", "webm", "wmv", "flv", "m4v", "3gp"});
        
        // Add formats from FFmpeg
        juce::StringArray ffmpegFormats = getSupportedFormats();
        for (const auto& format : ffmpegFormats) {
            // Filter for common video formats
            if (format.equalsIgnoreCase("mp4") || format.equalsIgnoreCase("mov") ||
                format.equalsIgnoreCase("avi") || format.equalsIgnoreCase("mkv") ||
                format.equalsIgnoreCase("webm")) {
                videoFormats.addIfNotAlreadyThere(format.toLowerCase());
            }
        }
        
        initialized = true;
    }
    
    return videoFormats;
}

juce::StringArray getSupportedImageFormats() {
    static juce::StringArray imageFormats;
    static bool initialized = false;
    
    if (!initialized) {
        // Common image file extensions
        imageFormats.addArray({"jpg", "jpeg", "png", "bmp", "tiff", "tif", "gif", "webp"});
        initialized = true;
    }
    
    return imageFormats;
}

bool isFormatSupported(const juce::String& fileExtension) {
    juce::String ext = fileExtension.toLowerCase();
    if (ext.startsWith(".")) {
        ext = ext.substring(1);
    }
    
    // Check audio formats
    if (getSupportedAudioFormats().contains(ext)) {
        return true;
    }
    
    // Check video formats
    if (getSupportedVideoFormats().contains(ext)) {
        return true;
    }
    
    // Check image formats
    if (getSupportedImageFormats().contains(ext)) {
        return true;
    }
    
    return false;
}

// ============================================================================
// FFmpeg Information
// ============================================================================

juce::String getFFmpegVersion() {
    return getFFmpegVersionString();
}

bool isHardwareDecodingAvailable() {
    if (!isFFmpegInitialized()) {
        return false;
    }
    
    // Check if any hardware device types are available
    AVHWDeviceType type = AV_HWDEVICE_TYPE_NONE;
    while ((type = av_hwdevice_get_type_name(type)) != AV_HWDEVICE_TYPE_NONE) {
        return true; // Found at least one hardware device type
    }
    
    return false;
}

juce::StringArray getAvailableHardwareDecoders() {
    juce::StringArray hwDecoders;
    
    if (!isFFmpegInitialized()) {
        return hwDecoders;
    }
    
    AVHWDeviceType type = AV_HWDEVICE_TYPE_NONE;
    while ((type = av_hwdevice_iterate_types(type)) != AV_HWDEVICE_TYPE_NONE) {
        const char* typeName = av_hwdevice_get_type_name(type);
        if (typeName) {
            hwDecoders.add(juce::String(typeName));
        }
    }
    
    return hwDecoders;
}

// ============================================================================
// Utility Functions
// ============================================================================

namespace Utils {

std::unique_ptr<MediaReader> createAudioOnlyReader() {
    auto config = MediaReaderConfig::createLowLatencyConfig();
    config.maxVideoWidth = 0;     // Disable video
    config.maxVideoHeight = 0;
    config.videoBufferFrames = 0;
    return std::make_unique<MediaReader>(config);
}

std::unique_ptr<MediaReader> createVideoReader() {
    auto config = MediaReaderConfig::createHighQualityConfig();
    config.enableHardwareDecoding = true;
    config.videoBufferFrames = 60;
    return std::make_unique<MediaReader>(config);
}

std::unique_ptr<MediaReader> createImageViewer() {
    auto config = MediaReaderConfig::createMemoryEfficientConfig();
    config.audioBufferSizeMs = 0;    // Disable audio
    config.videoBufferFrames = 5;    // Small buffer for images
    config.imageMemoryPool = 20;     // More image cache
    return std::make_unique<MediaReader>(config);
}

MediaType detectMediaType(const juce::File& file) {
    if (!file.exists()) {
        return MediaType::Unknown;
    }
    
    juce::String extension = file.getFileExtension().toLowerCase();
    if (extension.startsWith(".")) {
        extension = extension.substring(1);
    }
    
    // Check format arrays
    if (getSupportedAudioFormats().contains(extension)) {
        return MediaType::AudioOnly;
    }
    
    if (getSupportedVideoFormats().contains(extension)) {
        return MediaType::VideoOnly; // Could be AudioVideo, but we can't tell without opening
    }
    
    if (getSupportedImageFormats().contains(extension)) {
        return MediaType::ImageStill;
    }
    
    return MediaType::Unknown;
}

MediaInfo getQuickMediaInfo(const juce::File& file) {
    MediaInfo info;
    info.file = file;
    info.fileSize = file.getSize();
    info.type = detectMediaType(file);
    
    if (!isFFmpegInitialized()) {
        return info;
    }
    
    // Try to quickly open file and get basic info
    AVFormatContext* formatContext = nullptr;
    juce::String filePath = file.getFullPathName();
    
    int result = avformat_open_input(&formatContext, filePath.toUTF8(), nullptr, nullptr);
    if (result >= 0) {
        result = avformat_find_stream_info(formatContext, nullptr);
        if (result >= 0) {
            info = createMediaInfo(file, formatContext);
        }
        avformat_close_input(&formatContext);
    }
    
    return info;
}

juce::String formatTime(double timeInSeconds, bool showMilliseconds) {
    if (timeInSeconds < 0) {
        return showMilliseconds ? "-:---.---" : "-:--";
    }
    
    int totalMs = static_cast<int>(timeInSeconds * 1000);
    int ms = totalMs % 1000;
    int totalSeconds = totalMs / 1000;
    int seconds = totalSeconds % 60;
    int minutes = totalSeconds / 60;
    
    if (showMilliseconds) {
        return juce::String::formatted("%d:%02d.%03d", minutes, seconds, ms);
    } else {
        return juce::String::formatted("%d:%02d", minutes, seconds);
    }
}

juce::String formatFileSize(int64_t sizeInBytes) {
    if (sizeInBytes < 1024) {
        return juce::String(sizeInBytes) + " B";
    }
    
    double size = static_cast<double>(sizeInBytes);
    juce::StringArray units = {"B", "KB", "MB", "GB", "TB"};
    int unitIndex = 0;
    
    while (size >= 1024.0 && unitIndex < units.size() - 1) {
        size /= 1024.0;
        unitIndex++;
    }
    
    return juce::String(size, unitIndex > 0 ? 1 : 0) + " " + units[unitIndex];
}

int getOptimalAudioBufferSize(int sampleRate, int channels, double latencyMs) {
    // Calculate samples needed for desired latency
    double samples = (latencyMs / 1000.0) * sampleRate * channels;
    
    // Round to next power of 2 for efficiency
    int bufferSize = 64; // Minimum size
    while (bufferSize < samples) {
        bufferSize *= 2;
    }
    
    // Cap at reasonable maximum
    return std::min(bufferSize, 8192);
}

int getOptimalVideoBufferSize(double frameRate, double latencyMs) {
    if (frameRate <= 0) {
        return 30; // Default
    }
    
    // Calculate frames needed for desired latency
    double frames = (latencyMs / 1000.0) * frameRate;
    
    // Add some headroom
    int bufferSize = static_cast<int>(frames * 1.5);
    
    // Ensure reasonable bounds
    return std::max(5, std::min(bufferSize, 120));
}

} // namespace Utils

// ============================================================================
// MediaReaderFactory Implementation
// ============================================================================

std::unique_ptr<MediaReader> MediaReaderFactory::createRealtimeAudioReader() {
    return Utils::createAudioOnlyReader();
}

std::unique_ptr<MediaReader> MediaReaderFactory::createHighQualityReader() {
    return Utils::createVideoReader();
}

std::unique_ptr<MediaReader> MediaReaderFactory::createMemoryEfficientReader() {
    auto config = MediaReaderConfig::createMemoryEfficientConfig();
    return std::make_unique<MediaReader>(config);
}

std::unique_ptr<MediaReader> MediaReaderFactory::createCustomReader(const MediaReaderConfig& config) {
    return std::make_unique<MediaReader>(config);
}

std::unique_ptr<MediaReader> MediaReaderFactory::createOptimalReader(const juce::File& mediaFile) {
    MediaType type = Utils::detectMediaType(mediaFile);
    
    switch (type) {
        case MediaType::AudioOnly:
            return createRealtimeAudioReader();
            
        case MediaType::VideoOnly:
        case MediaType::AudioVideo:
            return createHighQualityReader();
            
        case MediaType::ImageStill:
        case MediaType::ImageSequence:
            return Utils::createImageViewer();
            
        default:
            // Unknown type, create general-purpose reader
            return std::make_unique<MediaReader>();
    }
}

// ============================================================================
// Debug and Performance Monitoring
// ============================================================================

namespace Debug {

void setDebugLogging(bool enabled) {
    g_debugLogging.store(enabled);
    
    if (enabled) {
        DBG("CB FFmpeg debug logging enabled");
    }
}

bool isDebugLoggingEnabled() {
    return g_debugLogging.load();
}

void setPerformanceLogging(bool enabled) {
    g_performanceLogging.store(enabled);
    
    if (enabled && g_debugLogging.load()) {
        DBG("CB FFmpeg performance logging enabled");
    }
}

juce::String getGlobalPerformanceStats() {
    juce::String stats;
    
    stats += "CB FFmpeg Global Statistics:\n";
    stats += "Total frames decoded: " + juce::String(g_totalFramesDecoded.load()) + "\n";
    stats += "Total underruns: " + juce::String(g_totalUnderruns.load()) + "\n";
    stats += "Total overruns: " + juce::String(g_totalOverruns.load()) + "\n";
    stats += "Module initialized: " + juce::String(g_moduleInitialized.load() ? "Yes" : "No") + "\n";
    stats += "FFmpeg version: " + getFFmpegVersion() + "\n";
    stats += "Hardware decoding: " + juce::String(isHardwareDecodingAvailable() ? "Available" : "Not available") + "\n";
    
    return stats;
}

void resetGlobalStats() {
    g_totalFramesDecoded.store(0);
    g_totalUnderruns.store(0);
    g_totalOverruns.store(0);
    
    if (g_debugLogging.load()) {
        DBG("CB FFmpeg global statistics reset");
    }
}

} // namespace Debug

// ============================================================================
// Internal Statistics Updates
// ============================================================================

void updateGlobalStats(uint64_t framesDecoded, uint64_t underruns, uint64_t overruns) {
    g_totalFramesDecoded.fetch_add(framesDecoded);
    g_totalUnderruns.fetch_add(underruns);
    g_totalOverruns.fetch_add(overruns);
}

} // namespace cb_ffmpeg 