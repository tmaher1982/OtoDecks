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
#include "DJAudioPlayer.h"


using namespace juce;

//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component, public juce::TableListBoxModel, public juce::Button::Listener, public FileDragAndDropTarget
{
public:
//    PlaylistComponent();
    
    PlaylistComponent(AudioFormatManager& _formatManager);
    
    ~PlaylistComponent() override;
    
    
    // This may not be needed
    void playListLoadURL(URL listaudioURL);

    
    void paint (juce::Graphics&) override;
    void resized() override;
    int getNumRows() override;
    
    void paintRowBackground (Graphics &, int rowNumber, int width, int Height, bool rowIsSelected) override;

    void paintCell (Graphics &, int rowNumber, int columnId, int width, int Height, bool rowIsSelected) override;
    
    bool isInterestedInFileDrag(const juce::StringArray& files) override ;
    void filesDropped(const juce::StringArray& files, int x, int y) override;
    
    
    
//        std::vector<std::string> trackTitles;
    
private:
    
    Component* refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate) override;
    
    void buttonClicked(juce::Button* button) override;
    
    juce::TableListBox tableComponent;
    std::vector<std::string> trackTitles;
    std::vector<std::string> trackDurations;
    
    AudioFormatManager& formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    ResamplingAudioSource resampleSource{&transportSource, false, 2};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
