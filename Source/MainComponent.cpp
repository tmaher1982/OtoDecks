#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (0, 2); // Setting to zero to avoid the glitch sounds as no input is needed, and only have a clean clear output
    }
    
    // addAndMakeVisible(button);
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    
    addAndMakeVisible(toggleButton);
    
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    volSlider.addListener(this);
    speedSlider.addListener(this);
    
    volSlider.setRange(0.0, 1.0);
 
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
    
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
   // transportSource.getNextAudioBlock(bufferToFill);
//    resampleSource.getNextAudioBlock(bufferToFill
    player1.getNextAudioBlock(bufferToFill);
    
}



//void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
//{
//    // Your audio-processing code goes here!
//
//    // For more details, see the help for AudioProcessor::getNextAudioBlock()
//
//    // Right now we are not producing any data, in which case we need to clear the buffer
//    // (to prevent the output of random noise)
//
//    if (!playing)
//    {
//        bufferToFill.clearActiveBufferRegion();
//        return;
//    }
//
//    auto* leftChan = bufferToFill.buffer -> getWritePointer(0,
//                                                            bufferToFill.startSample);
//    auto* rightChan = bufferToFill.buffer -> getWritePointer(0,
//                                                            bufferToFill.startSample);
//
//    for (auto i = 0; i < bufferToFill.numSamples; ++i)
//    {
//        // double sample = rand.nextDouble() * 0.25;
//        //double sample = fmod(phase, 0.2);
//
//        double sample = sin(phase) *  0.1;
//
//        leftChan[i] = sample;
//        rightChan[i] = sample;
//
//        //phase += 0.05;
////        phase += 0.005;
//        phase += dphase;
//    }
//
//    //bufferToFill.clearActiveBufferRegion();
//}



void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
    
    //transportSource.releaseResources();
    player1.releaseResources();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
    g.setFont(20.0f);
    //g.drawText("Hello form London", getLocalBounds(), juce::Justification::centred, true);
    
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    double rowH = getHeight() /5;
    //button.setBounds(0, 0, getWidth(), getHeight()/2);
    playButton.setBounds(0, 0, getWidth(), rowH);
    stopButton.setBounds(0, rowH , getWidth(), rowH);
    
    volSlider.setBounds(0, rowH * 2, getWidth(), rowH);
    speedSlider.setBounds(0, rowH * 3, getWidth(), rowH);
    
    loadButton.setBounds(0, rowH * 4, getWidth(),rowH);
    toggleButton.setBounds(0, rowH * 5  , getWidth(), rowH);
    
}

void MainComponent::buttonClicked(juce::Button* button)
{
    // Querying the memory address of which button was clicked
    if (button == &playButton)
    {
        std::cout << "PLay button was clicked" << std::endl;
//        transportSource.start();
        //playing = true;
        
        player1.start();
    }
    if (button == &stopButton)
    {
        std::cout << "Stop button was clicked" << std::endl;
//        transportSource.stop();
        //playing = false;
        player1.stop();
    }
    
    if (button == &loadButton)
    {
        juce::FileChooser chooser{"Select a file..."};
        if (chooser.browseForFileToOpen())
        {
//            loadURL(juce::URL{chooser.getResult()});
            player1.loadURL(URL{chooser.getResult()});
        }
    }
}


void MainComponent::sliderValueChanged (juce::Slider *slider)
{
    // to detect which slider
    if (slider == &volSlider)
    {
        
    }
    
    if (slider == &speedSlider)
    {
        
    }
    
}

