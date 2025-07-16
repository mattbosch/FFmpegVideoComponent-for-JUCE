# CB FFmpeg Universal Media Reader

A comprehensive, thread-safe media reader module for JUCE applications that provides universal support for audio, video, and image files using FFmpeg as the backend.

## 🎯 Features

- **Universal Format Support**: Audio (MP3, WAV, FLAC, AAC, OGG), Video (MP4, MOV, AVI, MKV), Images (JPEG, PNG, BMP, TIFF)
- **Thread-Safe Architecture**: Asynchronous decoding with lock-free FIFO buffers
- **Audio/Video Synchronization**: Precise sync with configurable tolerance
- **External Timeline Support**: Host-controlled playback for DAW integration
- **Hardware Acceleration**: GPU-accelerated decoding when available
- **Memory Efficient**: Smart frame pooling and configurable buffer sizes
- **Real-Time Performance**: Optimized for low-latency audio applications
- **JUCE Integration**: Seamless integration with JUCE audio and video systems

## 🏗️ Architecture

```
┌─────────────────┐    ┌──────────────────┐    ┌─────────────────┐
│   JUCE Audio    │    │   JUCE Video     │    │   Main Thread   │
│   Callback      │    │   Component      │    │   (UI/Control)  │
│   Thread        │    │   Thread         │    │                 │
└─────────┬───────┘    └─────────┬────────┘    └─────────┬───────┘
          │                      │                       │
          │ (read)               │ (read)                │ (control)
          ▼                      ▼                       ▼
┌─────────────────┐    ┌──────────────────┐    ┌─────────────────┐
│   AudioBuffer   │    │   VideoBuffer    │    │  MediaReader    │
│   (FIFO)        │    │   (FIFO)         │    │  (Coordinator)  │
└─────────┬───────┘    └─────────┬────────┘    └─────────┬───────┘
          ▲                      ▲                       │
          │ (write)              │ (write)               │ (control)
          │                      │                       ▼
┌─────────────────┐    ┌──────────────────┐    ┌─────────────────┐
│  AudioDecoder   │    │  VideoDecoder    │    │ DecoderManager  │
│  Thread         │    │  Thread          │    │ Thread          │
└─────────────────┘    └──────────────────┘    └─────────────────┘
```

### Core Components

1. **MediaReader**: Main interface coordinating all operations
2. **AudioDecoder/VideoDecoder**: Dedicated decoder threads using FFmpeg
3. **AudioBuffer/VideoBuffer**: Thread-safe FIFO buffers
4. **MediaAudioSource**: JUCE AudioSource integration
5. **MediaVideoComponent**: JUCE Component for video display
6. **SyncManager**: Audio/video synchronization
7. **FormatDetector**: Automatic format detection and configuration

## 🚀 Quick Start

### Basic Usage

```cpp
#include "cb_ffmpeg/cb_ffmpeg.h"

// Initialize module (once at startup)
cb_ffmpeg::initializeModule();

// Create media reader
auto mediaReader = std::make_unique<cb_ffmpeg::MediaReader>();

// Load and play media file
if (mediaReader->loadFile(mediaFile)) {
    // Get JUCE-compatible components
    auto* audioSource = mediaReader->getAudioSource();
    auto* videoComponent = mediaReader->getVideoComponent();
    
    // Add to your JUCE application
    audioDeviceManager.addAudioCallback(audioSource);
    addAndMakeVisible(videoComponent);
    
    // Start playback
    mediaReader->play();
}

// Cleanup (once at shutdown)
cb_ffmpeg::shutdownModule();
```

### Advanced Configuration

```cpp
// Create high-quality configuration
auto config = cb_ffmpeg::MediaReaderConfig::createHighQualityConfig();
config.enableHardwareDecoding = true;
config.audioBufferSizeMs = 1000;
config.videoBufferFrames = 60;
config.maxVideoWidth = 3840;
config.maxVideoHeight = 2160;

auto mediaReader = std::make_unique<cb_ffmpeg::MediaReader>(config);
```

### Audio-Only Playback

```cpp
auto audioReader = cb_ffmpeg::Utils::createAudioOnlyReader();
if (audioReader->loadFile(audioFile)) {
    audioReader->setLooping(true);
    audioReader->play();
}
```

### External Synchronization (DAW Integration)

