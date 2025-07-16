#include "AudioDecoder.h"
#include <iostream>

namespace cb
{

AudioDecoder::AudioDecoder(std::shared_ptr<AudioBuffer> buffer, const MediaReaderConfig& config)
    : audioBuffer(buffer)
    , config(config)
    , shouldStop(false)
    , isPaused(false)
    , seekRequested(false)
    , seekTime(0.0)
    , currentTime(0.0)
    , streamIndex(-1)
{
}

AudioDecoder::~AudioDecoder()
{
    stop();
}

bool AudioDecoder::initialize(AVFormatContext* formatContext, int audioStreamIndex)
{
    if (!formatContext || audioStreamIndex < 0)
        return false;

    formatCtx = formatContext;
    streamIndex = audioStreamIndex;
    
    // Get audio stream
    AVStream* stream = formatCtx->streams[streamIndex];
    codecParams = stream->codecpar;
    
    // Find decoder
    const AVCodec* codec = avcodec_find_decoder(codecParams->codec_id);
    if (!codec)
    {
        if (config.enableLogging)
            std::cerr << "AudioDecoder: Could not find audio decoder" << std::endl;
        return false;
    }
    
    // Allocate codec context
    codecCtx = AVCodecContextPtr(avcodec_alloc_context3(codec));
    if (!codecCtx)
        return false;
    
    // Copy codec parameters
    if (avcodec_parameters_to_context(codecCtx.get(), codecParams) < 0)
        return false;
    
    // Open codec
    if (avcodec_open2(codecCtx.get(), codec, nullptr) < 0)
    {
        if (config.enableLogging)
            std::cerr << "AudioDecoder: Could not open audio codec" << std::endl;
        return false;
    }
    
    // Initialize resampler if needed
    if (!initializeResampler())
        return false;
    
    // Calculate time base
    timeBase = av_q2d(stream->time_base);
    
    return true;
}

bool AudioDecoder::initializeResampler()
{
    // Get input format
    AVSampleFormat inputFormat = codecCtx->sample_fmt;
    int inputSampleRate = codecCtx->sample_rate;
    AVChannelLayout inputChannelLayout;
    av_channel_layout_copy(&inputChannelLayout, &codecCtx->ch_layout);
    
    // Set output format
    AVSampleFormat outputFormat = AV_SAMPLE_FMT_FLT;
    int outputSampleRate = config.audioConfig.targetSampleRate > 0 ? 
                          config.audioConfig.targetSampleRate : inputSampleRate;
    
    AVChannelLayout outputChannelLayout;
    if (config.audioConfig.targetChannels > 0)
        av_channel_layout_default(&outputChannelLayout, config.audioConfig.targetChannels);
    else
        av_channel_layout_copy(&outputChannelLayout, &inputChannelLayout);
    
    // Check if resampling is needed
    bool needsResampling = inputFormat != outputFormat ||
                          inputSampleRate != outputSampleRate ||
                          av_channel_layout_compare(&inputChannelLayout, &outputChannelLayout) != 0;
    
    if (needsResampling)
    {
        // Allocate resampler
        swrCtx = SwrContextPtr(swr_alloc());
        if (!swrCtx)
            return false;
        
        // Set options
        av_opt_set_chlayout(swrCtx.get(), "in_chlayout", &inputChannelLayout, 0);
        av_opt_set_int(swrCtx.get(), "in_sample_rate", inputSampleRate, 0);
        av_opt_set_sample_fmt(swrCtx.get(), "in_sample_fmt", inputFormat, 0);
        
        av_opt_set_chlayout(swrCtx.get(), "out_chlayout", &outputChannelLayout, 0);
        av_opt_set_int(swrCtx.get(), "out_sample_rate", outputSampleRate, 0);
        av_opt_set_sample_fmt(swrCtx.get(), "out_sample_fmt", outputFormat, 0);
        
        // Initialize resampler
        if (swr_init(swrCtx.get()) < 0)
        {
            if (config.enableLogging)
                std::cerr << "AudioDecoder: Could not initialize resampler" << std::endl;
            return false;
        }
    }
    
    // Store output format
    outputChannels = outputChannelLayout.nb_channels;
    outputSampleRate = outputSampleRate;
    
    av_channel_layout_uninit(&inputChannelLayout);
    av_channel_layout_uninit(&outputChannelLayout);
    
    return true;
}

void AudioDecoder::start()
{
    if (decoderThread.joinable())
        return;
    
    shouldStop = false;
    decoderThread = std::thread(&AudioDecoder::decoderThreadFunction, this);
}

void AudioDecoder::stop()
{
    shouldStop = true;
    
    if (decoderThread.joinable())
        decoderThread.join();
}

void AudioDecoder::pause()
{
    isPaused = true;
}

void AudioDecoder::resume()
{
    isPaused = false;
}

void AudioDecoder::seek(double timeInSeconds)
{
    seekTime = timeInSeconds;
    seekRequested = true;
}

double AudioDecoder::getCurrentTime() const
{
    return currentTime;
}

bool AudioDecoder::isFinished() const
{
    return shouldStop;
}

void AudioDecoder::decoderThreadFunction()
{
    AVPacketPtr packet(av_packet_alloc());
    AVFramePtr frame(av_frame_alloc());
    
    if (!packet || !frame)
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
        if (audioBuffer->getAvailableSpace() < config.audioConfig.bufferSizeFrames / 4)
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
                    std::cerr << "AudioDecoder: Error reading frame: " << ret << std::endl;
                break;
            }
        }
        
        // Check if this packet belongs to our audio stream
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
                std::cerr << "AudioDecoder: Error sending packet to decoder: " << ret << std::endl;
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
                    std::cerr << "AudioDecoder: Error receiving frame: " << ret << std::endl;
                break;
            }
            
            // Update current time
            if (frame->pts != AV_NOPTS_VALUE)
                currentTime = frame->pts * timeBase;
            
            // Process frame
            if (!processFrame(frame.get()))
                break;
            
            av_frame_unref(frame.get());
        }
    }
    
    // Flush decoder
    flushDecoder();
}

