/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"

//==============================================================================
PulseDelayAudioProcessor::PulseDelayAudioProcessor() : inputBuffers(1, 1)
{
    paramAttackInMs = kParameterAttackDefaultValue;
    paramDecayInMs = kParameterDecayDefaultValue;
    paramDryWetMix = kParameterDryWetMixDefaultValue;

    paramIntervalLengthInBeats = kParameterIntervalLengthDefaultValue;
    paramIntervalCaptureAmount = kParameterIntervalCaptureAmountDefaultValue;
    paramIntervalCaptureOffsetInBeats = kParameterIntervalCaptureOffsetDefaultValue;

    paramNumPulses = kParameterNumPulsesDefaultValue;
    paramPulseFadeAmount = kParameterPulseFadeAmountDefaultValue;
    paramTimeBetweenPulsesInMs = kParameterTimeBetweenPulsesDefaultValue;

    reset();
}

PulseDelayAudioProcessor::~PulseDelayAudioProcessor()
{
}

//==============================================================================
float PulseDelayAudioProcessor::getParameterScaled (float rawValue, float minValue, float maxValue) const
{
    return (rawValue - minValue) / (maxValue - minValue);
}

float PulseDelayAudioProcessor::getParameter (int index)
{
    switch(index) {
        default:
            return 0.0f;
    }
}

void PulseDelayAudioProcessor::setParameterScaled(double *destination, float scaledValue, float minValue, float maxValue)
{
    *destination = scaledValue * (maxValue - minValue) + minValue;
}

void PulseDelayAudioProcessor::setParameter (int index, float newValue)
{
    switch(index) {
        default:
            break;
    }
}

const String PulseDelayAudioProcessor::getParameterName (int index)
{
    switch(index) {
        case kParameterAttack:
            return "Attack";
        case kParameterDecay:
            return "Decay";
        case kParameterDryWetMix:
            return "Dry/Wet";
        case kPamatererIntervalLength:
            return "Interval Length";
        case kParameterIntervalCaptureAmount:
            return "Interval Capture %";
        case kParameterIntervalCaptureOffset:
            return "Capture Offset";
        case kParameterNumPulses:
            return "Number of Pulses";
        case kParameterPulseFadeAmount:
            return "Pulse Fade Amount";
        case kParameterTimeBetweenPulses:
            return "Time Between Pulses";
        default:
            return String::empty;
    }
}

const String PulseDelayAudioProcessor::getParameterText (int index)
{
    switch(index) {
        default:
            return String::empty;
    }
}

//==============================================================================
void PulseDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    AudioPlayHead* playHead = getPlayHead();
    if (playHead == nullptr) {
        // TODO: Error message or something
        state = kPulseDelayStateUndefined;
        return;
    }
    AudioPlayHead::CurrentPositionInfo currentPosition;
    if (!playHead->getCurrentPosition(currentPosition)) {
        // TODO: Error message or something
        state = kPulseDelayStateUndefined;
        return;
    }

    double quarterNoteLengthInSec = 60.0 / currentPosition.bpm;
    double quarterNoteLengthInSamples = (quarterNoteLengthInSec * sampleRate);
    unsigned long maxIntervalInSamples = (unsigned long)(quarterNoteLengthInSamples * kParameterIntervalLengthMaxValue);
    inputBuffers.setSize(2, maxIntervalInSamples, false, true, true);
    inputBuffers.clear();
    inputBufferIndex = 0;

    attackInSamples = (unsigned long) ((paramAttackInMs / 1000.0) * sampleRate);
    decayInSamples = (unsigned long) ((paramDecayInMs / 1000.0) * sampleRate);

    numPulsesRemaining = paramNumPulses;
    currentPulseAmplitude = (100.0 - paramPulseFadeAmount) / 100.0;
    double timeBetweenPulsesInSec = paramTimeBetweenPulsesInMs / 1000.0;
    ppqBetweenPulses = timeBetweenPulsesInSec / quarterNoteLengthInSec;

    stateWaitingForIntervalToStartPpq = paramIntervalCaptureOffsetInBeats;
    printf("1 %f\n", stateWaitingForIntervalToStartPpq);
    stateReadingIntervalPpq = stateWaitingForIntervalToStartPpq + paramIntervalCaptureAmount;
    printf("2 %f\n", stateReadingIntervalPpq);
    // These states change after each pulse is played
    stateWaitingToStartPulsePpq = stateReadingIntervalPpq + ppqBetweenPulses;
    printf("3 %f\n", stateWaitingToStartPulsePpq);
    statePlayingPulsePpq = stateWaitingToStartPulsePpq + paramIntervalCaptureAmount;
    printf("4 %f\n", statePlayingPulsePpq);
    stateEndPulsePpq = statePlayingPulsePpq + ppqBetweenPulses;
    printf("5 %f\n", stateEndPulsePpq);
    // End of the interval, state is reset when this point is reached
    stateEndIntervalPpq = paramIntervalLengthInBeats;
    printf("6 %f\n", stateEndIntervalPpq);

    state = kPulseDelayStateWaitingForIntervalToStart;
}

