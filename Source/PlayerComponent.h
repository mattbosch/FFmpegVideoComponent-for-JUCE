#pragma once

#include "JuceHeader.h"
#include "cb_ffmpeg/cb_ffmpeg.h"

class PlayerComponent : public juce::Component,
                        public juce::AudioIODeviceCallback,
                        public cb_ffmpeg::MediaReaderCallback,
                        private juce::Timer
{
public:
    PlayerComponent();
    ~PlayerComponent() override;

    void paint(juce::Graphics& g) override;
    void resized() override;
    
    // juce::AudioSource
    // juce::AudioIODeviceCallback
    void audioDeviceAboutToStart(juce::AudioIODevice* device) override;
    void audioDeviceStopped() override;
    void audioDeviceIOCallbackWithContext(const float* const* inputChannelData,
                                          int numInputChannels,
                                          float* const* outputChannelData,
                                          int numOutputChannels,
                                          int numSamples,
                                          const juce::AudioIODeviceCallbackContext& context) override;

    // Public playback controls
    bool loadMediaFile(const juce::File& file);
    void togglePlayPause();
    void stopPlayback();
    
    double getCurrentTime() const;
    double getDuration() const;
    bool isPlaying() const;
    bool isMediaLoaded() const;
    
    // Audio control
    void setVolume(double volume);
    double getVolume() const;
    void setMuted(bool muted);
    bool isMuted() const;

private:
    void timerCallback() override;

    // cb_ffmpeg::MediaReaderCallback
    void onMediaLoaded(const cb_ffmpeg::MediaInfo& info) override;
    void onPlaybackStarted() override;
    void onPlaybackStopped() override;
    void onPlaybackPaused() override;
    void onEndOfMedia() override;
    void onError(const juce::String& errorMessage) override;

    void resetPlayerState();
    void prepareAudioSource();
    void releaseAudioSource();

    std::unique_ptr<cb_ffmpeg::MediaReader> mediaReader_;
    cb_ffmpeg::MediaReaderConfig config_;
    
    // Video Display Area
    juce::Component* videoComponent_{nullptr};  // Raw pointer managed by MediaReader
    std::unique_ptr<juce::Component> audioInfoComponent_{nullptr};  // For audio-only files
    juce::Label videoPlaceholder_{"", "Drop video file here or click Open"};

    // State Management
    bool isMediaLoaded_{false};
    bool isPlaying_{false};
    double currentTime_{0.0};
    double duration_{0.0};
    cb_ffmpeg::MediaInfo currentMediaInfo_;
    
    // Audio processing
    double sampleRate_{44100.0};
    int bufferSize_{512};
    juce::AudioSource* currentAudioSource_{nullptr}; // Raw pointer managed by MediaReader
    bool audioSourcePrepared_{false};
    double currentVolume_{0.7};
    bool isMuted_{false};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerComponent)
}; 