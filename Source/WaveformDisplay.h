/*
  ==============================================================================

    WaveformDisplay.h
    Created: 17 Jul 2021 11:31:31pm
    Author:  Tamer Maher

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformDisplay  : public juce::Component
{
public:
    WaveformDisplay(juce::AudioFormatManager & formatManagerToUse, juce::AudioThumbnailCache & cacheToUse);
    ~WaveformDisplay() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void loadURL(juce::URL audioURL);

private:
    juce::AudioThumbnail audioThumb;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
