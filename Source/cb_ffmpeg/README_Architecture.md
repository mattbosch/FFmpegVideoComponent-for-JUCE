# CB FFmpeg MediaReader System - Complete Architecture

## Overview

The CB FFmpeg MediaReader system is a comprehensive, universal media playback solution for JUCE applications. It provides seamless support for audio, video, and image files using FFmpeg as the backend, with professional-grade features including hardware acceleration, thread-safe operation, and real-time performance.

## System Architecture

### Core Design Principles

1. **Universal Compatibility**: Single interface for all media types (audio, video, images)
2. **Thread Safety**: Lock-free buffers and asynchronous decoding threads
3. **Performance**: Hardware acceleration, memory pooling, zero-copy where possible
4. **JUCE Integration**: Native AudioSource and Component integration
5. **Flexibility**: Configurable for different use cases (low latency, high quality, etc.)

### Component Overview

```
┌─────────────────────────────────────────────────────────────┐
│                     MediaReader (Main Controller)          │
├─────────────────────────────────────────────────────────────┤
│  • File management                                         │
│  • Stream discovery                                        │
│  • Component coordination                                  │
│  • Playback control                                       │
└─────────┬─────────────────────────────────────────────┬─────┘
          │                                             │
    ┌─────▼─────┐                                 ┌─────▼─────┐
    │   AUDIO   │                                 │   VIDEO   │
    │ PIPELINE  │                                 │ PIPELINE  │
    └─────┬─────┘                                 └─────┬─────┘
          │                                             │
    ┌─────▼─────┐    ┌───────────┐           ┌─────▼─────┐    ┌──────────────┐
    │AudioDecod-│───▶│AudioBuffer│──────────▶│VideoDecod-│───▶│ VideoBuffer  │
    │er Thread  │    │(Lock-free)│           │er Thread  │    │(Timestamp-   │
    │           │    │Ring Buffer│           │           │    │aware Queue)  │
    └───────────┘    └─────┬─────┘           └───────────┘    └──────┬───────┘
                           │                                         │
                     ┌─────▼─────┐                            ┌─────▼─────┐
                     │MediaAudio-│                            │MediaVideo-│
                     │Source     │                            │Component  │
                     │(JUCE      │                            │(JUCE      │
                     │AudioSrc)  │                            │Component) │
                     └───────────┘                            └───────────┘
```

## Component Details

### 1. MediaReader (Core Controller)

**File**: `MediaReader.h/.cpp`

Central coordinator managing all media operations:

- **File Management**: Opens, parses, and manages media files
- **Stream Discovery**: Identifies audio/video streams automatically  
- **Component Lifecycle**: Initializes and coordinates all subsystems
- **Playback Control**: Play, pause, stop, seek operations
- **Synchronization**: Maintains audio/video sync when both present

**Key Features**:
- Automatic stream detection and optimal configuration
- Thread-safe playback control
- Comprehensive error handling and logging
- Statistics and monitoring
- Format support detection

### 2. Audio Pipeline

#### AudioDecoder
**File**: `AudioDecoder.h/.cpp`

Asynchronous audio decoding thread:
- **FFmpeg Integration**: Native codec support for all audio formats
- **Resampling**: Automatic sample rate and channel conversion
- **Threading**: Dedicated decoder thread for smooth playback
- **Seeking**: Frame-accurate seeking with buffer management

#### AudioBuffer  
**File**: `AudioBuffer.h/.cpp`

Lock-free ring buffer optimized for real-time audio:
- **Lock-Free Design**: Uses atomic operations for thread safety
- **Partial Frame Support**: Handles incomplete frame reads gracefully
- **Statistics**: Comprehensive performance monitoring
- **Configurable Size**: Adjustable buffer size for latency/stability trade-offs

#### MediaAudioSource
**File**: `MediaAudioSource.h/.cpp`

