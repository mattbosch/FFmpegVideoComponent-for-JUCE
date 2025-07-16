#include "juce_ffmpeg.h"

/*
    This file is part of the juce_ffmpeg module.
    
    The cb_ffmpeg MediaReader system provides universal media support
    for audio, video, and image files using FFmpeg as the backend.
    
    To use the MediaReader system in your application:
    
    1. Call cb::initializeFFmpeg() once at startup
    2. Create MediaReader instances as needed
    3. Call cb::shutdownFFmpeg() once at shutdown
    
    Example:
        auto mediaReader = cb::createHighPerformanceReader();
        if (mediaReader->open("video.mp4")) {
            auto* audioSource = mediaReader->getAudioSource();
            auto* videoComponent = mediaReader->getVideoComponent();
            mediaReader->play();
        }
*/

// Include all cb_ffmpeg implementation files
#include "Source/cb_ffmpeg/MediaReaderTypes.cpp"
#include "Source/cb_ffmpeg/AudioBuffer.cpp"
#include "Source/cb_ffmpeg/VideoBuffer.cpp"
#include "Source/cb_ffmpeg/AudioDecoder.cpp"
#include "Source/cb_ffmpeg/VideoDecoder.cpp"
#include "Source/cb_ffmpeg/MediaAudioSource.cpp"
#include "Source/cb_ffmpeg/MediaVideoComponent.cpp"
#include "Source/cb_ffmpeg/MediaReader.cpp"
#include "Source/cb_ffmpeg/cb_ffmpeg.cpp"
