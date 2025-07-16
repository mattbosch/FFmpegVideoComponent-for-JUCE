/*
    MediaReader System - Example Usage
    
    This file demonstrates how to use the cb::MediaReader system
    for universal media playback in JUCE applications.
*/

#include "cb_ffmpeg.h"

namespace cb
{

// Example: Simple Audio Player Component
class SimpleAudioPlayerComponent : public juce::Component,
                                  public juce::AudioSource,
                                  public juce::Timer
{
public:
    SimpleAudioPlayerComponent()
    {
        // Create audio-optimized MediaReader
        mediaReader = createAudioOnlyReader();
        
        // Setup UI
        addAndMakeVisible(openButton);
        addAndMakeVisible(playButton);
        addAndMakeVisible(stopButton);
        addAndMakeVisible(positionSlider);
        addAndMakeVisible(volumeSlider);
        
        openButton.setButtonText("Open Audio File");
        playButton.setButtonText("Play");
        stopButton.setButtonText("Stop");
        
        positionSlider.setRange(0.0, 100.0);
        volumeSlider.setRange(0.0, 1.0);
        volumeSlider.setValue(0.7);
        
        // Setup callbacks
        openButton.onClick = [this] { openAudioFile(); };
        playButton.onClick = [this] { togglePlayback(); };
        stopButton.onClick = [this] { stopPlayback(); };
        volumeSlider.onValueChange = [this] { 
            if (mediaReader)
                mediaReader->setVolume(static_cast<float>(volumeSlider.getValue()));
        };
        
        // Start position update timer
        startTimerHz(30);
    }
    
    // AudioSource implementation
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override
    {
        if (mediaReader && mediaReader->getAudioSource())
            mediaReader->getAudioSource()->prepareToPlay(samplesPerBlockExpected, sampleRate);
    }
    
    void releaseResources() override
    {
        if (mediaReader && mediaReader->getAudioSource())
            mediaReader->getAudioSource()->releaseResources();
    }
    
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override
    {
        if (mediaReader && mediaReader->getAudioSource())
            mediaReader->getAudioSource()->getNextAudioBlock(bufferToFill);
        else
            bufferToFill.clearActiveBufferRegion();
    }
    
    void resized() override
    {
        auto bounds = getLocalBounds().reduced(10);
        
        openButton.setBounds(bounds.removeFromTop(30));
        bounds.removeFromTop(10);
        
        auto buttonRow = bounds.removeFromTop(30);
        playButton.setBounds(buttonRow.removeFromLeft(80));
        buttonRow.removeFromLeft(10);
        stopButton.setBounds(buttonRow.removeFromLeft(80));
        
        bounds.removeFromTop(10);
        positionSlider.setBounds(bounds.removeFromTop(30));
        bounds.removeFromTop(10);
        volumeSlider.setBounds(bounds.removeFromTop(30));
    }
    
private:
    void openAudioFile()
    {
        juce::FileChooser chooser("Select audio file...",
                                juce::File{},
                                "*.wav;*.mp3;*.flac;*.aac;*.ogg");
        
        if (chooser.browseForFileToOpen())
        {
            auto file = chooser.getResult();
            if (mediaReader->open(file.getFullPathName().toStdString()))
            {
                positionSlider.setRange(0.0, mediaReader->getDuration());
                positionSlider.setValue(0.0);
                playButton.setEnabled(true);
                stopButton.setEnabled(true);
            }
        }
    }
    
    void togglePlayback()
    {
        if (!mediaReader || !mediaReader->getIsInitialized())
            return;
        
        if (mediaReader->getIsPlaying())
        {
            mediaReader->pause();
            playButton.setButtonText("Resume");
        }
        else
        {
            mediaReader->play();
            playButton.setButtonText("Pause");
        }
    }
    
    void stopPlayback()
    {
        if (mediaReader)
        {
            mediaReader->stop();
            playButton.setButtonText("Play");
            positionSlider.setValue(0.0);
        }
    }
    
    void timerCallback() override
    {
        if (mediaReader && mediaReader->getIsInitialized())
        {
            // Update position slider
            auto currentTime = mediaReader->getCurrentTime();
            positionSlider.setValue(currentTime, juce::dontSendNotification);
            
            // Check for end of file
            if (mediaReader->hasReachedEndOfFile())
            {
                stopPlayback();
            }
        }
    }
    
    std::unique_ptr<MediaReader> mediaReader;
    juce::TextButton openButton, playButton, stopButton;
    juce::Slider positionSlider, volumeSlider;
};

// Example: Video Player Component
class SimpleVideoPlayerComponent : public juce::Component,
                                  public juce::Timer
{
public:
    SimpleVideoPlayerComponent()
    {
        // Create high-performance MediaReader for video
        mediaReader = createHighPerformanceReader();
        
        // Setup UI
        addAndMakeVisible(openButton);
        addAndMakeVisible(playButton);
        addAndMakeVisible(stopButton);
        addAndMakeVisible(positionSlider);
        
        openButton.setButtonText("Open Video File");
        playButton.setButtonText("Play");
        stopButton.setButtonText("Stop");
        
        positionSlider.setRange(0.0, 100.0);
        
        // Setup callbacks
        openButton.onClick = [this] { openVideoFile(); };
        playButton.onClick = [this] { togglePlayback(); };
        stopButton.onClick = [this] { stopPlayback(); };
        
        // Start update timer
        startTimerHz(30);
    }
    
    void resized() override
    {
        auto bounds = getLocalBounds().reduced(10);
        
        // Controls at top
        auto controlsArea = bounds.removeFromTop(80);
        openButton.setBounds(controlsArea.removeFromTop(30));
        controlsArea.removeFromTop(10);
        
        auto buttonRow = controlsArea.removeFromTop(30);
        playButton.setBounds(buttonRow.removeFromLeft(80));
        buttonRow.removeFromLeft(10);
        stopButton.setBounds(buttonRow.removeFromLeft(80));
        
        bounds.removeFromTop(10);
        positionSlider.setBounds(bounds.removeFromTop(30));
        bounds.removeFromTop(10);
        
        // Video area
        if (videoComponent)
        {
            videoComponent->setBounds(bounds);
        }
    }
    
    void paint(juce::Graphics& g) override
    {
        if (!videoComponent)
        {
            g.fillAll(juce::Colours::black);
            g.setColour(juce::Colours::white);
            g.setFont(juce::Font(16.0f));
            g.drawText("No video loaded", getLocalBounds(), juce::Justification::centred);
        }
    }
    
private:
    void openVideoFile()
    {
        juce::FileChooser chooser("Select video file...",
                                juce::File{},
                                "*.mp4;*.avi;*.mov;*.mkv;*.webm");
        
        if (chooser.browseForFileToOpen())
        {
            auto file = chooser.getResult();
            if (mediaReader->open(file.getFullPathName().toStdString()))
            {
                // Add video component if we have video
                if (mediaReader->getHasVideo())
                {
                    videoComponent.reset(mediaReader->getVideoComponent());
                    if (videoComponent)
                    {
                        addAndMakeVisible(*videoComponent);
                        resized(); // Update layout
                    }
                }
                
                positionSlider.setRange(0.0, mediaReader->getDuration());
                positionSlider.setValue(0.0);
                playButton.setEnabled(true);
                stopButton.setEnabled(true);
                
                repaint();
            }
        }
    }
    
    void togglePlayback()
    {
        if (!mediaReader || !mediaReader->getIsInitialized())
            return;
        
        if (mediaReader->getIsPlaying())
        {
            mediaReader->pause();
            playButton.setButtonText("Resume");
        }
        else
        {
            mediaReader->play();
            playButton.setButtonText("Pause");
        }
    }
    
    void stopPlayback()
    {
        if (mediaReader)
        {
            mediaReader->stop();
            playButton.setButtonText("Play");
            positionSlider.setValue(0.0);
        }
    }
    
    void timerCallback() override
    {
        if (mediaReader && mediaReader->getIsInitialized())
        {
            // Update position
            auto currentTime = mediaReader->getCurrentTime();
            positionSlider.setValue(currentTime, juce::dontSendNotification);
            
            // Check for end of file
            if (mediaReader->hasReachedEndOfFile())
            {
                stopPlayback();
            }
        }
    }
    
    std::unique_ptr<MediaReader> mediaReader;
    std::unique_ptr<MediaVideoComponent> videoComponent;
    juce::TextButton openButton, playButton, stopButton;
    juce::Slider positionSlider;
};

// Example: Advanced Media Info Component
class MediaInfoComponent : public juce::Component,
                          public juce::Timer
{
public:
    MediaInfoComponent()
    {
        mediaReader = createMediaReader(MediaReaderConfig::createDefaultConfig());
        startTimerHz(5); // Update every 200ms
    }
    
    void setMediaFile(const std::string& filename)
    {
        if (mediaReader->open(filename))
        {
            updateInfo();
            repaint();
        }
    }
    
    void paint(juce::Graphics& g) override
    {
        g.fillAll(juce::Colours::darkgrey);
        g.setColour(juce::Colours::white);
        g.setFont(juce::Font(12.0f));
        
        auto bounds = getLocalBounds().reduced(10);
        int lineHeight = 15;
        
        // Draw info lines
        for (const auto& line : infoLines)
        {
            g.drawText(line, bounds.removeFromTop(lineHeight), juce::Justification::topLeft);
        }
    }
    
private:
    void updateInfo()
    {
        infoLines.clear();
        
        if (!mediaReader->getIsInitialized())
        {
            infoLines.push_back("No media loaded");
            return;
        }
        
        auto stats = mediaReader->getStats();
        auto streams = mediaReader->getStreamInfo();
        
        // Basic info
        infoLines.push_back("File: " + stats.filename);
        infoLines.push_back("Duration: " + juce::String(stats.duration, 2) + "s");
        infoLines.push_back("Current Time: " + juce::String(stats.currentTime, 2) + "s");
        infoLines.push_back("Status: " + juce::String(stats.isPlaying ? "Playing" : "Stopped"));
        infoLines.push_back("");
        
        // Stream info
        infoLines.push_back("Streams:");
        for (const auto& stream : streams)
        {
            juce::String streamInfo = "  [" + juce::String(stream.index) + "] " + 
                                    stream.codecName + " (" + 
                                    (stream.type == MediaType::Audio ? "Audio" : 
                                     stream.type == MediaType::Video ? "Video" : "Other") + ")";
            
            if (stream.type == MediaType::Audio)
            {
                streamInfo += " - " + juce::String(stream.audioInfo.sampleRate) + "Hz, " +
                             juce::String(stream.audioInfo.channels) + "ch";
            }
            else if (stream.type == MediaType::Video)
            {
                streamInfo += " - " + juce::String(stream.videoInfo.width) + "x" +
                             juce::String(stream.videoInfo.height) + 
                             " @" + juce::String(stream.videoInfo.frameRate, 1) + "fps";
            }
            
            infoLines.push_back(streamInfo);
        }
        
        if (stats.hasAudio)
        {
            infoLines.push_back("");
            infoLines.push_back("Audio Buffer:");
            infoLines.push_back("  Size: " + juce::String(stats.audioStats.currentSize) + 
                              "/" + juce::String(stats.audioStats.bufferSize));
            infoLines.push_back("  Underruns: " + juce::String(stats.audioStats.underruns));
            infoLines.push_back("  Overruns: " + juce::String(stats.audioStats.overruns));
        }
        
        if (stats.hasVideo)
        {
            infoLines.push_back("");
            infoLines.push_back("Video Buffer:");
            infoLines.push_back("  Queue: " + juce::String(stats.videoStats.queueSize) + 
                              "/" + juce::String(stats.videoStats.maxQueueSize));
            infoLines.push_back("  Dropped: " + juce::String(stats.videoStats.droppedFrames));
        }
    }
    
    void timerCallback() override
    {
        if (mediaReader && mediaReader->getIsInitialized())
        {
            updateInfo();
            repaint();
        }
    }
    
    std::unique_ptr<MediaReader> mediaReader;
    juce::StringArray infoLines;
};

} // namespace cb

