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
PlaylistComponent::PlaylistComponent( DJAudioPlayer* deckPlayer1, AudioFormatManager& _formatManager) : formatManager(_formatManager)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    ReadPlaylistFile();
    
    player1 = deckPlayer1;
    
    tableComponent.getHeader().addColumn("Track Title", 1, 400); // Making 1 instead of 0 for juce 6
    tableComponent.getHeader().addColumn("Duration(min:sec)", 2, 200); // One More Column for the Duration
    tableComponent.getHeader().addColumn("", 3, 100); // One more column for the play button
    tableComponent.getHeader().addColumn("", 4, 100); // One more column for the delete button
    
    tableComponent.setModel(this);
    
    addAndMakeVisible(tableComponent);
    
    addAndMakeVisible(playlistSearch);
    playlistSearch.addListener(this);

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
    g.drawText ("PlaylistComponent", getLocalBounds(), juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    double rowH = getHeight() ;
    playlistSearch.setBounds(0, 0, getWidth(), rowH * 0.1);
    playlistSearch.setColour(TextEditor::ColourIds::textColourId, Colours::darkorange);
    playlistSearch.setText("Search Here for tracks ");
    tableComponent.setBounds(0,rowH * 0.1,getWidth(), getHeight());
}

int PlaylistComponent::getNumRows()
{
    return trackTitles.size();
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

        player1->loadURL(juce::URL{trackFiles[id]});
        player1->start();
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
    for (const juce::File filename : files)
    // foreach filename in files
    {
        // This gets the file path that
        PlaylistComponent::trackFiles.push_back(filename.getFullPathName());

        
        //This adds track name to the playlist
        auto theTrack = URL({File{filename}});
        juce::String title = theTrack.getFileName();
        PlaylistComponent::trackTitles.push_back(title);
        
        // This adds track duration to the playlist
        juce::String duration = getTrackDuration(filename);
        PlaylistComponent::trackDurations.push_back(duration);

        // This updates the playlist table content
        tableComponent.updateContent();
        
        //        ****************************************************************************
        
        
        //        std::cout <<filename << std::endl;
        //        juce::URL theTrack = URL({File{filename}});
//        PlaylistComponent::trackFiles.push_back(filename);
//                PlaylistComponent::trackFiles.push_back(theTrack);
//        PlaylistComponent::playListLoadURL(filename);
        
//
        
        
        ////        std::cout < "title is " << title << std::endl;
        
//        std::cout<<"tracktitles size " << trackTitles.size() << std::endl;
        
        
//        PlaylistComponent::playListLoadURL(URL{files[0]});
        
        
        
        
//        PlaylistComponent::getTrackDuration(filename);
        
        
        // Correct one, but may not be needed
        
//        PlaylistComponent::playListLoadURL(URL{filename});
        
//        MainComponent::player1::loadURL(filename);
        
//        PlaylistComponent::trackTitles.push_back(theTrack);
        
        
//        tabeleComponent.repaint();
        
//        std::cout<<"tracktitles size " << trackTitles.size() << std::endl;
        
        
        // Update the method signature and details with the right parameters I have here
//        PlaylistComponent::ManagePlaylist(juce::File filename)
        
        
//            XmlElement* playlistXmlElement = new XmlElement();
//            XmlElement* track = playlistXmlElement.createNewChildElement("Track");
//            XmlElement* name = track->createNewChildElement("name");
//            name->addTextElement(juce::File(filename).getFileNameWithoutExtension());

        // Linkedlist approach on XML
//        XmlElement playlistTrack ("TrackPlaylist");
//        XmlElement * trackFile = new XmlElement("Thefilepath");
//        XmlElement * trackName = new XmlElement("TheSongName");
//        XmlElement * trackDuration = new XmlElement("4:50");
//        
//        
//        playlistTrack.addChildElement(trackFile);
//        playlistTrack.addChildElement(trackName);
//        playlistTrack.addChildElement(trackDuration);
//        
//        playlistTrack.writeTo(juce::File{BinaryData::Playlist_xml});
//
        //        ****************************************************************************
        
    }
}

// This gets the track length
juce::String PlaylistComponent::getTrackDuration(juce::File trackFile)
{
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    
    juce::AudioFormatReader* formatReader = formatManager.createReaderFor(trackFile);
    long trackLength = formatReader->lengthInSamples / formatReader->sampleRate;
    
    std::string tlength = std::to_string(trackLength / 60) + ":" + std::to_string(trackLength % 60);
    std::cout << "Track length is " << tlength << std::endl;

    return tlength;
}

void PlaylistComponent::textEditorReturnKeyPressed(juce::TextEditor&)
{
    std::cout<<"Key pressed in playlist search called " <<std::endl;
    std::cout<<playlistSearch.getText() <<std::endl;
    juce::String searchText = playlistSearch.getText();
    
//    auto foundtrack = find_if(trackTitles.begin(), trackTitles.end(), searchText);
//    playlistSearch.getText()
    for (int i = -1; i == trackTitles.size(); i++)
    {
         if (trackTitles[i].contains(searchText))
         {
             std::cout<<"called"<<std::endl;
             std::cout<<"Index is " << i <<std::endl;
//             This selects the row marching the keyword in search box
             tableComponent.selectRow(i);
         }
    }
}

// This reads the plaulist file and fills the playlist on app start
void PlaylistComponent::ReadPlaylistFile()
{
        trackTitles.push_back("Track 1");
        trackTitles.push_back("Track 2");
        trackTitles.push_back("Track 3");
        trackTitles.push_back("Track 4");
        trackTitles.push_back("Track 5");
        trackTitles.push_back("Track 6");
    
        trackDurations.push_back("30");
        trackDurations.push_back("50");
        trackDurations.push_back("80");
        trackDurations.push_back("100");
        trackDurations.push_back("18");
        trackDurations.push_back("30");
    
}
// This adds files added to teh playlist by drag and drop to playlist.xml
void PlaylistComponent::ManagePlaylist(juce::File filename, juce::String title, juce::String duration)
{
    // Add details to the XML file
//    juce::XmlElement* playlistXmlElement = new juce::XmlElement();
//    juce::XmlElement* track = playlistXmlElement.createNewChildElement("Track");
//    juce::XmlElement* name = track->createNewChildElement("name");
//    name->addTextElement(juce::File(filename).getFileNameWithoutExtension());
//    juce::XmlElement* path = track->createNewChildElement("path");
//    path->addTextElement(juce::File(filename).getFullPathName());
//
//    playlistXmlElement.writeTo(juce::File{"/Users/Tamer/tracks/playlist.xml"});
//    playlistXmlElement.writeTo(juce::File{BinaryData::Playlist_xml});
    
    
}
