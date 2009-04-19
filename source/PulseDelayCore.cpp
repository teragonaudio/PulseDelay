/*
 *  PulseDelayCore.cpp
 *  PulseDelay
 *
 *  Created by Nik Reiman on 29.12.05.
 *  Copyright 2005 Teragon Audio. All rights reserved.
 *
 */

#ifndef __PulseDelayCore_H
#include "PulseDelayCore.h"
#endif

PulseDelayCore::PulseDelayCore(int num_params, int version, char *name) : pluginCore(num_params, version, name) {
  addParameter(PRM_AMP_DECAY, "Amp. Decay", TYP_PERCENT, 1.0, 100.0, 75.0);
  addParameter(PRM_ATTACK, "Attack", TYP_SECONDS, MIN_ATTACK, MAX_ATTACK, MIN_ATTACK);
  addParameter(PRM_BAR_FREQ, "Bar Repeat", TYP_ABS_CENTS, 1, 8, 1);
  addParameter(PRM_BUFLEN, "Buffer Length", TYP_SAMPLEFRAMES, 1.0, MAX_BUF_SECS, MAX_BUF_SECS, true);
  addParameter(PRM_DECAY, "Decay", TYP_SECONDS, MIN_DECAY, MAX_DECAY, MIN_DECAY);
  addParameter(PRM_DRYWET, "Dry/Wet", TYP_GENERIC, 0.0, 1.0, 0.5);
  addParameter(PRM_INPUT_OFFSET, "Input Offset", TYP_SECONDS, 0.0, 1.0, 0.0);
  addParameter(PRM_OUTPUT_OFFSET, "Output Offset", TYP_SECONDS, 0.0, 1.0, 0.0);
  addParameter(PRM_PLAYBACK_MAX, "Buffer Playback", TYP_PERCENT, 0.0, 100.0, 25.0);
  addParameter(PRM_REPEAT, "Repeat", TYP_GENERIC, 1, 20, 1);
  addParameter(PRM_SAMPLE_RATE, "Sample Rate", TYP_HZ, 32000, 96000, DEF_SAMPLE_RATE, true);
  addParameter(PRM_SPAN, "Repeat span", TYP_SAMPLEFRAMES, 0, 10000, 2000);
  addParameter(PRM_TEMPO, "Tempo", TYP_BPM, 60.0, 180.0, 120.0, true);
  
  memset(m_delay_left, 0x0, sizeof(float) * DEF_SAMPLE_RATE * MAX_BUF_SECS);
  memset(m_delay_right, 0x0, sizeof(float) * DEF_SAMPLE_RATE * MAX_BUF_SECS);
    
  // Set up fx
  m_envelope = new fxEnvelope(this);
  m_envelope->linkParameter(PRM_ATTACK, fxEnvelope_PRM_ATTACK);
  m_envelope->linkParameter(PRM_DECAY, fxEnvelope_PRM_DECAY);
  m_envelope->linkParameter(PRM_BUFLEN, fxEnvelope_PRM_ENVELOPE_SIZE);
  m_envelope->linkParameter(PRM_SAMPLE_RATE, fxEnvelope_PRM_SAMPLE_RATE);
  
  reset();
}

PulseDelayCore::~PulseDelayCore() {
  delete m_envelope;
}

void PulseDelayCore::reset() {
  m_repeat_count = (int)PARAM(PRM_REPEAT);
  m_offset_count = (int)(PARAM(PRM_OUTPUT_OFFSET) * PARAM(PRM_SAMPLE_RATE));
  m_amplitude_factor = PARAM(PRM_AMP_DECAY) / 100.0;
  m_playback_max = (int)((PARAM(PRM_PLAYBACK_MAX) / 100.0) * PARAM(PRM_BUFLEN)) + (int)PARAM(PRM_SPAN);

  m_delay_index = 0;
  m_buffer_index = 0;
  m_envelope->recache();
}

void PulseDelayCore::process(float **inputs, float **outputs, long frames) {
  float *in_left = inputs[0];
  float *in_right = inputs[1];
  float *out_left = outputs[0];
  float *out_right = outputs[1];
  
  // TODO: Apply input and output offsets properly
  int in_offset = (int)(PARAM(PRM_INPUT_OFFSET) * PARAM(PRM_SAMPLE_RATE));
  int out_offset = (int)(PARAM(PRM_OUTPUT_OFFSET) * PARAM(PRM_SAMPLE_RATE));

  // Safety catch
  if(m_delay_index + frames > DEF_SAMPLE_RATE * (int)MAX_BUF_SECS) {
    m_delay_index = 0;
  }
  if(m_buffer_index + frames > DEF_SAMPLE_RATE * (int)MAX_BUF_SECS) {
    m_buffer_index = 0;
  }
  
  float outl = 0.0f, outr = 0.0f;
  for(int i = 0; i < frames; ++i, ++m_delay_index, ++m_buffer_index) {
    outl = in_left[i] * (1.0 - PARAM(PRM_DRYWET));
    outr = in_right[i] * (1.0 - PARAM(PRM_DRYWET));
    
    // TODO: Apply enveloper here
    m_delay_left[m_buffer_index] = in_left[i] * PARAM(PRM_DRYWET);
    m_delay_right[m_buffer_index] = in_right[i] * PARAM(PRM_DRYWET);

    // Repeat feature
    if(m_repeat_count > 0) {
      if(m_delay_index > m_playback_max) {
        m_delay_index = 0;
        //m_offset_count = (int)PARAM(PRM_SPAN);
        --m_repeat_count;
        m_amplitude_factor *= PARAM(PRM_AMP_DECAY) / 100.0f;
      }
      
      outl += m_delay_left[m_delay_index] * m_amplitude_factor;
      outr += m_delay_right[m_delay_index] * m_amplitude_factor;
    }
    
    out_left[i] = outl;
    out_right[i] = outr;
  }
}
