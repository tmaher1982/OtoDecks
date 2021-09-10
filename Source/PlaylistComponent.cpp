/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 27 Jul 2021 11:57:34pm
    Author:  Tamer Maher

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"


//==============================================================================
PlaylistComponent::PlaylistComponent(DJAudioPlayer* player1, AudioFormatManager& _formatManager) : formatManager(_formatManager)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
//    trackTitles.push_back("Track 1");
//    trackTitles.push_back("Track 2");
//    trackTitles.push_back("Track 3");
//    trackTitles.push_back("Track 4");
//    trackTitles.push_back("Track 5");
//    trackTitles.push_back("Track 6");
//
//    trackDurations.push_back("30");
//    trackDurations.push_back("50");
//    trackDurations.push_back("80");
//    trackDurations.push_back("100");
//    trackDurations.push_back("18");
//    trackDurations.push_back("30");
//
//

    
    tableComponent.getHeader().addColumn("Track Title", 1, 400); // Making 1 instead of 0 for juce 6
    tableComponent.getHeader().addColumn("Duration(Sec)", 2, 200); // One More Column for the Duration
    tableComponent.getHeader().addColumn("", 3, 100); // One more column for the delete button
    tableComponent.getHeader().addColumn("", 4, 100); // One more column for the delete button
    
//    tableComponent.getHeader().addColumn("Artist", 2, 400);
    tableComponent.setModel(this);
    
    addAndMakeVisible(tableComponent);
}

PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("PlaylistComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    tableComponent.setBounds(0,0,getWidth(), getHeight());
}

int PlaylistComponent::getNumRows()
{
    return trackTitles.size();
//    return trackDurations.size();
}

void PlaylistComponent::paintRowBackground (Graphics & g, int rowNumber, int width, int Height, bool rowIsSelected)
{
    if (rowIsSelected)
    {
        g.fillAll(Colours::orange);
    }
    else
    {
        g.fillAll(Colours::darkgrey);
    }
}

void PlaylistComponent::paintCell (Graphics & g, int rowNumber, int columnId, int width, int Height, bool rowIsSelected)
{
    
    // Splitting by columnIDs to add trackTitle and Duration
    if (columnId == 1)
    {
        g.drawText(trackTitles[rowNumber], 2, 0 , width -4, Height, Justification::centredLeft, true);
    }
    
    if (columnId == 2)
    {
        g.drawText(trackDurations[rowNumber], 2, 2 , width -4, Height, Justification::centredLeft, true);
    }
        
}

