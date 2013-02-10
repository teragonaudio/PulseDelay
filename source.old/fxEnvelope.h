/*
 *  fxEnvelope.h
 *  PulseDelay
 *
 *  Created by Nik Reiman on 05.01.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxEnvelope_H
#define __fxEnvelope_H

#ifndef __effectCore_H
#include "effectCore.h"
#endif

#include <stdio.h>

enum {
  fxEnvelope_PRM_ATTACK,
  fxEnvelope_PRM_DECAY,
  fxEnvelope_PRM_ENVELOPE_SIZE,
  fxEnvelope_PRM_SAMPLE_RATE,
  fxEnvelope_NUM_PARAMS
};

class fxEnvelope : public effectCore {
public:
  fxEnvelope(pluginCore *p, int num_params = fxEnvelope_NUM_PARAMS);
  ~fxEnvelope();
  
  void process(float &input);
  void process(float *inputs, long frames);
  void process(float *in_left, float *in_right, long frames);
  void recache();
protected:
  long m_index;
  long m_attack_end;
  long m_decay_start;
  long m_decay_end;
private:
};

#endif