void PulseDelayAudioProcessor::releaseResources()
{
}

void PulseDelayAudioProcessor::reset()
{
}

void PulseDelayAudioProcessor::processPluginState (double loopPositionPpq)
{
    if (loopPositionPpq <= stateWaitingForIntervalToStartPpq) {
        state = kPulseDelayStateWaitingForIntervalToStart;
        return;
    }

    // printf("Start state: %d\n", state);
    // Some slight abuse of the passthru behavior in the switch loop here...
    switch (state) {
        case kPulseDelayStateWaitingForIntervalToStart:
            if (loopPositionPpq > stateWaitingForIntervalToStartPpq) {
                state = kPulseDelayStateReadingInterval;
            }
            else {
                break;
            }
        case kPulseDelayStateReadingInterval:
            if (loopPositionPpq > stateReadingIntervalPpq) {
                state = kPulseDelayStateWaitingToStartPulse;
                currentPulseAmplitude = (100.0 - paramPulseFadeAmount) / 100.0;
                inputBufferIndex = 0;
                // TODO: Apply envelope here
            }
            else {
                break;
            }
        case kPulseDelayStateWaitingToStartPulse:
            if (loopPositionPpq > stateWaitingToStartPulsePpq) {
                state = kPulseDelayStatePlayingPulse;
                currentPulseAmplitude *= (100.0 - paramPulseFadeAmount) / 100.0;
            }
            else {
                break;
            }
        case kPulseDelayStatePlayingPulse:
            if (loopPositionPpq > statePlayingPulsePpq) {
                if (numPulsesRemaining == 0) {
                    state = kPulseDelayStateWaitingForNextInterval;
                }
                else if (loopPositionPpq >= stateEndIntervalPpq) {
                    state = kPulseDelayStateWaitingForIntervalToStart;
                }
                else {
                    state = kPulseDelayStateWaitingToStartPulse;
                    // TODO: Update state PPQ's
                    inputBufferIndex = 0;
                }
            }
            else {
                break;
            }
        case kPulseDelayStateWaitingForNextInterval:
        case kPulseDelayStateUndefined:
        default:
            break;
    }
    printf("Current state is %d\n", state);
}

void PulseDelayAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i) {
        buffer.clear (i, 0, buffer.getNumSamples());
    }

    AudioPlayHead* playHead = getPlayHead();
    if(playHead) {
        AudioPlayHead::CurrentPositionInfo currentPosition;
        if (playHead->getCurrentPosition(currentPosition)) {
            loopPositionPpq = currentPosition.ppqPosition;
            // Essentially, we want to take the modulus of the current position by the interval size,
            // but the % operator only works for integers, so instead subtrack the interval length
            // until we get the same result. This is a bit hacky, and there is probably a better way
            // to do this. Anyone know how?
            while (loopPositionPpq > paramIntervalLengthInBeats) {
                loopPositionPpq -= paramIntervalLengthInBeats;
            }

            processPluginState(loopPositionPpq);
        }
        else {
            state = kPulseDelayStateUndefined;
        }
    }
    else {
        state = kPulseDelayStateUndefined;
    }

    if (state == kPulseDelayStateUndefined) {
        return;
    }

    for (int channel = 0; channel < getNumInputChannels(); ++channel) {
        float* channelData = buffer.getSampleData(channel);
        float* inputBuffer = inputBuffers.getSampleData(channel);
        float outValue;
        for (int i = 0; i < buffer.getNumSamples(); ++i) {
            outValue = channelData[i];
            if (state == kPulseDelayStateReadingInterval) {
                inputBuffer[inputBufferIndex++] = channelData[i] * paramDryWetMix;
            }
            else if (state == kPulseDelayStatePlayingPulse) {
                outValue += inputBuffer[inputBufferIndex++] * currentPulseAmplitude;
            }
            channelData[i] = outValue;
        }
    }
}

//==============================================================================
//==============================================================================
void PulseDelayAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    XmlElement xml(JucePlugin_Name);
    for (int i = 0; i < getNumParameters(); ++i) {
        // TODO: xml.setAttribute(getParameterNameForStorage(i), (double)getParameter(i));
    }
    copyXmlToBinary(xml, destData);
}

void PulseDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != 0 && xmlState->hasTagName(JucePlugin_Name)) {
        for (int i = 0; i < getNumParameters(); i++) {
            // TODO: setParameter(i, (float) xmlState->getDoubleAttribute(getParameterNameForStorage(i)));
        }
        reset();
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PulseDelayAudioProcessor();
}
