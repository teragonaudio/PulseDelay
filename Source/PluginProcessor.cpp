/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
PulseDelayAudioProcessor::PulseDelayAudioProcessor()
{
}

PulseDelayAudioProcessor::~PulseDelayAudioProcessor()
{
}

//==============================================================================
const String PulseDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int PulseDelayAudioProcessor::getNumParameters()
{
    return 0;
}

float PulseDelayAudioProcessor::getParameter (int index)
{
    return 0.0f;
}

void PulseDelayAudioProcessor::setParameter (int index, float newValue)
{
}

const String PulseDelayAudioProcessor::getParameterName (int index)
{
    return String::empty;
}

const String PulseDelayAudioProcessor::getParameterText (int index)
{
    return String::empty;
}

const String PulseDelayAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String PulseDelayAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool PulseDelayAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool PulseDelayAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool PulseDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PulseDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PulseDelayAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

int PulseDelayAudioProcessor::getNumPrograms()
{
    return 0;
}

int PulseDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PulseDelayAudioProcessor::setCurrentProgram (int index)
{
}

const String PulseDelayAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void PulseDelayAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void PulseDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void PulseDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void PulseDelayAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < getNumInputChannels(); ++channel)
    {
        float* channelData = buffer.getSampleData (channel);

        // ..do something to the data...
    }

    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
}

//==============================================================================
bool PulseDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* PulseDelayAudioProcessor::createEditor()
{
    return new PulseDelayAudioProcessorEditor (this);
}

//==============================================================================
void PulseDelayAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PulseDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PulseDelayAudioProcessor();
}