```cpp
class MyExternalSync : public cb_ffmpeg::ExternalSyncInterface {
public:
    void setPosition(double timeInSeconds) override {
        // Update your timeline
        timeline.setPosition(timeInSeconds);
    }
    
    double getCurrentPosition() const override {
        return timeline.getCurrentPosition();
    }
    
    // ... implement other methods
};

auto externalSync = std::make_unique<MyExternalSync>();
mediaReader->setExternalSync(externalSync.get());
mediaReader->setSyncMode(cb_ffmpeg::SyncMode::External);
```

## 📋 API Reference

### MediaReader Main Interface

```cpp
class MediaReader {
public:
    // File Loading
    bool loadFile(const juce::File& file);
    bool loadFromMemory(const void* data, size_t size, const juce::String& formatHint = {});
    void unload();
    
    // Transport Control
    void play();
    void pause();
    void stop();
    void seek(double timeInSeconds, SeekMode mode = SeekMode::Accurate);
    void setLooping(bool shouldLoop);
    
    // Position and Timing
    double getCurrentPosition() const;
    double getDuration() const;
    double getProgress() const;
    void setPlaybackRate(double rate);
    
    // External Synchronization
    void setExternalSync(ExternalSyncInterface* sync);
    void setSyncMode(SyncMode mode);
    
    // Media Information
    const MediaInfo& getMediaInfo() const;
    bool hasAudio() const;
    bool hasVideo() const;
    bool isImage() const;
    
    // JUCE Integration
    juce::AudioSource* getAudioSource();
    juce::Component* getVideoComponent();
    juce::Image getCurrentImage();
    
    // Configuration and Statistics
    void setConfig(const MediaReaderConfig& config);
    DecoderStats getAudioDecoderStats() const;
    DecoderStats getVideoDecoderStats() const;
    double getAudioBufferLevel() const;
    double getVideoBufferLevel() const;
};
```

### Configuration Options

```cpp
struct MediaReaderConfig {
    // Buffer Configuration
    size_t audioBufferSizeMs = 500;
    size_t videoBufferFrames = 30;
    size_t maxDecodeAhead = 1000;
    
    // Synchronization Settings
    bool enableAVSync = true;
    double syncToleranceMs = 40.0;
    bool allowFrameDropping = true;
    
    // Video Configuration
    int maxVideoWidth = 1920;
    int maxVideoHeight = 1080;
    bool enableHardwareDecoding = true;
    
    // Audio Configuration
    int targetSampleRate = 44100;
    int targetChannels = 2;
    double audioGain = 1.0;
    
    // Threading Configuration
    int audioDecoderThreadPriority = 8;
    int videoDecoderThreadPriority = 5;
    bool useMultiThreadedDecoding = true;
    
    // Factory methods
    static MediaReaderConfig createLowLatencyConfig();
    static MediaReaderConfig createHighQualityConfig();
    static MediaReaderConfig createMemoryEfficientConfig();
};
```

## 🎛️ Performance Tuning

### Low Latency Audio

```cpp
auto config = cb_ffmpeg::MediaReaderConfig::createLowLatencyConfig();
config.audioBufferSizeMs = 100;        // Smaller buffer
config.audioDecoderThreadPriority = 10; // Highest priority
config.enablePreloading = false;        // Disable preloading
config.syncToleranceMs = 20.0;          // Tighter sync
```

### High Quality Video

```cpp
auto config = cb_ffmpeg::MediaReaderConfig::createHighQualityConfig();
config.maxVideoWidth = 3840;            // 4K support
config.maxVideoHeight = 2160;
config.videoBufferFrames = 60;          // Larger buffer
config.enableHardwareDecoding = true;   // GPU acceleration
config.useMultiThreadedDecoding = true; // Multi-threading
```

### Memory Constrained

```cpp
auto config = cb_ffmpeg::MediaReaderConfig::createMemoryEfficientConfig();
config.audioBufferSizeMs = 250;         // Smaller audio buffer
config.videoBufferFrames = 15;          // Fewer video frames
config.maxVideoWidth = 1280;            // Lower resolution limit
config.enableMemoryMapping = false;     // Disable memory mapping
```

## 🔧 Build Configuration

### CMake Integration

Add to your CMakeLists.txt:

```cmake
# Add FFmpeg libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(FFMPEG REQUIRED
    libavformat
    libavcodec
    libswresample
    libswscale
    libavutil
)

# Link libraries
target_link_libraries(your_target
    ${FFMPEG_LIBRARIES}
    # ... other JUCE libraries
)

# Include directories
target_include_directories(your_target PRIVATE
    ${FFMPEG_INCLUDE_DIRS}
    # ... other includes
)
```

### Required FFmpeg Components

