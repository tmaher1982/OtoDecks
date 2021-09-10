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
    
//    playImage = ImageCache::getFromFile(File::getCurrentWorkingDirectory().getChildFile & ("Play.png"));
//    static Image playImage = ImageCache::getFromMemory(const void* Play.png, int 47000);
//    Image playImage = ImageCache::getFromMemory(BinaryData::Play_png, BinaryData::Play_pngSize);
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
    g.drawText ("Relative Position", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
    
    
//    playButton.setImages(false, false, true, playImage, 1.0f, {}, playImage, 1.0f, {}, playImage, 1.0f, {});
}

void DeckGUI::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    double rowH = getHeight() /8;
    
//    playButton.setImages(false, false, true, playImage, 1.0f, {Colour(0xff3c1818)}, playImage, 1.0f, {Colour(0xff3c1818)}, playImage, 1.0f, {Colour(0xff3c1818)});
//    playButton.setImages(false, false, true, playImage, 1.0f, {}, playImage, 1.0f, {}, playImage, 1.0f, {});
    playButton.setBounds(0, 0, getWidth(), rowH);
    
    // Changing the look and feel of play button
    playButton.setColour(0x1000100, juce::Colours::green);
    stopButton.setBounds(0, rowH , getWidth(), rowH);
    
    // Changing the look and feel of Stop button
    stopButton.setColour(0x1000100, juce::Colours::indianred);
    volSlider.setBounds(0, rowH * 2, getWidth(), rowH);
    
    // Changing the Look and Feel for Volume Slider for R2A
    volSlider.setSliderStyle (Slider::Slider::RotaryHorizontalDrag);

    volSlider.setRange(0.0f, 1.0f, 0.01f);
    volSlider.setColour(Slider::ColourIds::thumbColourId, Colours::darkorange);
    
    // Changing the Look and Feel for speed Slider
    
    speedSlider.setBounds(0, rowH * 3, getWidth(), rowH);
    speedSlider.setRange(0.0f, 1.0f, 0.01f);
    speedSlider.setSliderStyle (Slider::Slider::RotaryHorizontalDrag);
    speedSlider.setColour(Slider::ColourIds::thumbColourId, Colours::darkorange);
    
    // Changing the Look and Feel for speed Slider and Pos Slider
    
    posSlider.setBounds(0,rowH * 4, getWidth(),rowH);
    posSlider.setColour(Slider::ColourIds::thumbColourId, Colours::darkorange);
    
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