bool AudioDecoder::processFrame(AVFrame* frame)
{
    if (!frame)
        return false;
    
    // Convert frame if needed
    if (swrCtx)
    {
        return processFrameWithResampling(frame);
    }
    else
    {
        return processFrameDirect(frame);
    }
}

bool AudioDecoder::processFrameDirect(AVFrame* frame)
{
    // Direct copy - frame format matches output format
    int numSamples = frame->nb_samples;
    int numChannels = frame->ch_layout.nb_channels;
    
    // Allocate temporary buffer
    std::vector<float> tempBuffer(numSamples * numChannels);
    
    // Copy and convert to float if needed
    if (frame->format == AV_SAMPLE_FMT_FLT)
    {
        // Planar float
        for (int ch = 0; ch < numChannels; ++ch)
        {
            const float* channelData = reinterpret_cast<const float*>(frame->data[ch]);
            for (int i = 0; i < numSamples; ++i)
            {
                tempBuffer[i * numChannels + ch] = channelData[i];
            }
        }
    }
    else if (frame->format == AV_SAMPLE_FMT_FLTP)
    {
        // Packed float - direct copy
        std::memcpy(tempBuffer.data(), frame->data[0], numSamples * numChannels * sizeof(float));
    }
    else
    {
        // Other formats - this shouldn't happen if resampler is working correctly
        if (config.enableLogging)
            std::cerr << "AudioDecoder: Unexpected audio format in direct processing" << std::endl;
        return false;
    }
    
    // Push to buffer
    return audioBuffer->push(tempBuffer.data(), numSamples);
}

bool AudioDecoder::processFrameWithResampling(AVFrame* frame)
{
    // Calculate output samples
    int outputSamples = swr_get_out_samples(swrCtx.get(), frame->nb_samples);
    if (outputSamples <= 0)
        return true; // Nothing to output
    
    // Allocate output buffer
    std::vector<float> outputBuffer(outputSamples * outputChannels);
    uint8_t* outputData[1] = { reinterpret_cast<uint8_t*>(outputBuffer.data()) };
    
    // Convert
    int convertedSamples = swr_convert(swrCtx.get(), outputData, outputSamples,
                                     const_cast<const uint8_t**>(frame->data), frame->nb_samples);
    
    if (convertedSamples < 0)
    {
        if (config.enableLogging)
            std::cerr << "AudioDecoder: Error in resampling: " << convertedSamples << std::endl;
        return false;
    }
    
    if (convertedSamples == 0)
        return true; // Nothing converted
    
    // Push to buffer
    return audioBuffer->push(outputBuffer.data(), convertedSamples);
}

void AudioDecoder::handleSeek()
{
    // Seek in format context
    int64_t seekTarget = static_cast<int64_t>(seekTime / timeBase);
    
    if (av_seek_frame(formatCtx, streamIndex, seekTarget, AVSEEK_FLAG_BACKWARD) < 0)
    {
        if (config.enableLogging)
            std::cerr << "AudioDecoder: Seek failed" << std::endl;
        return;
    }
    
    // Flush codec buffers
    avcodec_flush_buffers(codecCtx.get());
    
    // Clear audio buffer
    audioBuffer->clear();
    
    // Update current time
    currentTime = seekTime;
}

void AudioDecoder::flushDecoder()
{
    // Send NULL packet to flush
    avcodec_send_packet(codecCtx.get(), nullptr);
    
    AVFramePtr frame(av_frame_alloc());
    if (!frame)
        return;
    
    // Receive remaining frames
    while (true)
    {
        int ret = avcodec_receive_frame(codecCtx.get(), frame.get());
        if (ret == AVERROR_EOF || ret == AVERROR(EAGAIN))
            break;
        
        if (ret < 0)
            break;
        
        processFrame(frame.get());
        av_frame_unref(frame.get());
    }
}

} // namespace cb 