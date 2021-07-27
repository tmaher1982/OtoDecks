/*
  ==============================================================================

    PlaylistComponent.h
    Created: 27 Jul 2021 11:57:34pm
    Author:  Tamer Maher

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component
{
public:
    PlaylistComponent();
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
