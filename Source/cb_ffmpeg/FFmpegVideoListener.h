#pragma once

/**
 * Legacy FFmpegVideoListener interface for backward compatibility
 * 
 * This interface is kept for compatibility with existing TransportComponent.
 * For new code, use cb_ffmpeg::MediaReaderCallback instead.
 */
class FFmpegVideoListener
{
public:
    virtual ~FFmpegVideoListener() = default;
    
    /**
     * Called when playback position changes
     * @param pts Presentation timestamp in seconds
     */
    virtual void positionSecondsChanged(const double pts) {}
    
    /**
     * Called when playback starts
     */
    virtual void playbackStarted() {}
    
    /**
     * Called when playback stops
     */
    virtual void playbackStopped() {}
    
    /**
     * Called when media is loaded
     */
    virtual void mediaLoaded() {}
    
    /**
     * Called when an error occurs
     * @param errorMessage Error description
     */
    virtual void errorOccurred(const juce::String& errorMessage) {}
}; 