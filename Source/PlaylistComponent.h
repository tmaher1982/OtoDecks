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
class PlaylistComponent  : public juce::Component, public juce::TableListBoxModel, public juce::Button::Listener, public FileDragAndDropTarget, public juce::TextEditor::Listener

{
public:
//    PlaylistComponent();
    
    PlaylistComponent(DJAudioPlayer* player1, AudioFormatManager& _formatManager );
    
    ~PlaylistComponent() override;
    
    void paint (juce::Graphics&) override;
    void resized() override;
    int getNumRows() override;
    
    void paintRowBackground (Graphics &, int rowNumber, int width, int Height, bool rowIsSelected) override;

    void paintCell (Graphics &, int rowNumber, int columnId, int width, int Height, bool rowIsSelected) override;
    
    bool isInterestedInFileDrag(const juce::StringArray& files) override ;
    void filesDropped(const juce::StringArray& files, int x, int y) override;
    
    juce::String getTrackDuration(juce::File trackFile);
    
    void ReadPlaylistFile();
    
    void ManagePlaylist(juce::File filename, juce::String title, juce::String duration);
    
    void textEditorReturnKeyPressed(juce::TextEditor&)override;
    
private:
    
    Component* refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate) override;
    
    void buttonClicked(juce::Button* button) override;
    
    juce::TableListBox tableComponent;

    std::vector<juce::String> trackTitles;
    std::vector<juce::String> trackDurations;
    std::vector<juce::File>trackFiles;
    
    AudioFormatManager& formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    ResamplingAudioSource resampleSource{&transportSource, false, 2};
    
    DJAudioPlayer* player1;
    
    juce::TextEditor playlistSearch;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
