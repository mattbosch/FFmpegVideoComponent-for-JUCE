#pragma once

#include "MediaReaderConfig.h"
#include "MediaReaderTypes.h"
#include "AudioBuffer.h"
#include "VideoBuffer.h"
#include <memory>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>

namespace cb_ffmpeg {

// Forward declarations for internal components
class FormatDetector;
class AudioDecoder;
class VideoDecoder;
class ImageLoader;
class SyncManager;
class TransportController;

/**
 * Universal media reader for audio, video, and image files
 * 
 * This is the main interface class that provides a unified API for loading
 * and playing back any supported media format using FFmpeg. It coordinates
 * multiple decoder threads, FIFO buffers, and synchronization to provide
 * smooth, thread-safe media playback.
 */
class MediaReader {
public:
    /**
     * Constructor
     * @param config Configuration for the media reader
     */
    MediaReader(const MediaReaderConfig& config = MediaReaderConfig{});
    
    /**
     * Destructor
     */
    ~MediaReader();
    
    // Disable copy and assignment
    MediaReader(const MediaReader&) = delete;
    MediaReader& operator=(const MediaReader&) = delete;
    
    // ========================================================================
    // File Loading
    // ========================================================================
    
    /**
     * Load a media file
     * @param file File to load
     * @return true if successful, false on error
     */
    bool loadFile(const juce::File& file);
    
    /**
     * Load media from memory
     * @param data Pointer to media data
     * @param size Size of media data in bytes
     * @param formatHint Optional format hint (e.g., "mp4", "wav")
     * @return true if successful, false on error
     */
    bool loadFromMemory(const void* data, size_t size, const juce::String& formatHint = {});
    
    /**
     * Unload current media and free resources
     */
    void unload();
    
    /**
     * Check if media is currently loaded
     */
    bool isLoaded() const { return mediaInfo_.type != MediaType::Unknown; }
    
    // ========================================================================
    // Transport Control
    // ========================================================================
    
    /**
     * Start playback
     */
    void play();
    
    /**
     * Pause playback
     */
    void pause();
    
    /**
     * Stop playback and reset to beginning
     */
    void stop();
    
    /**
     * Seek to specific time position
     * @param timeInSeconds Target time in seconds
     * @param mode Seek mode (accurate, fast, etc.)
     */
    void seek(double timeInSeconds, SeekMode mode = SeekMode::Accurate);
    
    /**
     * Set looping behavior
     * @param shouldLoop Whether to loop when reaching end
     */
    void setLooping(bool shouldLoop);
    
    /**
     * Get current playback state
     */
    PlaybackState getPlaybackState() const { return playbackState_.load(); }
    
    /**
     * Check if currently playing
     */
    bool isPlaying() const { return getPlaybackState() == PlaybackState::Playing; }
    
    /**
     * Check if currently paused
     */
    bool isPaused() const { return getPlaybackState() == PlaybackState::Paused; }
    
    /**
     * Check if looping is enabled
     */
    bool isLooping() const { return looping_.load(); }
    
    // ========================================================================
    // Position and Timing
    // ========================================================================
    
    /**
     * Get current playback position in seconds
     */
    double getCurrentPosition() const;
    
    /**
     * Get total duration in seconds
     */
    double getDuration() const { return mediaInfo_.duration; }
    
    /**
     * Get current playback progress (0.0 to 1.0)
     */
    double getProgress() const;
    
    /**
     * Set playback rate (1.0 = normal speed)
     * @param rate Playback rate (0.1 to 4.0)
     */
    void setPlaybackRate(double rate);
    
    /**
     * Get current playback rate
     */
    double getPlaybackRate() const;
    
    // ========================================================================
    // External Synchronization
    // ========================================================================
    
    /**
     * Set external synchronization interface
     * @param sync External sync interface (null to disable)
     */
    void setExternalSync(ExternalSyncInterface* sync);
    
    /**
     * Set position from external source (used with external sync)
     * @param timeInSeconds Position in seconds
     */
    void setExternalPosition(double timeInSeconds);
    
    /**
     * Get synchronization mode
     */
    SyncMode getSyncMode() const;
    
    /**
     * Set synchronization mode
     * @param mode Sync mode to use
     */
    void setSyncMode(SyncMode mode);
    
    // ========================================================================
    // Media Information
    // ========================================================================
    
    /**
     * Get media information
     */
    const MediaInfo& getMediaInfo() const { return mediaInfo_; }
    
    /**
     * Check if media has audio stream
     */
    bool hasAudio() const { return mediaInfo_.hasAudio(); }
    
    /**
     * Check if media has video stream
     */
    bool hasVideo() const { return mediaInfo_.hasVideo(); }
    
    /**
     * Check if media is a still image
     */
    bool isImage() const { return mediaInfo_.isImage(); }
    
    /**
     * Get audio stream information
     */
    const StreamInfo* getAudioStreamInfo() const { return mediaInfo_.getAudioStream(); }
    
    /**
     * Get video stream information
     */
    const StreamInfo* getVideoStreamInfo() const { return mediaInfo_.getVideoStream(); }
    
    // ========================================================================
    // JUCE Integration
    // ========================================================================
    
