#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent,
                       public juce::Button::Listener,
                       public juce::Slider::Listener
{ 
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;
    
    /** implement Button listener */
    void buttonClicked (juce::Button *) override; // Override is needed here
    
    /** Implement Slider::Listener */
    void sliderValueChanged (juce::Slider *slider) override;

private:
    //==============================================================================
    // Your private member variables go here...

    // juce::TextButton button;
    juce::TextButton playButton{"PLAY"};
    juce::TextButton stopButton{"STOP"};
    juce::TextButton loadButton{"LOAD"};
    
    
    juce::Slider volSlider;
    juce::Slider speedSlider;
    
    juce::Random rand;
    double phase;
    double dphase; // this is for the changing phase
    
    bool playing;
    
    
    juce::ToggleButton toggleButton{"On or Off"};
    
    
    juce::AudioFormatManager formatManager;
    
    std::unique_ptr <juce::AudioFormatReaderSource> readerSource; // std::unique_ptr for smart pointer
    juce::AudioTransportSource transportSource;
    juce::ResamplingAudioSource resampleSource{&transportSource, false, 2};
    
    
    void loadURL(juce::URL audioURL);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
