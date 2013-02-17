/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"

//==============================================================================
PulseDelayAudioProcessor::PulseDelayAudioProcessor()
{
}

PulseDelayAudioProcessor::~PulseDelayAudioProcessor()
{
}

//==============================================================================
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

//==============================================================================
void PulseDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
}

void PulseDelayAudioProcessor::releaseResources()
{
}

void PulseDelayAudioProcessor::reset() {

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