    /**
     * Get audio source for JUCE audio system
     * @return AudioSource that reads from internal audio buffer
     */
    juce::AudioSource* getAudioSource();
    
    /**
     * Get video component for JUCE UI
     * @return Component that displays video frames
     */
    juce::Component* getVideoComponent();
    
    /**
     * Get current image (for still images or video frames)
     * @return Current image, or invalid image if not available
     */
    juce::Image getCurrentImage();
    
    /**
     * Get video frame at specific time
     * @param timeInSeconds Time position
     * @param tolerance Time tolerance for frame selection
     * @return Video frame, or empty frame if not found
     */
    juce::Image getImageAtTime(double timeInSeconds, double tolerance = 0.040);
    
    // ========================================================================
    // Configuration and Statistics
    // ========================================================================
    
    /**
     * Set configuration
     * @param config New configuration
     */
    void setConfig(const MediaReaderConfig& config);
    
    /**
     * Get current configuration
     */
    const MediaReaderConfig& getConfig() const { return config_; }
    
    /**
     * Get decoder statistics
     */
    DecoderStats getAudioDecoderStats() const;
    DecoderStats getVideoDecoderStats() const;
    
    /**
     * Get buffer levels (0.0 to 1.0)
     */
    double getAudioBufferLevel() const;
    double getVideoBufferLevel() const;
    
    /**
     * Get synchronization information
     */
    SyncInfo getSyncInfo() const;
    
    /**
     * Reset all statistics
     */
    void resetStatistics();
    
    // ========================================================================
    // Event Callbacks
    // ========================================================================
    
    /**
     * Set callback for media events
     * @param callback Callback interface (null to disable)
     */
    void setCallback(MediaReaderCallback* callback);
    
    /**
     * Get current callback
     */
    MediaReaderCallback* getCallback() const { return callback_; }
    
    // ========================================================================
    // Advanced Features
    // ========================================================================
    
    /**
     * Pre-load media for instant playback
     * @param preloadDurationMs Amount to preload in milliseconds
     */
    void preload(size_t preloadDurationMs = 1000);
    
    /**
     * Flush all buffers (useful before seeking)
     */
    void flushBuffers();
    
    /**
     * Get last error message
     */
    juce::String getLastError() const;
    
    /**
     * Check if hardware decoding is available and active
     */
    bool isHardwareDecodingActive() const;
    
private:
    // Configuration
    MediaReaderConfig config_;
    
    // Media information
    MediaInfo mediaInfo_;
    
    // State management
    std::atomic<PlaybackState> playbackState_{PlaybackState::Stopped};
    std::atomic<bool> looping_{false};
    std::atomic<double> playbackRate_{1.0};
    std::atomic<SyncMode> syncMode_{SyncMode::Internal};
    
    // Threading and synchronization
    mutable std::mutex stateMutex_;
    std::condition_variable stateCondition_;
    std::atomic<bool> shouldStop_{false};
    
    // Core components
    std::unique_ptr<FormatDetector> formatDetector_;
    std::unique_ptr<AudioDecoder> audioDecoder_;
    std::unique_ptr<VideoDecoder> videoDecoder_;
    std::unique_ptr<ImageLoader> imageLoader_;
    std::unique_ptr<SyncManager> syncManager_;
    std::unique_ptr<TransportController> transportController_;
    
    // Buffers
    std::unique_ptr<AudioBuffer> audioBuffer_;
    std::unique_ptr<VideoBuffer> videoBuffer_;
    std::unique_ptr<VideoFramePool> framePool_;
    
    // JUCE integration
    std::unique_ptr<juce::AudioSource> audioSource_;
    std::unique_ptr<juce::Component> videoComponent_;
    
    // External interfaces
    ExternalSyncInterface* externalSync_{nullptr};
    MediaReaderCallback* callback_{nullptr};
    
    // Error handling
    mutable std::mutex errorMutex_;
    juce::String lastError_;
    
    // Threading
    std::thread decoderManagerThread_;
    std::atomic<bool> decoderThreadRunning_{false};
    
    // ========================================================================
    // Internal Methods
    // ========================================================================
    
    /**
     * Initialize all components
     */
    bool initialize();
    
    /**
     * Shutdown all components
     */
    void shutdown();
    
    /**
     * Main decoder management thread function
     */
    void decoderManagerLoop();
    
    /**
     * Update playback state
     */
    void setPlaybackState(PlaybackState newState);
    
    /**
     * Notify callback of event
     */
    void notifyCallback(std::function<void(MediaReaderCallback*)> notification);
    
    /**
     * Set error message
     */
    void setError(const juce::String& error);
    
    /**
     * Validate configuration and adjust if needed
     */
    void validateConfig();
    
    /**
     * Create and configure buffers based on media info
     */
    bool setupBuffers();
    
    /**
     * Start decoder threads
     */
    bool startDecoders();
    
    /**
     * Stop decoder threads
     */
    void stopDecoders();
    
    /**
     * Handle end of stream
     */
    void handleEndOfStream();
    
    /**
     * Synchronize audio and video
     */
    void updateSynchronization();
    
    /**
     * Check if seeking is needed
     */
    bool needsSeeking() const;
    
    /**
     * Perform actual seek operation
     */
    void performSeek(double targetTime, SeekMode mode);
};

} // namespace cb_ffmpeg 