JUCE AudioSource integration:
- **Native JUCE Integration**: Seamless AudioDeviceManager compatibility
- **Sample Rate Conversion**: Real-time resampling if needed
- **Channel Mapping**: Flexible mono/stereo/multichannel support
- **Volume Control**: Built-in gain adjustment

### 3. Video Pipeline

#### VideoDecoder
**File**: `VideoDecoder.h/.cpp`

Asynchronous video decoding with hardware acceleration:
- **Hardware Acceleration**: Platform-specific GPU decoding (VideoToolbox, D3D11, CUDA)
- **Format Conversion**: Automatic pixel format conversion for JUCE
- **Scaling**: Real-time video scaling and resolution adjustment
- **Frame Dropping**: Intelligent frame dropping for performance

#### VideoBuffer
**File**: `VideoBuffer.h/.cpp`

Timestamp-aware video frame buffer:
- **Timestamp Management**: Precise frame timing for smooth playback
- **Memory Pool**: Efficient frame memory management
- **Frame Dropping**: Automatic frame dropping when buffer full
- **Statistics**: Performance monitoring and diagnostics

#### MediaVideoComponent
**File**: `MediaVideoComponent.h/.cpp`

JUCE Component for video display:
- **Aspect Ratio Management**: Multiple scaling modes (fit, fill, stretch)
- **Pixel Format Support**: RGB24, RGBA, BGRA format support
- **Performance Optimized**: Efficient JUCE image conversion
- **Debug Overlay**: Optional frame information display

### 4. Support Systems

#### MediaReaderTypes
**File**: `MediaReaderTypes.h/.cpp`

Core types and utilities:
- **FFmpeg RAII Wrappers**: Automatic resource management
- **Type Definitions**: Common structures and enums
- **Utility Functions**: Format detection, stream extraction
- **Global Initialization**: FFmpeg setup and teardown

#### Configuration System
**File**: `MediaReaderConfig.h`

Comprehensive configuration management:
- **Preset Configurations**: Optimized configs for different use cases
- **Audio Settings**: Sample rate, channels, buffer sizes
- **Video Settings**: Resolution, hardware acceleration, scaling
- **Performance Tuning**: Thread priorities, buffer sizes, timeouts

## Configuration Presets

### Default Configuration
Balanced performance and quality for general use:
```cpp
auto config = MediaReaderConfig::createDefaultConfig();
```

### Audio-Only Configuration  
Optimized for audio-only playback:
```cpp
auto config = MediaReaderConfig::createAudioOnlyConfig();
```

### High Performance Configuration
Maximum performance for demanding applications:
```cpp
auto config = MediaReaderConfig::createHighPerformanceConfig();
```

### Low Latency Configuration
Minimal latency for real-time applications:
```cpp
auto config = MediaReaderConfig::createLowLatencyConfig();
```

## Threading Model

### Thread Architecture

1. **Main Thread**: MediaReader control and JUCE integration
2. **Audio Decoder Thread**: FFmpeg audio decoding
3. **Video Decoder Thread**: FFmpeg video decoding  
4. **JUCE Audio Thread**: Audio callback execution
5. **JUCE Message Thread**: UI updates and video rendering

### Synchronization

- **Lock-Free Buffers**: Audio and video buffers use atomic operations
- **Seek Synchronization**: Coordinated seeking across all threads
- **Pause/Resume**: Thread-safe state management
- **Resource Cleanup**: Proper thread shutdown and resource cleanup

## Memory Management

### RAII Resource Management
All FFmpeg resources use smart pointers with custom deleters:
```cpp
using AVFormatContextPtr = std::unique_ptr<AVFormatContext, AVFormatContextDeleter>;
using AVCodecContextPtr = std::unique_ptr<AVCodecContext, AVCodecContextDeleter>;
```

### Memory Pools
- **Video Frames**: Pooled frame buffers for efficient memory reuse
- **Audio Buffers**: Pre-allocated ring buffer memory
- **Zero-Copy**: Minimize memory copies where possible

