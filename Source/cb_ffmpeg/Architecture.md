# MediaReader Architecture Design

## 🎯 Overview
Universal media reader module for JUCE that handles audio, video, and image files using FFmpeg APIs directly. Designed for thread-safe, asynchronous operation with smooth playback and external sync capabilities.

## 🏗️ Core Components

### 1. MediaReader (Main Interface)
- **Purpose**: Single entry point for all media operations
- **Thread**: Main/Audio thread
- **Responsibilities**:
  - File loading and format detection
  - Transport control (play, pause, seek, loop)
  - Coordinate between components
  - Provide JUCE-compatible interfaces

### 2. FormatDetector
- **Purpose**: Analyze media files and determine optimal decoding strategy
- **Thread**: Background thread
- **Responsibilities**:
  - Detect audio/video/image streams
  - Extract metadata (duration, sample rate, frame rate, etc.)
  - Configure decoder parameters

### 3. DecoderManager
- **Purpose**: Manage multiple decoder threads
- **Thread**: Background thread
- **Responsibilities**:
  - Spawn/manage AudioDecoder and VideoDecoder threads
  - Handle seeking operations across decoders
  - Coordinate decoder lifecycle

### 4. AudioDecoder
- **Purpose**: Decode audio streams using FFmpeg
- **Thread**: Dedicated audio decoder thread
- **Responsibilities**:
  - Read and decode audio packets
  - Resample to target format
  - Fill audio FIFO buffer
  - Handle audio-specific seeking

### 5. VideoDecoder  
- **Purpose**: Decode video streams using FFmpeg
- **Thread**: Dedicated video decoder thread
- **Responsibilities**:
  - Read and decode video packets
  - Convert pixel formats
  - Fill video FIFO buffer
  - Handle video-specific seeking

### 6. ImageLoader
- **Purpose**: Load static images
- **Thread**: Background thread
- **Responsibilities**:
  - Load and decode image files
  - Convert to JUCE-compatible formats
  - Cache for repeated access

### 7. AudioBuffer (Thread-Safe FIFO)
- **Purpose**: Buffer decoded audio samples
- **Thread**: Written by AudioDecoder, read by JUCE audio thread
- **Features**:
  - Lock-free ring buffer
  - Configurable size
  - Underrun/overrun detection
  - Sample rate conversion support

### 8. VideoBuffer (Thread-Safe FIFO)
- **Purpose**: Buffer decoded video frames
- **Thread**: Written by VideoDecoder, read by JUCE video thread
- **Features**:
  - Frame queue with timestamps
  - Memory pool for efficient allocation
  - Frame dropping for sync
  - Format conversion support

### 9. SyncManager
- **Purpose**: Maintain audio/video synchronization
- **Thread**: Main thread
- **Responsibilities**:
  - Calculate presentation timestamps
  - Handle AV sync drift
  - Coordinate with external timebases
  - Frame dropping/duplication decisions

### 10. TransportController
- **Purpose**: Handle playback state and seeking
- **Thread**: Main thread
- **Responsibilities**:
  - Play/pause state management
  - Seeking coordination
  - Loop point handling
  - External sync integration

## 🧵 Threading Model

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

## 📊 Data Flow

### Audio-Only Files (.mp3, .wav, .flac)
```
File → FormatDetector → AudioDecoder → AudioBuffer → JUCE Audio Callback
```

### Video-Only Files (.mov without audio)
```
File → FormatDetector → VideoDecoder → VideoBuffer → JUCE Video Component
```

### Audio-Video Files (.mp4, .mov)
```
File → FormatDetector → AudioDecoder → AudioBuffer → JUCE Audio Callback
                    └→ VideoDecoder → VideoBuffer → JUCE Video Component
                                            ↕
                                     SyncManager
```

### Image Files (.jpg, .png)
```
File → FormatDetector → ImageLoader → Direct JUCE Image
```

## 🔄 Synchronization Strategy

