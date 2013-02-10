/*
 *  PulseDelayCore.h
 *  PulseDelay
 *
 *  Created by Nik Reiman on 29.12.05.
 *  Copyright 2005 Teragon Audio. All rights reserved.
 *
 */

#ifndef __PulseDelayCore_H
#define __PulseDelayCore_H

#ifndef __pluginCore_H
#include "pluginCore.h"
#endif

#ifndef __fxEnvelope_H
#include "fxEnvelope.h"
#endif

#ifndef __defaults_H
#include "defaults.h"
#endif

class PulseDelayCore : public pluginCore {
  public:
    PulseDelayCore(int num_params, int version, char *name);
    ~PulseDelayCore();
      
    void process(float **inputs, float **outputs, long frames);
    void reset();
    
  private:
    fxEnvelope *m_envelope;

    float m_delay_left[DEF_SAMPLE_RATE * (int)MAX_BUF_SECS];
    float m_delay_right[DEF_SAMPLE_RATE * (int)MAX_BUF_SECS];
    float m_amplitude_factor;
    
    long m_playback_max;
    long m_delay_index;
    long m_repeat_count;
    long m_offset_count;
    long m_buffer_index;
};

#endif
