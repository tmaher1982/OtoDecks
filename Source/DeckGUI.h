/*
  ==============================================================================

    DeckGUI.h
    Created: 16 Jul 2021 2:01:06pm
    Author:  Tamer Maher

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"

using namespace juce;

//==============================================================================
/*
*/
class DeckGUI  : public juce::Component, public Button::Listener, public Slider::Listener, public FileDragAndDropTarget
{
public:
    DeckGUI(DJAudioPlayer* player, AudioFormatManager & formatManagerToUse, AudioThumbnailCache & cacheToUse );
    ~DeckGUI() override;

    /** implement Button listener */
    void buttonClicked (Button *) override; // Override is needed here
    
    /** Implement Slider::Listener */
    void sliderValueChanged (Slider *slider) override;
    
    bool isInterestedInFileDrag(const StringArray &files) override;
    void filesDropped (const StringArray &files, int x, int y) override;
    
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    TextButton playButton{"PLAY"};
    TextButton stopButton{"STOP"};
    TextButton loadButton{"LOAD"};
    
    Slider volSlider;
    Slider speedSlider;
    Slider posSlider;
    
    DJAudioPlayer* player;
    
    WaveformDisplay waveformDisplay;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
