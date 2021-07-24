/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 13 Jul 2021 10:28:56pm
    Author:  Tamer Maher

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

using namespace juce;

class DJAudioPlayer : public AudioSource
{
    public:
        DJAudioPlayer(AudioFormatManager& _formatManager);
        ~DJAudioPlayer();
    
        //==============================================================================
        void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
        void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
        void releaseResources() override;
    
        void loadURL(URL audioURL);
        void setGain(double gain);
        void setSpeed(double ratio);
        void setPosition(double posInSecs);
        void setPositionRelative(double pos);
        
        void start();
        void stop();
        
        /** get the relative position of the playhead */
        double getPositionRelative();
    private:
        AudioFormatManager& formatManager;
        std::unique_ptr<AudioFormatReaderSource> readerSource;
        AudioTransportSource transportSource;
        ResamplingAudioSource resampleSource{&transportSource, false, 2};
};
