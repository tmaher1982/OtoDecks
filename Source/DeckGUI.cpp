/*
  ==============================================================================

    DeckGUI.cpp
    Created: 16 Jul 2021 2:01:06pm
    Author:  Tamer Maher

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player, juce::AudioFormatManager & formatManagerToUse, juce::AudioThumbnailCache & cacheToUse) : player(_player), waveformDisplay(formatManagerToUse, cacheToUse)
{
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);
    
    addAndMakeVisible(waveformDisplay);
    
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    
    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);
    
    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.0, 100.0);
    posSlider.setRange(0.0, 1.0);
    
    startTimer(500);
    
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (juce::Graphics& g)
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
    g.drawText ("DeckGUI", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void DeckGUI::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    double rowH = getHeight() /8;
    
    playButton.setBounds(0, 0, getWidth(), rowH);
    stopButton.setBounds(0, rowH , getWidth(), rowH);
    
    volSlider.setBounds(0, rowH * 2, getWidth(), rowH);
    speedSlider.setBounds(0, rowH * 3, getWidth(), rowH);
    posSlider.setBounds(0,rowH * 4, getWidth(),rowH);
    waveformDisplay.setBounds(0, rowH * 5, getWidth(), rowH * 2);
    loadButton.setBounds(0, rowH * 7, getWidth(),rowH);

}

void DeckGUI::buttonClicked(Button* button)
{
    // Querying the memory address of which button was clicked
    if (button == &playButton)
    {
        std::cout << "PLay button was clicked" << std::endl;
//        transportSource.start();
        //playing = true;

        player->start();
    }
    if (button == &stopButton)
    {
        std::cout << "Stop button was clicked" << std::endl;
//        transportSource.stop();
        //playing = false;
        player->stop();
    }

    if (button == &loadButton)
    {
        FileChooser chooser{"Select a file..."};
        if (chooser.browseForFileToOpen())
        {
//            loadURL(juce::URL{chooser.getResult()});
            player->loadURL(URL{chooser.getResult()});
            waveformDisplay.loadURL(URL{chooser.getResult()});
        }
    }
}


void DeckGUI::sliderValueChanged (Slider *slider)
{
//    // to detect which slider
    if (slider == &volSlider)
    {
        player->setGain(slider -> getValue());
    }

    if (slider == &speedSlider)
    {
        player->setSpeed(slider -> getValue());
    }

    if (slider == &posSlider)
    {
        player->setPositionRelative(slider -> getValue());
    }
    
}

bool DeckGUI::isInterestedInFileDrag(const StringArray &files)
{
    std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
    return true;
    
}


void DeckGUI::filesDropped (const StringArray &files, int x, int y)
{
    std::cout << "DeckGUI::filesDropped" << std::endl;
    if(files.size() == 1)
    {
        player->loadURL(URL{File{files[0]}});
    }
}

void DeckGUI::timerCallback()
{
    // std::cout << "DeckGUI::timerCallback" << std::endl;
    waveformDisplay.setPositionRelative(player->getPositionRelative());
}


