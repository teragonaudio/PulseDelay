/*
 *  PulseDelayVST - PulseDelayVST.h
 *  Created by Nik Reiman on 09.12.05
 *  Copyright (c) 2005 Teragon Audio, All rights reserved
 */

#ifndef __PulseDelayVST_H
#define __PulseDelayVST_H

#ifndef __PulseDelayCore_H
#include "PulseDelayCore.h"
#endif

#ifndef __audioeffectx__
#include "audioeffectx.h"
#endif

#ifndef __defaults_H
#include "defaults.h"
#endif

class PulseDelay : public AudioEffectX {
  public:
    PulseDelay(audioMasterCallback audioMaster);
    ~PulseDelay();

    // Processes
    virtual void processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames);

    // Parameters
    virtual void setParameter(VstInt32 index, float value);
    virtual float getParameter(VstInt32 index);
    virtual void getParameterLabel(VstInt32 index, char *label);
    virtual void getParameterDisplay(VstInt32 index, char *text);
    virtual void getParameterName(VstInt32 index, char *text);

    virtual bool getEffectName(char* name);
    virtual bool getVendorString(char* text);
    virtual bool getProductString(char* text);
    virtual VstInt32 getVendorVersion();

    virtual VstPlugCategory getPlugCategory();

  protected:

  private:
    PulseDelayCore *core;
    VstTimeInfo *m_host_time;

    double m_last_bar;
    float m_sample_rate;
    float m_tempo;
    long m_num_samples_counted;
};

#endif
