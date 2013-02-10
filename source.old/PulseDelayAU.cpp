/*
 *  PulseDelayAU.cpp
 *  PulseDelay
 *
 *  Created by Nik Reiman on 16.01.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __PulseDelayAU_H
#include "PulseDelayAU.h"
#endif

#ifndef __PulseDelayCore_H
#include "PulseDelayCore.h"
#endif

#ifndef __defaults_H
#include "defaults.h"
#endif

COMPONENT_ENTRY(PulseDelay);

PulseDelay::PulseDelay(AudioUnit component) : AUEffectBase(component) {
	CreateElements();
	Globals()->UseIndexedParameters(NUM_PARAMS);
  
  core = new PulseDelayCore(NUM_PARAMS, VERSION, DEF_PRODUCT);
  
  // Get the sample rate and push it into the plugin
  Float64 srate;
  if(DispatchGetProperty(kAudioUnitProperty_SampleRate, kAudioUnitScope_Global, 0, &srate) !=
     kAudioUnitErr_InvalidProperty) {
    SetParameter(PRM_SAMPLE_RATE, kAudioUnitScope_Global, 0, srate, 0);
  }
  
  m_last_beat = 0;
  m_num_samples_counted = 0;
  m_last_sample_count = 0;
  
#if AU_DEBUG_DISPATCHER
	mDebugDispatcher = new AUDebugDispatcher(this);
#endif
}

ComponentResult PulseDelay::GetParameter(AudioUnitParameterID inID,
                                         AudioUnitScope inScope,
                                         AudioUnitElement inElement,
                                         Float32& outValue) {
  outValue = core->getParameter(REQ_VALUE, inID, NULL);
  return noErr;
}

ComponentResult	PulseDelay::GetParameterInfo(AudioUnitScope inScope,
                                             AudioUnitParameterID inParameterID,
                                             AudioUnitParameterInfo &outParameterInfo) {
	ComponentResult result = noErr;
  
	outParameterInfo.flags = kAudioUnitParameterFlag_IsWritable
    |	kAudioUnitParameterFlag_IsReadable;
  
  if(inScope == kAudioUnitScope_Global) {
    char *c_name = new char[24];
    core->getParameter(REQ_NAME, inParameterID, c_name);
    CFStringRef name = CFStringCreateWithCString(kCFAllocatorDefault, c_name, 0);
    delete [] c_name;

    AUBase::FillInParameterName(outParameterInfo, name, false);
    outParameterInfo.unit = (AudioUnitParameterUnit)core->getParameter(REQ_LABEL, inParameterID, NULL);
    outParameterInfo.minValue = core->getParameter(REQ_VALUE_MIN, inParameterID, NULL);
    outParameterInfo.maxValue = core->getParameter(REQ_VALUE_MAX, inParameterID, NULL);
    outParameterInfo.defaultValue = core->getParameter(REQ_VALUE_DEF, inParameterID, NULL);
	}
  else {
    result = kAudioUnitErr_InvalidParameter;
  }
  
	return result;
}

ComponentResult	PulseDelay::GetParameterValueStrings(AudioUnitScope inScope,
                                                     AudioUnitParameterID inParameterID,
                                                     CFArrayRef *outStrings) {
  return kAudioUnitErr_InvalidProperty;
}

OSStatus PulseDelay::ProcessBufferLists(AudioUnitRenderActionFlags &ioActionFlags,
                                        const AudioBufferList &inBuffer,
                                        AudioBufferList &outBuffer,
                                        UInt32 inFramesToProcess) {
  OSStatus err = DispatchGetProperty(kAudioUnitProperty_HostCallbacks, kAudioUnitScope_Global, 0, &m_hci);
  if(err == noErr) {
    if(m_hci.beatAndTempoProc) {
      Float64 beat, tempo;
      m_hci.beatAndTempoProc(m_hci.hostUserData, &beat, &tempo);
      if(beat > m_last_beat + ((int)core->getParameter(REQ_VALUE, PRM_BAR_FREQ, NULL) * 4.0)) {        
        core->setParameter(PRM_BUFLEN, m_num_samples_counted - m_last_sample_count, true);
        core->setParameter(PRM_TEMPO, tempo, true);
        core->reset();
        m_num_samples_counted = 0;
        m_last_sample_count = 0;
        m_last_beat = beat;
      }
    }
  }
  
  Boolean playing = true;
  if(m_hci.transportStateProc) {
    Boolean transchanged, iscycling;
    Float64 samplein, outstart, outend;
    m_hci.transportStateProc(m_hci.hostUserData, &playing, &transchanged, &samplein,
                             &iscycling, &outstart, &outend);
  }
  
  if(playing) {
    // call the kernels to handle either interleaved or deinterleaved
    if(inBuffer.mNumberBuffers == 1) {
      // process each interleaved channel individually
      float **inputs = new float*[2];
      inputs[0] = (float*)inBuffer.mBuffers[0].mData;
      inputs[1] = (float*)inBuffer.mBuffers[0].mData + 1;
      
      float **outputs = new float*[2];
      outputs[0] = (float*)outBuffer.mBuffers[0].mData;
      outputs[1] = (float*)outBuffer.mBuffers[0].mData + 1;
      
      core->process(inputs, outputs, inFramesToProcess);
    }
    else {
      float **inputs = new float*[2 * sizeof(float*)];
      inputs[0] = (float*)inBuffer.mBuffers[0].mData;
      inputs[1] = (float*)inBuffer.mBuffers[1].mData;
      
      float **outputs = new float*[2 * sizeof(float*)];
      outputs[0] = (float*)outBuffer.mBuffers[0].mData;
      outputs[1] = (float*)outBuffer.mBuffers[1].mData;
      
      core->process(inputs, outputs, inFramesToProcess);
    }
    
    m_num_samples_counted += inFramesToProcess;
  }
  return noErr;
}

ComponentResult PulseDelay::SetParameter(AudioUnitParameterID inID,
                                         AudioUnitScope inScope,
                                         AudioUnitElement inElement,
                                         Float32 inValue,
                                         UInt32 inBufferOffsetInFrames) {
  core->setParameter(inID, inValue);
  return noErr;
}