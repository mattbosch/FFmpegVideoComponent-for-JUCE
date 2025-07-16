#include "MediaReaderTypes.h"

// FFmpeg includes
extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>
#include <libavutil/avutil.h>
#include <libavutil/error.h>
}

namespace cb_ffmpeg {

// ============================================================================
// FFmpeg RAII Deleters Implementation
// ============================================================================

namespace FFmpegRAII {

void FormatContextDeleter::operator()(AVFormatContext* ctx) const {
    if (ctx) {
        avformat_close_input(&ctx);
    }
}

void CodecContextDeleter::operator()(AVCodecContext* ctx) const {
    if (ctx) {
        avcodec_free_context(&ctx);
    }
}

void FrameDeleter::operator()(AVFrame* frame) const {
    if (frame) {
        av_frame_free(&frame);
    }
}

void PacketDeleter::operator()(AVPacket* packet) const {
    if (packet) {
        av_packet_free(&packet);
    }
}

void SwrContextDeleter::operator()(SwrContext* ctx) const {
    if (ctx) {
        swr_free(&ctx);
    }
}

void SwsContextDeleter::operator()(SwsContext* ctx) const {
    if (ctx) {
        sws_freeContext(ctx);
    }
}

} // namespace FFmpegRAII

// ============================================================================
// Global FFmpeg Initialization
// ============================================================================

namespace {
    std::atomic<bool> g_ffmpegInitialized{false};
    std::mutex g_initMutex;
}

bool initializeFFmpeg() {
    std::lock_guard<std::mutex> lock(g_initMutex);
    
    if (g_ffmpegInitialized.load()) {
        return true;
    }
    
    try {
        // Initialize FFmpeg libraries
        av_log_set_level(AV_LOG_WARNING); // Reduce log spam
        
        // Register all formats and codecs
        // Note: In newer FFmpeg versions, this is automatic
        #if LIBAVFORMAT_VERSION_INT < AV_VERSION_INT(58, 9, 100)
        av_register_all();
        #endif
        
        #if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(58, 9, 100)
        avcodec_register_all();
        #endif
        
        // Initialize network protocols
        avformat_network_init();
        
        g_ffmpegInitialized.store(true);
        return true;
    }
    catch (...) {
        return false;
    }
}

void shutdownFFmpeg() {
    std::lock_guard<std::mutex> lock(g_initMutex);
    
    if (!g_ffmpegInitialized.load()) {
        return;
    }
    
    // Cleanup network
    avformat_network_deinit();
    
    g_ffmpegInitialized.store(false);
}

bool isFFmpegInitialized() {
    return g_ffmpegInitialized.load();
}

// ============================================================================
// FFmpeg Utility Functions
// ============================================================================

juce::String getFFmpegErrorString(int errorCode) {
    char errorBuffer[AV_ERROR_MAX_STRING_SIZE];
    av_strerror(errorCode, errorBuffer, AV_ERROR_MAX_STRING_SIZE);
    return juce::String(errorBuffer);
}

juce::String getFFmpegVersionString() {
    return juce::String("FFmpeg ") + juce::String(av_version_info());
}

juce::StringArray getSupportedAudioCodecs() {
    juce::StringArray codecs;
    
    void* iter = nullptr;
    const AVCodec* codec = nullptr;
    
    while ((codec = av_codec_iterate(&iter)) != nullptr) {
        if (codec->type == AVMEDIA_TYPE_AUDIO && av_codec_is_decoder(codec)) {
            codecs.add(juce::String(codec->name));
        }
    }
    
    return codecs;
}

juce::StringArray getSupportedVideoCodecs() {
    juce::StringArray codecs;
    
    void* iter = nullptr;
    const AVCodec* codec = nullptr;
    
    while ((codec = av_codec_iterate(&iter)) != nullptr) {
        if (codec->type == AVMEDIA_TYPE_VIDEO && av_codec_is_decoder(codec)) {
            codecs.add(juce::String(codec->name));
        }
    }
    
    return codecs;
}

juce::StringArray getSupportedFormats() {
    juce::StringArray formats;
    
    void* iter = nullptr;
    const AVInputFormat* format = nullptr;
    
    while ((format = av_demuxer_iterate(&iter)) != nullptr) {
        if (format->extensions) {
            juce::String extensions(format->extensions);
            juce::StringArray extArray = juce::StringArray::fromTokens(extensions, ",", "");
            for (const auto& ext : extArray) {
                formats.addIfNotAlreadyThere(ext.trim());
            }
        }
    }
    
    return formats;
}

// ============================================================================
// Format Conversion Utilities
// ============================================================================

SampleFormat convertAVSampleFormat(AVSampleFormat avFormat) {
    switch (avFormat) {
        case AV_SAMPLE_FMT_U8:
        case AV_SAMPLE_FMT_U8P:
            return SampleFormat::UInt8;
            
        case AV_SAMPLE_FMT_S16:
        case AV_SAMPLE_FMT_S16P:
            return SampleFormat::Int16;
            
        case AV_SAMPLE_FMT_S32:
        case AV_SAMPLE_FMT_S32P:
            return SampleFormat::Int32;
            
        case AV_SAMPLE_FMT_FLT:
        case AV_SAMPLE_FMT_FLTP:
            return SampleFormat::Float32;
            
        case AV_SAMPLE_FMT_DBL:
        case AV_SAMPLE_FMT_DBLP:
            return SampleFormat::Float64;
            
        default:
            return SampleFormat::Unknown;
    }
}

AVSampleFormat convertToAVSampleFormat(SampleFormat format) {
    switch (format) {
        case SampleFormat::UInt8:
            return AV_SAMPLE_FMT_U8;
        case SampleFormat::Int16:
            return AV_SAMPLE_FMT_S16;
        case SampleFormat::Int32:
            return AV_SAMPLE_FMT_S32;
        case SampleFormat::Float32:
            return AV_SAMPLE_FMT_FLT;
        case SampleFormat::Float64:
            return AV_SAMPLE_FMT_DBL;
        default:
            return AV_SAMPLE_FMT_NONE;
    }
}

PixelFormat convertAVPixelFormat(AVPixelFormat avFormat) {
    switch (avFormat) {
        case AV_PIX_FMT_RGB24:
            return PixelFormat::RGB24;
        case AV_PIX_FMT_RGBA:
            return PixelFormat::RGBA;
        case AV_PIX_FMT_BGR24:
            return PixelFormat::BGR24;
        case AV_PIX_FMT_BGRA:
            return PixelFormat::BGRA;
        case AV_PIX_FMT_YUV420P:
            return PixelFormat::YUV420P;
        case AV_PIX_FMT_YUV422P:
            return PixelFormat::YUV422P;
        case AV_PIX_FMT_YUV444P:
            return PixelFormat::YUV444P;
        case AV_PIX_FMT_GRAY8:
            return PixelFormat::Gray8;
        case AV_PIX_FMT_GRAY16:
            return PixelFormat::Gray16;
        default:
            return PixelFormat::Unknown;
    }
}

AVPixelFormat convertToAVPixelFormat(PixelFormat format) {
    switch (format) {
        case PixelFormat::RGB24:
            return AV_PIX_FMT_RGB24;
        case PixelFormat::RGBA:
            return AV_PIX_FMT_RGBA;
        case PixelFormat::BGR24:
            return AV_PIX_FMT_BGR24;
        case PixelFormat::BGRA:
            return AV_PIX_FMT_BGRA;
        case PixelFormat::YUV420P:
            return AV_PIX_FMT_YUV420P;
        case PixelFormat::YUV422P:
            return AV_PIX_FMT_YUV422P;
        case PixelFormat::YUV444P:
            return AV_PIX_FMT_YUV444P;
        case PixelFormat::Gray8:
            return AV_PIX_FMT_GRAY8;
        case PixelFormat::Gray16:
            return AV_PIX_FMT_GRAY16;
        default:
            return AV_PIX_FMT_NONE;
    }
}

// ============================================================================
// Media Type Detection
// ============================================================================

MediaType detectMediaTypeFromCodec(AVCodecParameters* codecpar) {
    if (!codecpar) {
        return MediaType::Unknown;
    }
    
    switch (codecpar->codec_type) {
        case AVMEDIA_TYPE_AUDIO:
            return MediaType::AudioOnly;
        case AVMEDIA_TYPE_VIDEO:
            return MediaType::VideoOnly;
        default:
            return MediaType::Unknown;
    }
}

MediaType analyzeStreamsForMediaType(AVFormatContext* formatContext) {
    if (!formatContext) {
        return MediaType::Unknown;
    }
    
    bool hasAudio = false;
    bool hasVideo = false;
    
    for (unsigned int i = 0; i < formatContext->nb_streams; i++) {
        AVStream* stream = formatContext->streams[i];
        if (!stream || !stream->codecpar) {
            continue;
        }
        
        switch (stream->codecpar->codec_type) {
            case AVMEDIA_TYPE_AUDIO:
                hasAudio = true;
                break;
            case AVMEDIA_TYPE_VIDEO:
                // Check if it's a real video stream (not just cover art)
                if (!(stream->disposition & AV_DISPOSITION_ATTACHED_PIC)) {
                    hasVideo = true;
                }
                break;
            default:
                break;
        }
    }
    
    if (hasAudio && hasVideo) {
        return MediaType::AudioVideo;
    } else if (hasAudio) {
        return MediaType::AudioOnly;
    } else if (hasVideo) {
        return MediaType::VideoOnly;
    }
    
    return MediaType::Unknown;
}

// ============================================================================
// Stream Information Extraction
// ============================================================================

StreamInfo extractStreamInfo(AVStream* stream) {
    StreamInfo info;
    
    if (!stream || !stream->codecpar) {
        return info;
    }
    
    AVCodecParameters* codecpar = stream->codecpar;
    
    // Basic information
    info.streamIndex = stream->index;
    info.type = detectMediaTypeFromCodec(codecpar);
    
    // Codec information
    const AVCodec* codec = avcodec_find_decoder(codecpar->codec_id);
    if (codec) {
        info.codec = juce::String(codec->name);
    }
    
    // Duration and frame count
    if (stream->duration != AV_NOPTS_VALUE && stream->time_base.num > 0) {
        info.duration = static_cast<double>(stream->duration) * stream->time_base.num / stream->time_base.den;
    }
    
    // Type-specific information
    if (codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
        info.sampleRate = codecpar->sample_rate;
        info.channels = codecpar->channels;
        info.sampleFormat = convertAVSampleFormat(static_cast<AVSampleFormat>(codecpar->format));
        info.bitsPerSample = av_get_bits_per_sample(codecpar->codec_id);
        
        if (info.duration > 0 && info.sampleRate > 0) {
            info.frameCount = static_cast<int64_t>(info.duration * info.sampleRate);
        }
    }
    else if (codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
        info.width = codecpar->width;
        info.height = codecpar->height;
        info.pixelFormat = convertAVPixelFormat(static_cast<AVPixelFormat>(codecpar->format));
        
        // Frame rate calculation
        if (stream->r_frame_rate.num > 0 && stream->r_frame_rate.den > 0) {
            info.frameRate = static_cast<double>(stream->r_frame_rate.num) / stream->r_frame_rate.den;
        } else if (stream->avg_frame_rate.num > 0 && stream->avg_frame_rate.den > 0) {
            info.frameRate = static_cast<double>(stream->avg_frame_rate.num) / stream->avg_frame_rate.den;
        }
        
        // Aspect ratio
        if (codecpar->sample_aspect_ratio.num > 0 && codecpar->sample_aspect_ratio.den > 0) {
            info.aspectRatio = static_cast<double>(codecpar->sample_aspect_ratio.num) / codecpar->sample_aspect_ratio.den;
        } else {
            info.aspectRatio = static_cast<double>(info.width) / info.height;
        }
        
        // Frame count
        if (info.duration > 0 && info.frameRate > 0) {
            info.frameCount = static_cast<int64_t>(info.duration * info.frameRate);
        }
        
        // Interlacing
        info.isInterlaced = (codecpar->field_order != AV_FIELD_PROGRESSIVE &&
                           codecpar->field_order != AV_FIELD_UNKNOWN);
    }
    
    // Extract metadata
    AVDictionaryEntry* entry = nullptr;
    while ((entry = av_dict_get(stream->metadata, "", entry, AV_DICT_IGNORE_SUFFIX)) != nullptr) {
        info.metadata.set(juce::String(entry->key), juce::String(entry->value));
    }
    
    return info;
}

MediaInfo createMediaInfo(const juce::File& file, AVFormatContext* formatContext) {
    MediaInfo info;
    
    if (!formatContext) {
        return info;
    }
    
    // Basic file information
    info.file = file;
    info.fileSize = file.getSize();
    info.format = juce::String(formatContext->iformat->name);
    
    // Duration
    if (formatContext->duration != AV_NOPTS_VALUE) {
        info.duration = static_cast<double>(formatContext->duration) / AV_TIME_BASE;
    }
    
    // Extract stream information
    for (unsigned int i = 0; i < formatContext->nb_streams; i++) {
        StreamInfo streamInfo = extractStreamInfo(formatContext->streams[i]);
        info.streams.push_back(streamInfo);
        
        // Find primary audio and video streams
        if (streamInfo.type == MediaType::AudioOnly && info.audioStreamIndex < 0) {
            info.audioStreamIndex = static_cast<int>(i);
        }
        else if (streamInfo.type == MediaType::VideoOnly && info.videoStreamIndex < 0) {
            // Skip attached pictures (cover art)
            AVStream* stream = formatContext->streams[i];
            if (!(stream->disposition & AV_DISPOSITION_ATTACHED_PIC)) {
                info.videoStreamIndex = static_cast<int>(i);
            }
        }
    }
    
    // Determine overall media type
    info.type = analyzeStreamsForMediaType(formatContext);
    
    // Extract global metadata
    AVDictionaryEntry* entry = nullptr;
    while ((entry = av_dict_get(formatContext->metadata, "", entry, AV_DICT_IGNORE_SUFFIX)) != nullptr) {
        info.metadata.set(juce::String(entry->key), juce::String(entry->value));
    }
    
    return info;
}

// ============================================================================
// Error Handling Utilities
// ============================================================================

bool isFFmpegError(int result) {
    return result < 0;
}

bool isEndOfFile(int result) {
    return result == AVERROR_EOF;
}

bool isWouldBlock(int result) {
    return result == AVERROR(EAGAIN);
}

juce::String formatFFmpegError(const juce::String& operation, int errorCode) {
    return operation + ": " + getFFmpegErrorString(errorCode) + " (" + juce::String(errorCode) + ")";
}

// ============================================================================
// Time Conversion Utilities
// ============================================================================

double convertTimestamp(int64_t timestamp, AVRational timebase) {
    if (timestamp == AV_NOPTS_VALUE) {
        return -1.0;
    }
    return static_cast<double>(timestamp) * timebase.num / timebase.den;
}

int64_t convertToTimestamp(double timeInSeconds, AVRational timebase) {
    if (timeInSeconds < 0) {
        return AV_NOPTS_VALUE;
    }
    return static_cast<int64_t>(timeInSeconds * timebase.den / timebase.num);
}

double rescaleTimestamp(int64_t timestamp, AVRational fromTimebase, AVRational toTimebase) {
    if (timestamp == AV_NOPTS_VALUE) {
        return -1.0;
    }
    
    int64_t rescaled = av_rescale_q(timestamp, fromTimebase, toTimebase);
    return static_cast<double>(rescaled) * toTimebase.num / toTimebase.den;
}

} // namespace cb_ffmpeg 