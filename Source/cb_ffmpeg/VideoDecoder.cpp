#include "VideoDecoder.h"
#include <iostream>

namespace cb
{

VideoDecoder::VideoDecoder(std::shared_ptr<VideoBuffer> buffer, const MediaReaderConfig& config)
    : videoBuffer(buffer)
    , config(config)
    , shouldStop(false)
    , isPaused(false)
    , seekRequested(false)
    , seekTime(0.0)
    , currentTime(0.0)
    , streamIndex(-1)
    , hwDeviceType(AV_HWDEVICE_TYPE_NONE)
{
}

VideoDecoder::~VideoDecoder()
{
    stop();
}

bool VideoDecoder::initialize(AVFormatContext* formatContext, int videoStreamIndex)
{
    if (!formatContext || videoStreamIndex < 0)
        return false;

    formatCtx = formatContext;
    streamIndex = videoStreamIndex;
    
    // Get video stream
    AVStream* stream = formatCtx->streams[streamIndex];
    codecParams = stream->codecpar;
    
    // Find decoder with hardware acceleration if enabled
    const AVCodec* codec = nullptr;
    if (config.videoConfig.enableHardwareAcceleration)
    {
        codec = findHardwareDecoder();
    }
    
    if (!codec)
    {
        codec = avcodec_find_decoder(codecParams->codec_id);
    }
    
    if (!codec)
    {
        if (config.enableLogging)
            std::cerr << "VideoDecoder: Could not find video decoder" << std::endl;
        return false;
    }
    
    // Allocate codec context
    codecCtx = AVCodecContextPtr(avcodec_alloc_context3(codec));
    if (!codecCtx)
        return false;
    
    // Copy codec parameters
    if (avcodec_parameters_to_context(codecCtx.get(), codecParams) < 0)
        return false;
    
    // Setup hardware context if needed
    if (hwDeviceType != AV_HWDEVICE_TYPE_NONE)
    {
        setupHardwareContext();
    }
    
    // Open codec
    if (avcodec_open2(codecCtx.get(), codec, nullptr) < 0)
    {
        if (config.enableLogging)
            std::cerr << "VideoDecoder: Could not open video codec" << std::endl;
        return false;
    }
    
    // Initialize scaling context if needed
    if (!initializeScaler())
        return false;
    
    // Calculate time base
    timeBase = av_q2d(stream->time_base);
    
    // Store frame rate
    AVRational frameRate = stream->avg_frame_rate;
    if (frameRate.num > 0 && frameRate.den > 0)
        frameDuration = av_q2d(av_inv_q(frameRate));
    else
        frameDuration = 1.0 / 30.0; // Default to 30fps
    
    return true;
}

const AVCodec* VideoDecoder::findHardwareDecoder()
{
    // Try different hardware acceleration types
    const AVHWDeviceType hwTypes[] = {
#ifdef __APPLE__
        AV_HWDEVICE_TYPE_VIDEOTOOLBOX,
#endif
#ifdef _WIN32
        AV_HWDEVICE_TYPE_D3D11VA,
        AV_HWDEVICE_TYPE_DXVA2,
#endif
#ifdef __linux__
        AV_HWDEVICE_TYPE_VAAPI,
        AV_HWDEVICE_TYPE_VDPAU,
#endif
        AV_HWDEVICE_TYPE_CUDA
    };
    
    for (auto hwType : hwTypes)
    {
        const AVCodec* codec = avcodec_find_decoder_by_name(getHardwareDecoderName(hwType).c_str());
        if (codec)
        {
            hwDeviceType = hwType;
            if (config.enableLogging)
                std::cout << "VideoDecoder: Using hardware decoder: " << codec->name << std::endl;
            return codec;
        }
    }
    
    return nullptr;
}

std::string VideoDecoder::getHardwareDecoderName(AVHWDeviceType type) const
{
    switch (codecParams->codec_id)
    {
        case AV_CODEC_ID_H264:
            switch (type)
            {
#ifdef __APPLE__
                case AV_HWDEVICE_TYPE_VIDEOTOOLBOX: return "h264_videotoolbox";
#endif
#ifdef _WIN32
                case AV_HWDEVICE_TYPE_D3D11VA: return "h264_d3d11va";
                case AV_HWDEVICE_TYPE_DXVA2: return "h264_dxva2";
#endif
                case AV_HWDEVICE_TYPE_CUDA: return "h264_cuvid";
                default: break;
            }
            break;
            
        case AV_CODEC_ID_H265:
            switch (type)
            {
#ifdef __APPLE__
                case AV_HWDEVICE_TYPE_VIDEOTOOLBOX: return "hevc_videotoolbox";
#endif
#ifdef _WIN32
                case AV_HWDEVICE_TYPE_D3D11VA: return "hevc_d3d11va";
                case AV_HWDEVICE_TYPE_DXVA2: return "hevc_dxva2";
#endif
                case AV_HWDEVICE_TYPE_CUDA: return "hevc_cuvid";
                default: break;
            }
            break;
            
        default:
            break;
    }
    
    return "";
}

bool VideoDecoder::setupHardwareContext()
{
    if (hwDeviceType == AV_HWDEVICE_TYPE_NONE)
        return true;
    
    // Create hardware device context
    int ret = av_hwdevice_ctx_create(&hwDeviceCtx, hwDeviceType, nullptr, nullptr, 0);
    if (ret < 0)
    {
        if (config.enableLogging)
            std::cerr << "VideoDecoder: Failed to create hardware device context" << std::endl;
        hwDeviceType = AV_HWDEVICE_TYPE_NONE;
        return false;
    }
    
    // Set hardware device context in codec
    codecCtx->hw_device_ctx = av_buffer_ref(hwDeviceCtx);
    
    return true;
}

bool VideoDecoder::initializeScaler()
{
    // Get input format
    int inputWidth = codecCtx->width;
    int inputHeight = codecCtx->height;
    AVPixelFormat inputFormat = codecCtx->pix_fmt;
    
    // Determine output format
    int outputWidth = config.videoConfig.targetWidth > 0 ? 
                     config.videoConfig.targetWidth : inputWidth;
    int outputHeight = config.videoConfig.targetHeight > 0 ? 
                      config.videoConfig.targetHeight : inputHeight;
    AVPixelFormat outputFormat = AV_PIX_FMT_RGB24; // Standard RGB for JUCE
    
    // Check if scaling/conversion is needed
    bool needsScaling = inputWidth != outputWidth ||
                       inputHeight != outputHeight ||
                       inputFormat != outputFormat;
    
    if (needsScaling)
    {
        // Create scaling context
        swsCtx = SwsContextPtr(sws_getContext(
            inputWidth, inputHeight, inputFormat,
            outputWidth, outputHeight, outputFormat,
            SWS_BILINEAR, nullptr, nullptr, nullptr
        ));
        
        if (!swsCtx)
        {
            if (config.enableLogging)
                std::cerr << "VideoDecoder: Could not create scaling context" << std::endl;
            return false;
        }
    }
    
    // Store output format
    this->outputWidth = outputWidth;
    this->outputHeight = outputHeight;
    this->outputFormat = outputFormat;
    
    return true;
}

void VideoDecoder::start()
{
    if (decoderThread.joinable())
        return;
    
    shouldStop = false;
    decoderThread = std::thread(&VideoDecoder::decoderThreadFunction, this);
}

void VideoDecoder::stop()
{
    shouldStop = true;
    
    if (decoderThread.joinable())
        decoderThread.join();
}

void VideoDecoder::pause()
{
    isPaused = true;
}

void VideoDecoder::resume()
{
    isPaused = false;
}

void VideoDecoder::seek(double timeInSeconds)
{
    seekTime = timeInSeconds;
    seekRequested = true;
}

double VideoDecoder::getCurrentTime() const
{
    return currentTime;
}

bool VideoDecoder::isFinished() const
{
    return shouldStop;
}

void VideoDecoder::decoderThreadFunction()
{
    AVPacketPtr packet(av_packet_alloc());
    AVFramePtr frame(av_frame_alloc());
    AVFramePtr hwFrame(av_frame_alloc());
    
    if (!packet || !frame || !hwFrame)
        return;
    
    while (!shouldStop)
    {
        // Handle seek requests
        if (seekRequested)
        {
            handleSeek();
            seekRequested = false;
        }
        
        // Pause handling
        if (isPaused)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }
        
        // Check buffer space
        if (videoBuffer->getQueueSize() >= config.videoConfig.maxQueueSize)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            continue;
        }
        