### Internal Sync (Default)
- Audio decoder sets master clock
- Video frames presented based on audio timeline
- SyncManager handles drift correction

### External Sync (Host-Controlled)
- External timeline drives both audio and video
- Seeking coordinated across all streams
- Frame-accurate positioning support

### Sync Tolerance
- Configurable AV sync tolerance (default: ±40ms)
- Frame dropping for catch-up
- Audio sample interpolation for minor adjustments

## 🛡️ Thread Safety

### Lock-Free Components
- AudioBuffer and VideoBuffer use lock-free ring buffers
- Atomic operations for state changes
- Memory barriers for ordering guarantees

### Synchronization Primitives
- std::condition_variable for decoder thread coordination
- std::atomic for simple state flags
- juce::CriticalSection only for complex state updates

### Memory Management
- Smart pointers for automatic lifetime management
- Memory pools for video frames to avoid allocation overhead
- RAII for FFmpeg resource cleanup

## 🎛️ Configuration Options

### Buffer Sizes
```cpp
struct MediaReaderConfig {
    size_t audioBufferSizeMs = 500;      // Audio buffer in milliseconds
    size_t videoBufferFrames = 30;       // Video frames to buffer
    size_t maxDecodeAhead = 1000;        // Max decode ahead in ms
    bool enableAVSync = true;            // Enable audio/video sync
    double syncToleranceMs = 40.0;       // AV sync tolerance
    int maxVideoWidth = 1920;            // Max video resolution
    int maxVideoHeight = 1080;
    bool enableHardwareDecoding = true;  // Use GPU acceleration if available
};
```

### Supported Formats
- **Audio**: MP3, WAV, FLAC, AAC, OGG, M4A
- **Video**: MP4, MOV, AVI, MKV, WEBM
- **Images**: JPEG, PNG, BMP, TIFF
- **Containers**: Automatically detected via FFmpeg

## 🚀 Performance Considerations

### Decoder Thread Priority
- High priority for audio decoder (real-time audio)
- Normal priority for video decoder
- Low priority for image loading

### Memory Usage
- Pre-allocated buffers to avoid runtime allocation
- Configurable buffer sizes based on available memory
- Automatic buffer adaptation for different media types

### CPU Optimization
- SIMD operations for format conversion
- Multi-threaded decoding where supported
- Hardware acceleration (GPU) when available

## 🔧 Integration Points

### JUCE Audio
```cpp
class MediaAudioSource : public juce::AudioSource {
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    // Reads from AudioBuffer FIFO
};
```

### JUCE Video
```cpp
class MediaVideoComponent : public juce::Component {
    void paint(juce::Graphics& g) override;
    // Reads from VideoBuffer FIFO
};
```

### External Sync
```cpp
class ExternalSyncInterface {
    virtual void setPosition(double timeInSeconds) = 0;
    virtual double getCurrentPosition() const = 0;
    virtual void setPlaybackRate(double rate) = 0;
};
```

## 📋 API Design Preview

```cpp
class MediaReader {
public:
    // File loading
    bool loadFile(const juce::File& file);
    bool loadFromMemory(const void* data, size_t size);
    
    // Transport control
    void play();
    void pause();
    void stop();
    void seek(double timeInSeconds);
    void setLooping(bool shouldLoop);
    
    // External sync
    void setExternalSync(ExternalSyncInterface* sync);
    void setPosition(double timeInSeconds);
    
    // Information
    double getDuration() const;
    bool hasAudio() const;
    bool hasVideo() const;
    bool isImage() const;
    
    // JUCE integration
    juce::AudioSource* getAudioSource();
    juce::Component* getVideoComponent();
    juce::Image getCurrentImage();
    
    // Configuration
    void setConfig(const MediaReaderConfig& config);
    MediaReaderConfig getConfig() const;
};
```

This architecture provides a robust, thread-safe foundation for universal media playback while maintaining clean separation of concerns and optimal performance characteristics. 