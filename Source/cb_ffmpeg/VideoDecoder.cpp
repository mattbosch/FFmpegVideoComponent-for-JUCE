#include "VideoDecoder.h"

namespace cb_ffmpeg
{
VideoDecoder::VideoDecoder(VideoBuffer& videoBuffer, VideoFramePool& framePool, const MediaReaderConfig& config)
    : config_(config), videoBuffer_(videoBuffer), framePool_(framePool)
{
}

VideoDecoder::~VideoDecoder()
{
    stop();
}

bool VideoDecoder::initialize(AVFormatContext* formatContext, int streamIndex)
{
    return false;
}

bool VideoDecoder::start()
{
    return false;
}

void VideoDecoder::stop()
{
}

void VideoDecoder::seek(double timeInSeconds, SeekMode mode)
{
}

void VideoDecoder::flush()
{
}

juce::String VideoDecoder::getLastError() const
{
    return juce::String();
}

void VideoDecoder::decoderLoop()
{
}

bool VideoDecoder::initializeCodec()
{
    return false;
}

bool VideoDecoder::initializeHardwareDecoding()
{
    return false;
}

bool VideoDecoder::initializeScaler()
{
    return false;
}

bool VideoDecoder::decodePacket(AVPacket* packet)
{
    return false;
}

bool VideoDecoder::processFrame(AVFrame* frame)
{
    return false;
}

bool VideoDecoder::convertAndWriteFrame(AVFrame* frame)
{
    return false;
}

void VideoDecoder::performSeek()
{
}

void VideoDecoder::handleEndOfStream()
{
}

void VideoDecoder::updateStats()
{
}

void VideoDecoder::setError(const juce::String& error)
{
}

double VideoDecoder::calculatePTS(AVFrame* frame) const
{
    return 0.0;
}

bool VideoDecoder::needsConversion(AVFrame* frame) const
{
    return false;
}

bool VideoDecoder::transferHardwareFrame(AVFrame* hwFrame, AVFrame* swFrame)
{
    return false;
}

void VideoDecoder::cleanup()
{
}

enum AVPixelFormat VideoDecoder::getHwFormat(AVCodecContext* ctx, const enum AVPixelFormat* pixFmts)
{
    return AV_PIX_FMT_NONE;
}

} 