/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 13 Jul 2021 10:28:56pm
    Author:  Tamer Maher

  ==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(AudioFormatManager& _formatManager) : formatManager(_formatManager)
{
    
}

DJAudioPlayer::~DJAudioPlayer()
{
    
}

void DJAudioPlayer::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    
}

void DJAudioPlayer::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    //transportSource.getNextAudioBlock(bufferToFill);
    resampleSource.getNextAudioBlock(bufferToFill);
    
}

void DJAudioPlayer::releaseResources()
{
    transportSource.releaseResources();
    resampleSource.releaseResources();
}

// R1 : Load Audio file into audio players
void DJAudioPlayer::loadURL(URL audioURL)
{
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
       if (reader != nullptr) // good file!
        {
           std::unique_ptr<juce::AudioFormatReaderSource> newSource (new juce::AudioFormatReaderSource (reader, true));
           transportSource.setSource( newSource.get(), 0, nullptr, reader -> sampleRate);
           readerSource.reset (newSource.release());
           
        }
}

// R1: Can mix the tracks by varuing each of their volumes
void DJAudioPlayer::setGain(double gain)
{
    if(gain < 0 || gain > 1.0)
    {
        std::cout << "DJAudioPlayer::setGain gain should be between 0 and 1" << std::endl;
    }
    else
    {
        transportSource.setGain(gain);
    }
}

// R1: Can speed up and slow down tracks
void DJAudioPlayer::setSpeed(double ratio)
{
    if(ratio < 0 || ratio > 100)
    {
        std::cout << "DJAudioPlayer::setSpeed ratio should be between 0 and 100" << std::endl;
    }
    else
    {
        resampleSource.setResamplingRatio(ratio);
    }
    
}

void DJAudioPlayer::setPosition(double posInSecs)
{
    transportSource.setPosition(posInSecs);
}

void DJAudioPlayer::setPositionRelative(double pos)
{
    if(pos < 0 || pos > 1.0)
    {
        std::cout << "DJAudioPlayer::setPositionRelative should be between 0 and 1" << std::endl;
    }
    else
    {
        
        double posInSecs = transportSource.getLengthInSeconds()  * pos;
        
        setPosition(posInSecs);
    }
}

void DJAudioPlayer::start()
{
    transportSource.start();
}

void DJAudioPlayer::stop()
{
    transportSource.stop();
}

double DJAudioPlayer::getPositionRelative()
{
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}
