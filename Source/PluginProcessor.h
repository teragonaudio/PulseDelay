/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifndef __PLUGINPROCESSOR_H_A394BF9B__
#define __PLUGINPROCESSOR_H_A394BF9B__

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
class PulseDelayAudioProcessor : public AudioProcessor
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
    float getParameterScaled (float rawValue, float minValue, float maxValue) const;
    void setParameterScaled (double *destination, float scaledValue, float minValue, float maxValue);
    void processPluginState (double loopPositionPpq);

private:
    // Parameter definitions
    typedef enum {
        kParameterAttack,
        kParameterDecay,
        kParameterDryWetMix,

        kPamatererIntervalLength,
        kParameterIntervalCaptureAmount,
        kParameterIntervalCaptureOffset,

        kParameterNumPulses,
        kParameterPulseFadeAmount,
        kParameterTimeBetweenPulses,

        kNumParameters
    } ParameterName;

private:
    // Parameter constants and defaults
    static const int kParameterAttackMinValue = 1;
    static const int kParameterAttackMaxValue = 50;
    static const int kParameterAttackDefaultValue = 1;
    static const int kParameterDecayMinValue = 1;
    static const int kParameterDecayMaxValue = 100;
    static const int kParameterDecayDefaultValue = 1;
    static const float kParameterDryWetMixMinValue = 0.0f;
    static const float kParameterDryWetMixMaxValue = 1.0f;
    static const float kParameterDryWetMixDefaultValue = 0.5f;

    static const int kParameterIntervalLengthMinValue = 1;
    static const int kParameterIntervalLengthMaxValue = 16;
    static const int kParameterIntervalLengthDefaultValue = 4;
    static const int kParameterIntervalCaptureAmountMinValue = 1;
    static const int kParameterIntervalCaptureAmountMaxValue = 16;
    static const int kParameterIntervalCaptureAmountDefaultValue = 1;
    static const int kParameterIntervalCaptureOffsetMinValue = 0;
    static const int kParameterIntervalCaptureOffsetMaxValue = 15;
    static const int kParameterIntervalCaptureOffsetDefaultValue = 0;

    static const int kParameterNumPulsesMinValue = 0;
    static const int kParameterNumPulsesMaxValue = 16;
    static const int kParameterNumPulsesDefaultValue = 4;
    static const float kParameterPulseFadeAmountMinValue = 0.0f;
    static const float kParameterPulseFadeAmountMaxValue = 100.0f;
    static const float kParameterPulseFadeAmountDefaultValue = 25.0f;
    static const int kParameterTimeBetweenPulsesMinValue = 0;
    static const int kParameterTimeBetweenPulsesMaxValue = 250;
    static const int kParameterTimeBetweenPulsesDefaultValue = 0;

    // Local variables which are tied to parameters and their corresponding internal representations
    double paramAttackInMs;
    unsigned long attackInSamples;
    double paramDecayInMs;
    unsigned long decayInSamples;
    float paramDryWetMix;

    double paramIntervalLengthInBeats;
    double paramIntervalCaptureAmount;
    double paramIntervalCaptureOffsetInBeats;

    unsigned int paramNumPulses;
    unsigned int numPulsesRemaining;
    float paramPulseFadeAmount;
    float currentPulseAmplitude;
    double paramTimeBetweenPulsesInMs;
    double ppqBetweenPulses;

    // Delay buffer storage and position
    AudioSampleBuffer inputBuffers;
    unsigned long inputBufferIndex;

private:
    // Plugin states
    typedef enum {
        kPulseDelayStateWaitingForIntervalToStart,
        kPulseDelayStateReadingInterval,
        kPulseDelayStateWaitingToStartPulse,
        kPulseDelayStatePlayingPulse,
        kPulseDelayStateWaitingForNextInterval,
        kPulseDelayStateUndefined,
    } PulseDelayState;

private:
    // Delay state and PPQ positions for each event
    PulseDelayState state;
    double loopPositionPpq;
    // These variables mark the position in PPQ when each state *ends*, thus indicating a state change
    double stateWaitingForIntervalToStartPpq;
    double stateReadingIntervalPpq;
    double stateWaitingToStartPulsePpq;
    double statePlayingPulsePpq;
    double stateEndPulsePpq;
    double stateEndIntervalPpq;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PulseDelayAudioProcessor)
};

#endif  // __PLUGINPROCESSOR_H_A394BF9B__