Component* PlaylistComponent::refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate)
{
    
    if (columnId == 3)
    {
        if (existingComponentToUpdate == nullptr)
        {

            // Gave play button a prefix ID of 10000
            TextButton* btn = new TextButton{"PLAY on Deck1"};
            btn->setColour(0x1000100, juce::Colours::green);
            String id{std::to_string(rowNumber + 10000)};
            btn->setComponentID(id);
            
            btn ->addListener(this);
            existingComponentToUpdate = btn;
            
        }
    }

    if (columnId == 4)
    {
        if (existingComponentToUpdate == nullptr)
        {
            TextButton* btn2 = new TextButton{"DELETE"};

            // Gave play button a prefix ID of 20000
            String id2{std::to_string(rowNumber + 20000)};
            btn2->setComponentID(id2);
            
            btn2 ->addListener(this);
            existingComponentToUpdate = btn2;
            
            
        }
    }
    return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked(Button* button)
{
   
    int id = std::stoi(button->getComponentID().toStdString());
    int id2 = std::stoi(button->getComponentID().toStdString());
    
    // Detects if the button is a Delete button
    if ( id && id2 >= 20000)
    {
        // Gives back the track ID to delete
        id2 = id2 - 20000;
        std::cout<< "PlaylistComponent::DELETE buttonClicked " << trackTitles[id2] << std::endl;
        
        PlaylistComponent::trackDurations.erase(trackDurations.begin() + id2);
        PlaylistComponent::trackTitles.erase(trackTitles.begin() + id2);
        PlaylistComponent::trackFiles.erase(trackFiles.begin() + id2);
    
        tableComponent.updateContent();
    }
    
    // Detects if the button is a Play button
    else
    {
        // Gives back the track ID to play
        id = id - 10000;
        std::cout<< "PlaylistComponent::Play buttonClicked " << trackTitles[id] << std::endl;
//        PlaylistComponent::playListLoadURL(trackFiles[id]);
        
        
        player1->loadURL(juce::URL{trackFiles[id]});
//        player1->loadURL(trackFiles[id]);
        
        
    }
        
    
}

bool PlaylistComponent::isInterestedInFileDrag(const juce::StringArray& files)
{
    std::cout << "Playlist::isInterestedInFileDrag" << std::endl;
    return true;
}

void PlaylistComponent::filesDropped(const juce::StringArray& files, int x, int y)
{
    std::cout << "files dragged in playlist " << std::endl;
    
    // This gets filename(s) of on or more files dragged in the playlist
//    for (const juce::String& filename : files)
    for (const juce::File filename : files)
    
    {
        
//        std::cout <<filename << std::endl;
//        juce::URL theTrack = URL({File{filename}});
        auto theTrack = URL({File{filename}});
        PlaylistComponent::trackFiles.push_back(filename.getFullPathName());
        
//        PlaylistComponent::trackFiles.push_back(filename);
//                PlaylistComponent::trackFiles.push_back(theTrack);
//        PlaylistComponent::playListLoadURL(filename);
        
//
        
        
        ////        std::cout < "title is " << title << std::endl;
        
//        std::cout<<"tracktitles size " << trackTitles.size() << std::endl;
        
        
//        PlaylistComponent::trackTitles.push_back("Track 7");
//        PlaylistComponent::trackDurations.push_back("25 ");
//
//        auto theTrack = URL({File{filename}});
//
//        PlaylistComponent::playListLoadURL(URL{files[0]});
        
        
        
        
//        PlaylistComponent::getTrackDuration(filename);
        //This adds track name to the playlist
        juce::String title = theTrack.getFileName();
        PlaylistComponent::trackTitles.push_back(title);
        
        // This adds track duration to the playlist
        juce::String duration = getTrackDuration(filename);
        PlaylistComponent::trackDurations.push_back(duration);

        
        // Correct one, but may not be needed
        
//        PlaylistComponent::playListLoadURL(URL{filename});
        
//        MainComponent::player1::loadURL(filename);
        
//        PlaylistComponent::trackTitles.push_back(theTrack);
        
        // This updates the playlist table content
        tableComponent.updateContent();
//        tabeleComponent.repaint();
        
//        std::cout<<"tracktitles size " << trackTitles.size() << std::endl;
    }
    //    trackTitles.emplace_back(files);
    
}




// This may not be needed here 
void PlaylistComponent::playListLoadURL(URL listaudioURL)
{
    std::cout << " I'm called "<< std::endl;
    
    auto* reader = formatManager.createReaderFor(listaudioURL.createInputStream(false));
       if (reader != nullptr) // good file!
        {
           std::unique_ptr<juce::AudioFormatReaderSource> newSource (new juce::AudioFormatReaderSource (reader, true));
           transportSource.setSource( newSource.get(), 0, nullptr, reader -> sampleRate);
           readerSource.reset (newSource.release());
        }
}


// This gets the track length
juce::String PlaylistComponent::getTrackDuration(juce::File trackFile)

{
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    
    juce::AudioFormatReader* formatReader = formatManager.createReaderFor(trackFile);
    long trackLength = formatReader->lengthInSamples / formatReader->sampleRate;
    
    
    std::string tlength = std::to_string(trackLength / 60) + ":" + std::to_string(trackLength & 60);
    std::cout << "Track length is " << tlength << std::endl;
//    return std::to_string(trackLength / 60) + ":" + std::to_string(trackLength & 60);
    return tlength;
    
}