- libavformat (container formats)
- libavcodec (audio/video codecs)
- libswresample (audio resampling)
- libswscale (video scaling)
- libavutil (utilities)

Optional for hardware decoding:
- libavdevice (hardware devices)

## 🐛 Debugging and Monitoring

### Enable Debug Logging

```cpp
cb_ffmpeg::Debug::setDebugLogging(true);
cb_ffmpeg::Debug::setPerformanceLogging(true);
```

### Monitor Performance

```cpp
// Get decoder statistics
auto audioStats = mediaReader->getAudioDecoderStats();
auto videoStats = mediaReader->getVideoDecoderStats();

std::cout << "Audio frames decoded: " << audioStats.framesDecoded << std::endl;
std::cout << "Video frames dropped: " << videoStats.framesDropped << std::endl;
std::cout << "Buffer levels: Audio " << mediaReader->getAudioBufferLevel() 
          << ", Video " << mediaReader->getVideoBufferLevel() << std::endl;
```

### Check Sync Status

```cpp
auto syncInfo = mediaReader->getSyncInfo();
if (!syncInfo.isInSync) {
    std::cout << "Sync offset: " << syncInfo.offset << " seconds" << std::endl;
}
```

## ⚠️ Known Limitations

1. **Thread Safety**: MediaReader methods should be called from the main thread unless specifically documented as thread-safe
2. **Hardware Decoding**: Availability depends on system hardware and drivers
3. **Memory Usage**: Video buffers can consume significant memory for high-resolution content
4. **Seeking Accuracy**: Depends on keyframe placement in the source media
5. **Format Support**: Limited by the specific FFmpeg build and enabled codecs

## 🤝 Integration Examples

### DAW Plugin Integration

```cpp
class AudioProcessor : public juce::AudioProcessor {
private:
    std::unique_ptr<cb_ffmpeg::MediaReader> mediaReader_;
    std::unique_ptr<cb_ffmpeg::ExternalSyncInterface> sync_;
    
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock) override {
        // Initialize MediaReader with DAW settings
        auto config = cb_ffmpeg::MediaReaderConfig::createLowLatencyConfig();
        config.targetSampleRate = static_cast<int>(sampleRate);
        mediaReader_ = std::make_unique<cb_ffmpeg::MediaReader>(config);
        
        // Set up external sync
        sync_ = std::make_unique<DAWExternalSync>(*this);
        mediaReader_->setExternalSync(sync_.get());
        mediaReader_->setSyncMode(cb_ffmpeg::SyncMode::External);
    }
    
    void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&) override {
        // Update position for sync
        double currentTime = getPlayHead()->getPosition()->getTimeInSeconds().orFallback(0.0);
        mediaReader_->setExternalPosition(currentTime);
        
        // Get audio from MediaReader
        if (auto* audioSource = mediaReader_->getAudioSource()) {
            juce::AudioSourceChannelInfo info(&buffer, 0, buffer.getNumSamples());
            audioSource->getNextAudioBlock(info);
        }
    }
};
```

### Video Player Application

```cpp
class VideoPlayerComponent : public juce::Component {
private:
    std::unique_ptr<cb_ffmpeg::MediaReader> mediaReader_;
    std::unique_ptr<juce::AudioDeviceManager> audioDeviceManager_;
    
public:
    VideoPlayerComponent() {
        // Create MediaReader optimized for video
        mediaReader_ = cb_ffmpeg::Utils::createVideoReader();
        
        // Set up audio device
        audioDeviceManager_ = std::make_unique<juce::AudioDeviceManager>();
        audioDeviceManager_->initialiseWithDefaultDevices(0, 2);
    }
    
    void loadVideo(const juce::File& videoFile) {
        if (mediaReader_->loadFile(videoFile)) {
            // Add audio source
            if (auto* audioSource = mediaReader_->getAudioSource()) {
                audioDeviceManager_->addAudioCallback(audioSource);
            }
            
            // Add video component
            if (auto* videoComponent = mediaReader_->getVideoComponent()) {
                addAndMakeVisible(videoComponent);
                resized();
            }
        }
    }
    
    void resized() override {
        if (auto* videoComponent = mediaReader_->getVideoComponent()) {
            videoComponent->setBounds(getLocalBounds());
        }
    }
};
```

## 📄 License

This module uses FFmpeg libraries which are licensed under LGPL. Please ensure compliance with FFmpeg licensing terms in your application.

## 🔗 Dependencies

- JUCE Framework (GPL/Commercial)
- FFmpeg Libraries (LGPL/GPL)
- C++17 compatible compiler
- CMake 3.15+ (recommended) 