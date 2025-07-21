#include "AudioDecoder.h"

namespace cb_ffmpeg
{

AudioDecoder::AudioDecoder(AudioBuffer& audioBuffer, const MediaReaderConfig& config)
    : config_(config), audioBuffer_(audioBuffer)
{
}

AudioDecoder::~AudioDecoder()
{
    stop();
    
    // Clean up FFmpeg resources
    if (swrContext_)
    {
        swr_free(&swrContext_);
    }
    
    if (codecContext_)
    {
        avcodec_free_context(&codecContext_);
    }
    
    // Note: formatContext_ is not owned by us, so don't free it
}

bool AudioDecoder::initialize(AVFormatContext* formatContext, int streamIndex)
{
    if (!formatContext || streamIndex < 0)
    {
        setError("Invalid format context or stream index");
        return false;
    }
    
    // Store raw pointer - we don't own this
    formatContext_ = formatContext;
    streamIndex_ = streamIndex;
    audioStream_ = formatContext->streams[streamIndex];
    
    if (!audioStream_)
    {
        setError("Audio stream not found");
        return false;
    }
    
    // Find the decoder for the audio stream
    const AVCodec* codec = avcodec_find_decoder(audioStream_->codecpar->codec_id);
    if (!codec)
    {
        setError("Audio codec not found");
        return false;
    }
    
    // Allocate codec context - use raw pointer for now
    AVCodecContext* codecCtx = avcodec_alloc_context3(codec);
    if (!codecCtx)
    {
        setError("Could not allocate audio codec context");
        return false;
    }
    
    // Copy codec parameters from input stream to output codec context
    if (avcodec_parameters_to_context(codecCtx, audioStream_->codecpar) < 0)
    {
        avcodec_free_context(&codecCtx);
        setError("Could not copy audio codec parameters");
        return false;
    }
    
    // Open codec
    if (avcodec_open2(codecCtx, codec, nullptr) < 0)
    {
        avcodec_free_context(&codecCtx);
        setError("Could not open audio codec");
        return false;
    }
    
    // Store the codec context
    codecContext_ = codecCtx;
    
    // Extract stream info for MediaReader
    streamInfo_.type = MediaType::AudioOnly;
    streamInfo_.sampleRate = codecCtx->sample_rate;
    streamInfo_.channels = codecCtx->ch_layout.nb_channels;
    streamInfo_.duration = (double)audioStream_->duration * av_q2d(audioStream_->time_base);
    streamInfo_.bitRate = codecCtx->bit_rate;
    
    // Set up resampling if needed
    targetSampleRate_ = config_.targetSampleRate;
    targetChannels_ = config_.targetChannels;
    needsResampling_ = (codecCtx->sample_rate != targetSampleRate_ || 
                       codecCtx->ch_layout.nb_channels != targetChannels_);
    
    if (needsResampling_)
    {
        // Set up software resampler
        SwrContext* swrCtx = nullptr;
        AVChannelLayout targetChannelLayout = AV_CHANNEL_LAYOUT_STEREO;
        swr_alloc_set_opts2(&swrCtx,
                           &targetChannelLayout, AV_SAMPLE_FMT_FLT, targetSampleRate_,
                           &codecCtx->ch_layout, codecCtx->sample_fmt, codecCtx->sample_rate,
                           0, nullptr);
        
        if (swr_init(swrCtx) < 0)
        {
            swr_free(&swrCtx);
            setError("Could not initialize resampler");
            return false;
        }
        
        swrContext_ = swrCtx;
    }
    
    state_.store(DecoderState::Ready);
    juce::Logger::writeToLog("AudioDecoder initialized successfully - " + 
                            juce::String(streamInfo_.sampleRate) + "Hz, " + 
                            juce::String(streamInfo_.channels) + " channels");
    
    return true;
}

bool AudioDecoder::start()
{
    if (state_.load() != DecoderState::Ready)
    {
        setError("Decoder not ready to start");
        return false;
    }
    
    if (decoderThread_.joinable())
    {
        setError("Decoder thread already running");
        return false;
    }
    
    shouldStop_.store(false);
    shouldSeek_.store(false);
    
    try
    {
        decoderThread_ = std::thread(&AudioDecoder::decoderLoop, this);
        state_.store(DecoderState::Decoding);
        juce::Logger::writeToLog("AudioDecoder started successfully");
        return true;
    }
    catch (const std::exception& e)
    {
        setError("Failed to start decoder thread: " + juce::String(e.what()));
        return false;
    }
}

void AudioDecoder::stop()
{
    shouldStop_.store(true);
    
    if (decoderThread_.joinable())
    {
        decoderThread_.join();
    }
    
    // Reset timestamp to 0 so we start from beginning when restarted
    currentTimestamp_.store(0.0);
    
    state_.store(DecoderState::Ready);
    juce::Logger::writeToLog("AudioDecoder stopped and reset to beginning");
}

void AudioDecoder::seek(double timeInSeconds, SeekMode mode)
{
    juce::Logger::writeToLog("AudioDecoder::seek() called - Target: " + juce::String(timeInSeconds) + " seconds");
    
    if (state_.load() != DecoderState::Decoding) {
        juce::Logger::writeToLog("AudioDecoder: Cannot seek - decoder not running");
        return;
    }
    
    // Set seek parameters atomically
    seekTarget_.store(timeInSeconds);
    seekMode_.store(mode);
    
    // Signal the decoder thread to perform seek
    shouldSeek_.store(true);
    
    juce::Logger::writeToLog("AudioDecoder: Seek request queued for " + juce::String(timeInSeconds) + " seconds");
}

void AudioDecoder::flush()
{
    juce::Logger::writeToLog("AudioDecoder::flush() called");
    
    // Clear the audio buffer
    audioBuffer_.clear();
    
    // Flush codec buffers if available
    if (codecContext_) {
        avcodec_flush_buffers(codecContext_);
        juce::Logger::writeToLog("AudioDecoder: Codec buffers flushed");
    }
    
    // Reset timestamp
    currentTimestamp_.store(0.0);
    
    juce::Logger::writeToLog("AudioDecoder: Flush completed");
}

void AudioDecoder::setPlaybackRate(double rate)
{
}

juce::String AudioDecoder::getLastError() const
{
    return juce::String();
}

void AudioDecoder::decoderLoop()
{
    AVPacket* packet = av_packet_alloc();
    AVFrame* frame = av_frame_alloc();
    
    if (!packet || !frame)
    {
        setError("Could not allocate packet or frame");
        state_.store(DecoderState::Error);
        return;
    }
    
    juce::Logger::writeToLog("AudioDecoder: Starting decoder loop");
    
    // Check if we need to seek to current timestamp at start (e.g., after restart)
    double startTime = currentTimestamp_.load();
    if (startTime >= 0.0)
    {
        juce::Logger::writeToLog("AudioDecoder: Seeking to start position " + juce::String(startTime) + " seconds");
        
        // Convert time to stream timebase and seek
        if (formatContext_ && audioStream_)
        {
            int64_t seekTarget = static_cast<int64_t>(startTime / av_q2d(audioStream_->time_base));
            int ret = av_seek_frame(formatContext_, streamIndex_, seekTarget, AVSEEK_FLAG_ANY);
            if (ret >= 0)
            {
                // Flush codec buffers after seek
                if (codecContext_)
                {
                    avcodec_flush_buffers(codecContext_);
                }
                juce::Logger::writeToLog("AudioDecoder: Successfully seeked to start position");
            }
            else
            {
                juce::Logger::writeToLog("AudioDecoder: Failed to seek to start position");
            }
        }
    }
    
    while (!shouldStop_.load())
    {
        // Handle seeking
        if (shouldSeek_.load())
        {
            performSeek();
            shouldSeek_.store(false);
        }
        
        // Read packet from input
        int ret = av_read_frame(formatContext_, packet);
        
        if (ret < 0)
        {
            if (ret == AVERROR_EOF)
            {
                // End of file - flush decoder
                juce::Logger::writeToLog("AudioDecoder: End of file reached");
                state_.store(DecoderState::EndOfStream);
                break;
            }
            else if (ret == AVERROR(EAGAIN))
            {
                // Would block - try again
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                continue;
            }
            else
            {
                char errbuf[128];
                av_strerror(ret, errbuf, sizeof(errbuf));
                setError("Error reading frame: " + juce::String(errbuf));
                state_.store(DecoderState::Error);
                break;
            }
        }
        
        // Check if this packet belongs to our audio stream
        if (packet->stream_index == streamIndex_)
        {
            // Wait for buffer space without dropping packets
            while (audioBuffer_.getBufferLevel() > 0.8 && !shouldStop_.load()) // More than 80% full
            {
                juce::Logger::writeToLog("AudioDecoder: Buffer nearly full (" + juce::String(audioBuffer_.getBufferLevel() * 100, 1) + "%), waiting for space...");
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
            }
            
            // If we're stopping, break out
            if (shouldStop_.load()) {
                break;
            }
            
            // Decode the packet
            if (!decodePacket(packet))
            {
                juce::Logger::writeToLog("AudioDecoder: Failed to decode packet");
                // Continue with next packet instead of stopping
            }
        }
        
        av_packet_unref(packet);
    }
    
    // Clean up
    av_packet_free(&packet);
    av_frame_free(&frame);
    
    juce::Logger::writeToLog("AudioDecoder: Decoder loop finished");
}

bool AudioDecoder::initializeCodec()
{
    return false;
}

bool AudioDecoder::initializeResampler()
{
    return false;
}

bool AudioDecoder::decodePacket(AVPacket* packet)
{
    if (!packet || !codecContext_)
    {
        return false;
    }
    
    // Send packet to decoder
    int ret = avcodec_send_packet(codecContext_, packet);
    if (ret < 0 && ret != AVERROR(EAGAIN))
    {
        char errbuf[128];
        av_strerror(ret, errbuf, sizeof(errbuf));
        juce::Logger::writeToLog("Error sending packet to decoder: " + juce::String(errbuf) + 
                                " (error code: " + juce::String(ret) + ")");
        return false;
    }
    
    if (ret == AVERROR(EAGAIN))
    {
        juce::Logger::writeToLog("AudioDecoder: Decoder busy (EAGAIN), trying to receive frames first");
    }
    
    // Receive decoded frames
    AVFrame* frame = av_frame_alloc();
    if (!frame)
    {
        return false;
    }
    
    bool success = false;
    while (true)
    {
        ret = avcodec_receive_frame(codecContext_, frame);
        
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
        {
            // No more frames available
            break;
        }
        else if (ret < 0)
        {
            char errbuf[128];
            av_strerror(ret, errbuf, sizeof(errbuf));
            juce::Logger::writeToLog("Error receiving frame from decoder: " + juce::String(errbuf));
            break;
        }
        
        // Process the decoded frame
        if (processFrame(frame))
        {
            success = true;
        }
        else
        {
            juce::Logger::writeToLog("AudioDecoder: Failed to process decoded frame");
        }
        
        av_frame_unref(frame);
    }
    
    av_frame_free(&frame);
    return success;
}

bool AudioDecoder::processFrame(AVFrame* frame)
{
    if (!frame || !frame->data[0])
    {
        return false;
    }
    
    // Calculate timestamp
    double pts = calculatePTS(frame);
    currentTimestamp_.store(pts);
    
    // Convert and write frame to audio buffer
    return convertAndWriteFrame(frame);
}

bool AudioDecoder::convertAndWriteFrame(AVFrame* frame)
{
    if (!frame)
    {
        return false;
    }
    
    int numSamples = frame->nb_samples;
    int sourceChannels = frame->ch_layout.nb_channels;
    int numChannels = targetChannels_;
    
    juce::Logger::writeToLog("AudioDecoder: Processing frame - " + juce::String(numSamples) + 
                            " samples, Source channels: " + juce::String(sourceChannels) + 
                            ", Target channels: " + juce::String(numChannels));
    
    // Create audio frame for the buffer
    AudioFrame audioFrame;
    audioFrame.numSamples = numSamples;
    audioFrame.numChannels = numChannels;
    audioFrame.sampleRate = targetSampleRate_;
    audioFrame.timestamp = currentTimestamp_.load();
    audioFrame.data = std::make_unique<float[]>(numSamples * numChannels);
    
    if (needsResampling_ && swrContext_)
    {
        // Resample the audio
        uint8_t* outputData[1] = { reinterpret_cast<uint8_t*>(audioFrame.data.get()) };
        int outputSamples = swr_convert(swrContext_,
                                       outputData, numSamples,
                                       const_cast<const uint8_t**>(frame->data), frame->nb_samples);
        
        if (outputSamples < 0)
        {
            juce::Logger::writeToLog("Error resampling audio");
            return false;
        }
        
        audioFrame.numSamples = outputSamples;
    }
    else
    {
        // Direct copy if no resampling needed
        if (frame->format == AV_SAMPLE_FMT_FLT || frame->format == AV_SAMPLE_FMT_FLTP)
        {
            // Float format - can copy directly or deinterleave
            if (frame->format == AV_SAMPLE_FMT_FLT)
            {
                // Interleaved float - handle channel mapping
                if (sourceChannels == numChannels)
                {
                    // Direct copy if channel counts match
                    memcpy(audioFrame.data.get(), frame->data[0], numSamples * sourceChannels * sizeof(float));
                }
                else
                {
                    // Channel conversion needed
                    float* input = reinterpret_cast<float*>(frame->data[0]);
                    float* output = audioFrame.data.get();
                    for (int sample = 0; sample < numSamples; ++sample)
                    {
                        for (int channel = 0; channel < numChannels; ++channel)
                        {
                            if (channel < sourceChannels)
                            {
                                output[sample * numChannels + channel] = input[sample * sourceChannels + channel];
                            }
                            else
                            {
                                // Duplicate last channel or set to zero
                                output[sample * numChannels + channel] = (sourceChannels > 0) ? 
                                    input[sample * sourceChannels + (sourceChannels - 1)] : 0.0f;
                            }
                        }
                    }
                }
            }
            else
            {
                // Planar float - need to interleave
                float* output = audioFrame.data.get();
                for (int sample = 0; sample < numSamples; ++sample)
                {
                    for (int channel = 0; channel < numChannels; ++channel)
                    {
                        if (channel < sourceChannels)
                        {
                            float* channelData = reinterpret_cast<float*>(frame->data[channel]);
                            output[sample * numChannels + channel] = channelData[sample];
                        }
                        else
                        {
                            // Duplicate last channel or set to zero
                            if (sourceChannels > 0)
                            {
                                float* lastChannelData = reinterpret_cast<float*>(frame->data[sourceChannels - 1]);
                                output[sample * numChannels + channel] = lastChannelData[sample];
                            }
                            else
                            {
                                output[sample * numChannels + channel] = 0.0f;
                            }
                        }
                    }
                }
            }
        }
        else
        {
            // Other formats - would need conversion
            juce::Logger::writeToLog("Unsupported audio format: " + juce::String(frame->format));
            return false;
        }
    }
    
    // Apply gain if needed
    double gainValue = gain_.load();
    if (gainValue != 1.0)
    {
        float gain = static_cast<float>(gainValue);
        float* data = audioFrame.data.get();
        int totalSamples = audioFrame.numSamples * audioFrame.numChannels;
        
        for (int i = 0; i < totalSamples; ++i)
        {
            data[i] *= gain;
        }
    }
    
    // Push to audio buffer
    bool success = audioBuffer_.push(std::move(audioFrame));
    if (!success)
    {
        juce::Logger::writeToLog("AudioDecoder: Failed to push frame to audio buffer (buffer full?)");
    }
    return success;
}

void AudioDecoder::performSeek()
{
    double targetTime = seekTarget_.load();
    SeekMode mode = seekMode_.load();
    
    juce::Logger::writeToLog("AudioDecoder::performSeek() - Seeking to " + juce::String(targetTime) + " seconds");
    
    if (!formatContext_ || !audioStream_) {
        juce::Logger::writeToLog("AudioDecoder: Cannot seek - invalid format context or stream");
        return;
    }
    
    // Convert time to stream timebase
    int64_t seekTarget = static_cast<int64_t>(targetTime / av_q2d(audioStream_->time_base));
    
    // Determine seek flags based on mode
    int seekFlags = 0;
    switch (mode) {
        case SeekMode::Fast:
            seekFlags = 0; // Seek to any frame (keyframe seeking)
            break;
        case SeekMode::Accurate:
            seekFlags = AVSEEK_FLAG_ANY; // Seek to any frame (more accurate)
            break;
        case SeekMode::Backward:
            seekFlags = AVSEEK_FLAG_BACKWARD;
            break;
        case SeekMode::Forward:
            seekFlags = 0;
            break;
    }
    
    // Perform the seek
    int ret = av_seek_frame(formatContext_, streamIndex_, seekTarget, seekFlags);
    if (ret < 0) {
        char errbuf[128];
        av_strerror(ret, errbuf, sizeof(errbuf));
        juce::Logger::writeToLog("AudioDecoder: Seek failed - " + juce::String(errbuf));
        return;
    }
    
    // Flush the codec to clear internal buffers
    if (codecContext_) {
        avcodec_flush_buffers(codecContext_);
        juce::Logger::writeToLog("AudioDecoder: Codec buffers flushed");
    }
    
    // Update current timestamp
    currentTimestamp_.store(targetTime);
    
    juce::Logger::writeToLog("AudioDecoder: Seek completed successfully to " + juce::String(targetTime) + " seconds");
}

void AudioDecoder::handleEndOfStream()
{
}

void AudioDecoder::updateStats()
{
}

void AudioDecoder::setError(const juce::String& error)
{
    std::lock_guard<std::mutex> lock(errorMutex_);
    lastError_ = error;
    juce::Logger::writeToLog("AudioDecoder Error: " + error);
}

double AudioDecoder::calculatePTS(AVFrame* frame) const
{
    if (!frame || !audioStream_)
    {
        return 0.0;
    }
    
    // Use frame's best_effort_timestamp if available
    int64_t pts = frame->best_effort_timestamp;
    if (pts == AV_NOPTS_VALUE)
    {
        pts = frame->pts;
    }
    if (pts == AV_NOPTS_VALUE)
    {
        pts = frame->pkt_dts;
    }
    
    if (pts != AV_NOPTS_VALUE)
    {
        return pts * av_q2d(audioStream_->time_base);
    }
    
    return 0.0;
}

void AudioDecoder::applyGain(float* audioData, size_t numSamples, double gainValue) const
{
    // TODO: Implement gain application
}

bool AudioDecoder::needsFormatConversion(AVFrame* frame) const
{
    return false;
}

size_t AudioDecoder::getOptimalBufferSize() const
{
    return 0;
}

void AudioDecoder::cleanup()
{
}

} 