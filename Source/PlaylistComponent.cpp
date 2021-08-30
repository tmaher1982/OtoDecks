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
PlaylistComponent::PlaylistComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    trackTitles.push_back("Track 1");
    trackTitles.push_back("Track 2");
    trackTitles.push_back("Track 3");
    trackTitles.push_back("Track 4");
    trackTitles.push_back("Track 5");
    trackTitles.push_back("Track 6");
    
    
    tableComponent.getHeader().addColumn("Track title", 1, 400); // Making 1 instead of 0 for juce 6
    tableComponent.getHeader().addColumn("", 2, 200); // Making 1 instead of 0 for juce 6
    tableComponent.getHeader().addColumn("", 3, 200); // One more column for the delete button
    
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
    g.drawText(trackTitles[rowNumber], 2, 0 , width -4, Height, Justification::centredLeft, true);
}

Component* PlaylistComponent::refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate)
{
    
    if (columnId == 2)
    {
        if (existingComponentToUpdate == nullptr)
        {

            // Gave play button a prefix ID of 10000
            TextButton* btn = new TextButton{"play"};
            String id{std::to_string(rowNumber + 10000)};
            btn->setComponentID(id);
            
            btn ->addListener(this);
            existingComponentToUpdate = btn;
            
        }
    }

    if (columnId == 3)
    {
        if (existingComponentToUpdate == nullptr)
        {
            TextButton* btn2 = new TextButton{"delete"};

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
        std::cout<< "PlaylistComponent::DELET EbuttonClicked" << trackTitles[id2] << std::endl;
    }
    
    // Detects if the button is a Play button
    else
    {
        // Gives back the track ID to play
        id = id - 10000;
        std::cout<< "PlaylistComponent::Play buttonClicked" << trackTitles[id] << std::endl;
    }
        
    
}
