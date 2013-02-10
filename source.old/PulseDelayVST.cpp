/*
 *  PulseDelay - PulseDelayMain.cpp
 *  Created by Nik Reiman on 09.12.05
 *  Copyright (c) 2005 Teragon Audio, All rights reserved
 */

#ifndef __PulseDelayVST_H
#include "PulseDelayVST.h"
#endif

#ifndef __pluginCore_H
#include "pluginCore.h"
#endif

#ifndef __defaults_H
#include "defaults.h"
#endif

#ifdef DEBUG
#include <stdio.h>
#endif

AudioEffect* createEffectInstance(audioMasterCallback audioMaster) {
	return new PulseDelay(audioMaster);
}

PulseDelay::PulseDelay(audioMasterCallback audioMaster)
: AudioEffectX(audioMaster, 0, NUM_PARAMS) {
  setNumInputs(NUM_INPUTS);
  setNumOutputs(NUM_OUTPUTS);
  setUniqueID(UNIQUE_ID);
  
  core = new PulseDelayCore(NUM_PARAMS, VERSION, DEF_PRODUCT);
  
  m_sample_rate = getSampleRate();
  core->setParameter(PRM_SAMPLE_RATE, m_sample_rate, true);
  m_num_samples_counted = 0;
  m_last_bar = 0;
}

PulseDelay::~PulseDelay() {
  delete core;
}

bool PulseDelay::getEffectName(char* name) {
  strcpy(name, "PulseDelay");
  return true;
}

VstPlugCategory PulseDelay::getPlugCategory() {
  return kPlugCategEffect;
}

bool PulseDelay::getProductString(char* text) {
  strcpy(text, "PulseDelay");
  return true;
}

bool PulseDelay::getVendorString(char* text) {
  strcpy(text, "Teragon Audio");
  return true;
}

VstInt32 PulseDelay::getVendorVersion() {
  return 1000;
}

float PulseDelay::getParameter(VstInt32 index) {
  return core->getParameterNormalized(index);
}

void PulseDelay::getParameterDisplay(VstInt32 index, char *text) {
  core->getParameter(REQ_DISPLAY, index, text);
}

void PulseDelay::getParameterLabel(VstInt32 index, char *text) {
  core->getParameter(REQ_LABEL, index, text);
}

void PulseDelay::getParameterName(VstInt32 index, char *text) {
  core->getParameter(REQ_NAME, index, text);
}

void PulseDelay::processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames) {
  // Gets the tempo periodically
  m_host_time = getTimeInfo(kVstTransportCycleActive);
  if(m_host_time) {
    if(m_host_time->flags & kVstTransportPlaying) {
      m_tempo = m_host_time->tempo;
      if(m_host_time->barStartPos > m_last_bar +
        (((int)core->getParameter(REQ_VALUE_RAW, PRM_BAR_FREQ, NULL) - 1) * 4)) {
        core->setParameter(PRM_BUFLEN, m_num_samples_counted, true);
        core->setParameter(PRM_TEMPO, m_tempo, true);
        core->reset();
        m_num_samples_counted = 0;
        m_last_bar = m_host_time->barStartPos;
      }
    }
    else {
      m_last_bar = 0;
    }
  }

  core->process(inputs, outputs, sampleFrames); 
  m_num_samples_counted += sampleFrames;
}

void PulseDelay::setParameter(VstInt32 index, float value) {
  core->setParameterNormalized(index, value);
}