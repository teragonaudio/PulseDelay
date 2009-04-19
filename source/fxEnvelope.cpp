/*
 *  fxEnvelope.cpp
 *  PulseDelay
 *
 *  Created by Nik Reiman on 05.01.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxEnvelope_H
#include "fxEnvelope.h"
#endif

fxEnvelope::fxEnvelope(pluginCore *p, int num_params) : effectCore(p, fxEnvelope_NUM_PARAMS) {
  m_index = 0;
  m_attack_end = 0;
  m_decay_start = 0;
  m_decay_end = 0;
}

fxEnvelope::~fxEnvelope() {
}

inline void fxEnvelope::process(float &input) {
  if(m_index < m_attack_end) {
    input *= m_index / m_attack_end;  
  }
  else if(m_index > m_decay_start) {
    input *= (-1.0 * (m_index - m_decay_start) / (m_decay_end)) + 1.0;
  }
  else if(m_index > m_decay_end + m_decay_start) {
    input = 0.0;
  }

  ++m_index;
}

inline void fxEnvelope::process(float *inputs, long frames) {
 for(int i = 0; i < frames; ++i) {
   process(inputs[i]);
 }
}

inline void fxEnvelope::process(float *in_left, float *in_right, long frames) {
  for(int i = 0; i < frames; ++i) {
    process(in_left[i]);
    process(in_right[i]);
  }
}

void fxEnvelope::recache() {
  m_attack_end = *m_params[fxEnvelope_PRM_ATTACK] * *m_params[fxEnvelope_PRM_SAMPLE_RATE] + 1;
  m_decay_start = *m_params[fxEnvelope_PRM_ENVELOPE_SIZE] * *m_params[fxEnvelope_PRM_SAMPLE_RATE];
  m_decay_end = *m_params[fxEnvelope_PRM_DECAY] * *m_params[fxEnvelope_PRM_SAMPLE_RATE] + 1;
}