        // Read packet
        int ret = av_read_frame(formatCtx, packet.get());
        if (ret < 0)
        {
            if (ret == AVERROR_EOF)
            {
                // End of file - handle looping
                if (config.enableLooping)
                {
                    seek(0.0);
                    continue;
                }
                else
                {
                    shouldStop = true;
                    break;
                }
            }
            else
            {
                if (config.enableLogging)
                    std::cerr << "VideoDecoder: Error reading frame: " << ret << std::endl;
                break;
            }
        }
        
        // Check if this packet belongs to our video stream
        if (packet->stream_index != streamIndex)
        {
            av_packet_unref(packet.get());
            continue;
        }
        
        // Send packet to decoder
        ret = avcodec_send_packet(codecCtx.get(), packet.get());
        av_packet_unref(packet.get());
        
        if (ret < 0)
        {
            if (config.enableLogging)
                std::cerr << "VideoDecoder: Error sending packet to decoder: " << ret << std::endl;
            continue;
        }
        
        // Receive frames
        while (ret >= 0 && !shouldStop)
        {
            ret = avcodec_receive_frame(codecCtx.get(), frame.get());
            if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
                break;
            
            if (ret < 0)
            {
                if (config.enableLogging)
                    std::cerr << "VideoDecoder: Error receiving frame: " << ret << std::endl;
                break;
            }
            
            // Handle hardware frames
            AVFrame* processFrame = frame.get();
            if (frame->format == codecCtx->pix_fmt && hwDeviceType != AV_HWDEVICE_TYPE_NONE)
            {
                // Transfer from hardware to system memory
                ret = av_hwframe_transfer_data(hwFrame.get(), frame.get(), 0);
                if (ret < 0)
                {
                    if (config.enableLogging)
                        std::cerr << "VideoDecoder: Error transferring hardware frame" << std::endl;
                    continue;
                }
                processFrame = hwFrame.get();
            }
            
            // Update current time
            if (processFrame->pts != AV_NOPTS_VALUE)
                currentTime = processFrame->pts * timeBase;
            
            // Process frame
            if (!processVideoFrame(processFrame))
                break;
            
            av_frame_unref(frame.get());
            av_frame_unref(hwFrame.get());
        }
    }
    
    // Flush decoder
    flushDecoder();
}

