/*
  ==============================================================================

    DeckGUI.h
    Created: 16 Jul 2021 2:01:06pm
    Author:  Tamer Maher

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
using namespace juce;

//==============================================================================
/*
*/
class DeckGUI  : public juce::Component
{
public:
    DeckGUI();
    ~DeckGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    TextButton playButton{"PLAY"};
    TextButton stopButton{"STOP"};
    TextButton loadButton{"LOAD"};
    
    Slider volSlider;
    Slider speedSlider;
    Slider posSlider;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
