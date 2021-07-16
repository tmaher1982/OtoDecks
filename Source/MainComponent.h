#pragma once

#include <JuceHeader.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "DeckGUI.h"

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

        
    DJAudioPlayer player1;
    DeckGUI deckGUI1{&player1};
    
    DJAudioPlayer player2;
    DeckGUI deckGUI2{&player2};
    
    MixerAudioSource mixerSource;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