/*
Usage Examples:

1. Basic Audio Playback:
```cpp
// Create audio-only reader
auto audioReader = cb::createAudioOnlyReader();
if (audioReader->open("audio.wav"))
{
    // Get JUCE AudioSource
    auto* audioSource = audioReader->getAudioSource();
    
    // Add to your audio device manager
    audioDeviceManager.setAudioCallback(audioSource);
    
    // Control playback
    audioReader->play();
    audioReader->pause();
    audioReader->seek(30.0); // Seek to 30 seconds
    audioReader->stop();
}
```

2. Video Playback:
```cpp
// Create high-performance reader
auto videoReader = cb::createHighPerformanceReader();
if (videoReader->open("video.mp4"))
{
    // Get video component
    auto* videoComponent = videoReader->getVideoComponent();
    addAndMakeVisible(*videoComponent);
    
    // Start playback
    videoReader->play();
}
```

3. Custom Configuration:
```cpp
// Create custom config
cb::MediaReaderConfig config;
config.audioConfig.targetSampleRate = 48000;
config.audioConfig.targetChannels = 2;
config.videoConfig.enableHardwareAcceleration = true;
config.videoConfig.targetWidth = 1920;
config.videoConfig.targetHeight = 1080;

auto reader = cb::createMediaReader(config);
```

4. Format Support Check:
```cpp
if (cb::isFormatSupported("mp4"))
{
    // MP4 is supported
}

auto supportedFormats = cb::getSupportedFormats();
// Returns vector of supported format extensions
```
*/ 