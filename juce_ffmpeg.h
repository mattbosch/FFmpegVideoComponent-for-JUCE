/*
  ==============================================================================

  BEGIN_JUCE_MODULE_DECLARATION

  ID:                 juce_ffmpeg
  vendor:             juce_ffmpeg
  version:            0.1.0
  name:               FFmpeg wrapper for handling video
  description:        Provides classes to read audio streams from video files or to
                      mux audio into an existing video
  dependencies:       juce_audio_basics juce_audio_devices juce_audio_formats juce_gui_basics juce_graphics juce_core juce_audio_utils juce_audio_processors
  minimumCppStandard: 17
  searchpaths:        ffmpeg/include
  windowsLibs:        avformat,avutil,avcodec,swscale,swresample
  OSXLibs:            avformat,avutil,avcodec,swscale,swresample
  website:            https://github.com/Cle3000/FFmpegVideoComponent-for-JUCE

  END_JUCE_MODULE_DECLARATION

  ==============================================================================
 */

#pragma once

#include <juce_core/juce_core.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>

#include "Source/cb_ffmpeg/AudioBufferFIFO.h"
#include "Source/cb_ffmpeg/FFmpegHelpers.h"
#include "Source/cb_ffmpeg/FFmpegVideoComponent.h"
#include "Source/cb_ffmpeg/FFmpegVideoDecodeThread.h"
#include "Source/cb_ffmpeg/FFmpegVideoFramesFIFO.h"
#include "Source/cb_ffmpeg/FFmpegVideoListener.h"
#include "Source/cb_ffmpeg/FFmpegVideoReader.h"
#include "Source/cb_ffmpeg/FFmpegVideoScaler.h"
#include "Source/cb_strings/StringHelper.h"