## Error Handling

### Comprehensive Error Management
- **FFmpeg Error Codes**: Proper interpretation and logging
- **Graceful Degradation**: Continue operation when possible
- **User Feedback**: Clear error messages and recovery suggestions
- **Logging System**: Configurable logging levels and output

## Performance Features

### Audio Performance
- **Lock-Free Buffers**: No blocking in audio callback
- **Partial Frame Handling**: Minimal latency audio delivery
- **Sample Rate Conversion**: High-quality real-time resampling
- **Zero Underruns**: Sophisticated buffer management

### Video Performance  
- **Hardware Acceleration**: GPU decoding on all platforms
- **Frame Dropping**: Intelligent frame skipping under load
- **Memory Pool**: Efficient frame buffer management
- **Scaling Optimization**: Fast pixel format conversion

## Format Support

### Audio Formats
- **Compressed**: MP3, AAC, OGG Vorbis, FLAC, Opus
- **Uncompressed**: WAV, AIFF, raw PCM
- **Professional**: BWF, RF64, high sample rates
- **Streaming**: HTTP/HTTPS streams, RTMP

### Video Formats
- **Modern**: MP4, WebM, MKV, AVI
- **Streaming**: HLS, DASH, RTMP
- **Professional**: ProRes, DNxHD, uncompressed
- **Legacy**: Many legacy formats via FFmpeg

### Hardware Acceleration
- **macOS**: VideoToolbox (H.264, H.265, VP9)
- **Windows**: D3D11VA, DXVA2 (H.264, H.265)  
- **Linux**: VAAPI, VDPAU (H.264, H.265)
- **Cross-Platform**: NVIDIA CUDA (H.264, H.265)

## API Usage Examples

### Basic Audio Playback
```cpp
auto reader = cb::createAudioOnlyReader();
if (reader->open("audio.mp3")) {
    audioDeviceManager.setAudioCallback(reader->getAudioSource());
    reader->play();
}
```

### Video Playback with Audio
```cpp
auto reader = cb::createHighPerformanceReader();
if (reader->open("video.mp4")) {
    addAndMakeVisible(*reader->getVideoComponent());
    audioDeviceManager.setAudioCallback(reader->getAudioSource());
    reader->play();
}
```

### Custom Configuration
```cpp
MediaReaderConfig config;
config.audioConfig.targetSampleRate = 48000;
config.videoConfig.enableHardwareAcceleration = true;
config.videoConfig.targetWidth = 1920;
config.videoConfig.targetHeight = 1080;

auto reader = cb::createMediaReader(config);
```

## Integration Guide

### JUCE Project Integration

1. **Add Module**: Include juce_ffmpeg module in your project
2. **FFmpeg Setup**: Ensure FFmpeg libraries are available
3. **Initialize**: Call `cb::initializeFFmpeg()` at startup
4. **Create Reader**: Use factory functions or custom config
5. **Connect to JUCE**: Use getAudioSource() and getVideoComponent()

### Build Requirements

- **JUCE 7.0+**: Modern JUCE version required
- **C++17**: Required for smart pointers and modern features
- **FFmpeg 4.0+**: Recent FFmpeg version for best compatibility
- **CMake 3.15+**: For build system integration

## Future Extensions

### Planned Features
- **Image Support**: JPEG, PNG, TIFF image display
- **Playlist Support**: Multi-file playback queues
- **Effects Processing**: Real-time audio/video effects
- **Streaming Optimization**: Enhanced network streaming
- **Metadata Support**: ID3, MP4 metadata extraction

### Architecture Extensions
- **Plugin System**: Extensible codec and effect plugins
- **Multi-Instance**: Improved support for multiple readers
- **GPU Processing**: Advanced GPU compute integration
- **Network Caching**: Intelligent streaming cache management

This architecture provides a robust, scalable foundation for universal media playback in JUCE applications, with professional-grade performance and extensive format support. 