bool VideoDecoder::processVideoFrame(AVFrame* frame)
{
    if (!frame)
        return false;
    
    // Calculate timestamp
    double timestamp = currentTime;
    
    // Convert/scale frame if needed
    if (swsCtx)
    {
        return processFrameWithScaling(frame, timestamp);
    }
    else
    {
        return processFrameDirect(frame, timestamp);
    }
}

bool VideoDecoder::processFrameDirect(AVFrame* frame, double timestamp)
{
    // Direct copy - frame format matches output format
    int width = frame->width;
    int height = frame->height;
    
    // Calculate data size
    int dataSize = av_image_get_buffer_size(static_cast<AVPixelFormat>(frame->format), 
                                           width, height, 1);
    if (dataSize < 0)
        return false;
    
    // Create video frame data
    std::vector<uint8_t> frameData(dataSize);
    
    // Copy frame data
    av_image_copy_to_buffer(frameData.data(), dataSize,
                           const_cast<const uint8_t**>(frame->data), frame->linesize,
                           static_cast<AVPixelFormat>(frame->format), width, height, 1);
    
    // Create video frame
    VideoFrame videoFrame;
    videoFrame.data = std::move(frameData);
    videoFrame.width = width;
    videoFrame.height = height;
    videoFrame.timestamp = timestamp;
    videoFrame.format = static_cast<AVPixelFormat>(frame->format);
    
    // Push to buffer
    return videoBuffer->push(std::move(videoFrame));
}

