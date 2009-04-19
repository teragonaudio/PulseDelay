/*
 *  PulseDelayAU.h
 *  PulseDelay
 *
 *  Created by Nik Reiman on 16.01.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __PulseDelayAU_H
#define __PulseDelayAU_H

#ifndef __PulseDelayCore_H
#include "PulseDelayCore.h"
#endif

#ifndef __defaults_H
#include "defaults.h"
#endif

#include "AUCarbonViewBase.h"
#include "AUCarbonViewControl.h"
#include "AUEffectBase.h"

#if AU_DEBUG_DISPATCHER
#include "AUDebugDispatcher.h"
#endif

class PulseDelay : public AUEffectBase {
  public:
    PulseDelay(AudioUnit component);
#if AU_DEBUG_DISPATCHER
    virtual ~PulseDelay() { delete mDebugDispatcher; }
#endif
    
    virtual	ComponentResult GetParameterValueStrings(AudioUnitScope inScope,
                                                     AudioUnitParameterID inParameterID,
                                                     CFArrayRef *outStrings);
    virtual ComponentResult GetParameter(AudioUnitParameterID inID,
                                         AudioUnitScope inScope,
                                         AudioUnitElement inElement,
                                         Float32& outValue);
    virtual	ComponentResult GetParameterInfo(AudioUnitScope inScope,
                                             AudioUnitParameterID	inParameterID,
                                             AudioUnitParameterInfo	&outParameterInfo);
    virtual OSStatus ProcessBufferLists(AudioUnitRenderActionFlags &ioActionFlags,
                                        const AudioBufferList &inBuffer,
                                        AudioBufferList &outBuffer,
                                        UInt32 inFramesToProcess);
    virtual ComponentResult SetParameter(AudioUnitParameterID inID,
                                         AudioUnitScope inScope,
                                         AudioUnitElement inElement,
                                         Float32 inValue,
                                         UInt32 inBufferOffsetInFrames);
    
    virtual	bool SupportsTail() { return false; }
    virtual ComponentResult	Version() { return kPulseDelayVersion; }
  protected:
  private:
    PulseDelayCore *core;
    AUParameterListenerRef m_listener;
    HostCallbackInfo m_hci;
    
    float m_last_beat;
    long m_last_sample_count;
    long m_num_samples_counted;
};

#endif