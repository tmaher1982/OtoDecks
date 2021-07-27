/*
  ==============================================================================

    PlaylistComponent.h
    Created: 27 Jul 2021 11:57:34pm
    Author:  Tamer Maher

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>

using namespace juce;

//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component, public juce::TableListBoxModel
{
public:
    PlaylistComponent();
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    int getNumRows() override;
    
    void paintRowBackground (Graphics &, int rowNumber, int width, int Height, bool rowIsSelected) override;

    void paintCell (Graphics &, int rowNumber, int columnId, int width, int Height, bool rowIsSelected) override;
private:
    
    juce::TableListBox tableComponent;
    std::vector<std::string> trackTitles;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
