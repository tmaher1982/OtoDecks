#pragma once

#include <JuceHeader.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public AudioAppComponent,
                       public Button::Listener,
                       public Slider::Listener
{ 
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;
    
    /** implement Button listener */
    void buttonClicked (Button *) override; // Override is needed here
    
    /** Implement Slider::Listener */
    void sliderValueChanged (Slider *slider) override;

private:
    //==============================================================================
    // Your private member variables go here...

    // juce::TextButton button;
    TextButton playButton{"PLAY"};
    TextButton stopButton{"STOP"};
    TextButton loadButton{"LOAD"};
    
    Slider volSlider;
    Slider speedSlider;
    Slider posSlider;
    
    juce::ToggleButton toggleButton{"On or Off"};
    
        
    DJAudioPlayer player1;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
