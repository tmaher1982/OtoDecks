#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (0, 2); // Setting to zero to avoid the glitch sounds as no input is needed, and only have a clean clear output
    }
    
    addAndMakeVisible(deckGUI1);
    addAndMakeVisible(deckGUI2);
    addAndMakeVisible(deckGUI3);
    
    addAndMakeVisible(playlistComponent);
    
    formatManager.registerBasicFormats();
   
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
    
    
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    player2.prepareToPlay(samplesPerBlockExpected, sampleRate);
    player3.prepareToPlay(samplesPerBlockExpected, sampleRate);
    
    //mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    
    mixerSource.addInputSource(&player1, false);
    mixerSource.addInputSource(&player2, false);
    mixerSource.addInputSource(&player3, false);
    
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
   // transportSource.getNextAudioBlock(bufferToFill);
//    resampleSource.getNextAudioBlock(bufferToFill
    
//    player1.getNextAudioBlock(bufferToFill);
    mixerSource.getNextAudioBlock(bufferToFill);
    
    
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
    
    //transportSource.releaseResources();
    player1.releaseResources();
    player2.releaseResources();
    player3.releaseResources();
    mixerSource.releaseResources();
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
    g.setFont(20.0f);
    //g.drawText("Hello form London", getLocalBounds(), juce::Justification::centred, true);
    
}

void MainComponent::resized()
{

        deckGUI1.setBounds(0,0,getWidth()/3, getHeight()/2);
        deckGUI2.setBounds(getWidth()/3, 0, getWidth()/3, getHeight() /2 );
        deckGUI3.setBounds(getWidth()* 2/3, 0, getWidth()/3, getHeight() /2 );
    
    playlistComponent.setBounds(0, getHeight()/2,getWidth(),getHeight()/2);
    
}
