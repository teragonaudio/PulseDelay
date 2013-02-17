/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifndef __PLUGINPROCESSOR_H_A394BF9B__
#define __PLUGINPROCESSOR_H_A394BF9B__

#include "../JuceLibraryCode/JuceHeader.h"


enum {
  kParameterAmpDecay,
  kParameterAmpAttack,
  kParameterBarRepeat,
  kParameterBufferLength,
  kPamatererDecayLength,
  kParameterWetDryMix,
  kParameterInputOffset,
  kParameterOutputOffset,
  kParameterBufferPlaybackPercent,
  kParameterRepeatOn,

  kNumParameters
};

//==============================================================================
class PulseDelayAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    PulseDelayAudioProcessor();
    ~PulseDelayAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();
    void reset();

    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);

    //==============================================================================
    AudioProcessorEditor* createEditor() { return NULL; }
    bool hasEditor() const { return false; }

    //==============================================================================
    const String getName() const { return JucePlugin_Name; }

    int getNumParameters() { return kNumParameters; }
    float getParameter (int index);
    void setParameter (int index, float newValue);

    const String getParameterName (int index);
    const String getParameterText (int index);

    const String getInputChannelName (int channelIndex) const { return String (channelIndex + 1); }
    const String getOutputChannelName (int channelIndex) const { return String (channelIndex + 1); }
    bool isInputChannelStereoPair (int index) const { return true; }
    bool isOutputChannelStereoPair (int index) const { return true; }

    bool acceptsMidi() const { return false; }
    bool producesMidi() const { return false; }
    bool silenceInProducesSilenceOut() const { return false; }

    //==============================================================================
    int getNumPrograms() { return 0; }
    int getCurrentProgram() { return 0; }
    void setCurrentProgram (int index) {}
    const String getProgramName (int index) { return String::empty; }
    void changeProgramName (int index, const String& newName) {}

    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PulseDelayAudioProcessor)
};

#endif  // __PLUGINPROCESSOR_H_A394BF9B__