bool VideoDecoder::processFrameWithScaling(AVFrame* frame, double timestamp)
{
    // Allocate output frame
    AVFramePtr outputFrame(av_frame_alloc());
    if (!outputFrame)
        return false;
    
    // Set output frame properties
    outputFrame->width = outputWidth;
    outputFrame->height = outputHeight;
    outputFrame->format = outputFormat;
    
    // Allocate output buffer
    int ret = av_frame_get_buffer(outputFrame.get(), 32);
    if (ret < 0)
        return false;
    
    // Scale frame
    ret = sws_scale(swsCtx.get(),
                   const_cast<const uint8_t**>(frame->data), frame->linesize,
                   0, frame->height,
                   outputFrame->data, outputFrame->linesize);
    
    if (ret < 0)
    {
        if (config.enableLogging)
            std::cerr << "VideoDecoder: Error scaling frame: " << ret << std::endl;
        return false;
    }
    
    // Calculate data size
    int dataSize = av_image_get_buffer_size(outputFormat, outputWidth, outputHeight, 1);
    if (dataSize < 0)
        return false;
    
    // Create video frame data
    std::vector<uint8_t> frameData(dataSize);
    
    // Copy scaled data
    av_image_copy_to_buffer(frameData.data(), dataSize,
                           const_cast<const uint8_t**>(outputFrame->data), outputFrame->linesize,
                           outputFormat, outputWidth, outputHeight, 1);
    
    // Create video frame
    VideoFrame videoFrame;
    videoFrame.data = std::move(frameData);
    videoFrame.width = outputWidth;
    videoFrame.height = outputHeight;
    videoFrame.timestamp = timestamp;
    videoFrame.format = outputFormat;
    
    // Push to buffer
    return videoBuffer->push(std::move(videoFrame));
}

void VideoDecoder::handleSeek()
{
    // Seek in format context
    int64_t seekTarget = static_cast<int64_t>(seekTime / timeBase);
    
    if (av_seek_frame(formatCtx, streamIndex, seekTarget, AVSEEK_FLAG_BACKWARD) < 0)
    {
        if (config.enableLogging)
            std::cerr << "VideoDecoder: Seek failed" << std::endl;
        return;
    }
    
    // Flush codec buffers
    avcodec_flush_buffers(codecCtx.get());
    
    // Clear video buffer
    videoBuffer->clear();
    
    // Update current time
    currentTime = seekTime;
}

void VideoDecoder::flushDecoder()
{
    // Send NULL packet to flush
    avcodec_send_packet(codecCtx.get(), nullptr);
    
    AVFramePtr frame(av_frame_alloc());
    AVFramePtr hwFrame(av_frame_alloc());
    
    if (!frame || !hwFrame)
        return;
    
    // Receive remaining frames
    while (true)
    {
        int ret = avcodec_receive_frame(codecCtx.get(), frame.get());
        if (ret == AVERROR_EOF || ret == AVERROR(EAGAIN))
            break;
        
        if (ret < 0)
            break;
        
        // Handle hardware frames
        AVFrame* processFrame = frame.get();
        if (frame->format == codecCtx->pix_fmt && hwDeviceType != AV_HWDEVICE_TYPE_NONE)
        {
            ret = av_hwframe_transfer_data(hwFrame.get(), frame.get(), 0);
            if (ret >= 0)
                processFrame = hwFrame.get();
        }
        
        processVideoFrame(processFrame);
        av_frame_unref(frame.get());
        av_frame_unref(hwFrame.get());
    }
}

} // namespace cb 