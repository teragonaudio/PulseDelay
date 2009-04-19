/*
 *  defaults.h
 *  PulseDelay
 *
 *  Created by Nik Reiman on 30.12.05.
 *  Copyright 2005 Teragon Audio. All rights reserved.
 *
 */

#ifndef __defaults_H
#define __defaults_H

#define DEF_PRODUCT "PulseDelay"
#define MAJ_VERSION 1
#define MIN_VERSION 1
#define REL_BRANCH 'r'
#define VERSION ((MAJ_VERSION * 1000) + (MIN_VERSION * 10))

enum {
  PRM_TEMPO,
  PRM_SAMPLE_RATE,
  PRM_BUFLEN,
  PRM_BAR_FREQ,
  PRM_ATTACK,
  PRM_DECAY,
  PRM_DRYWET,
  PRM_INPUT_OFFSET,
  PRM_OUTPUT_OFFSET,
  PRM_PLAYBACK_MAX,
  PRM_REPEAT,
  PRM_SPAN,
  PRM_AMP_DECAY,
  NUM_PARAMS
};

#define NUM_INPUTS 2
#define NUM_OUTPUTS 2
#define UNIQUE_ID 'PlDl'

#define DEF_SAMPLE_RATE 44100
#define MAX_BUF_SECS 8.0
#define MIN_ATTACK 0.1
#define MAX_ATTACK 1.0
#define MIN_DECAY 0.1
#define MAX_DECAY 1.0

#ifdef USE_PC_AU
#ifdef DEBUG
#define kPulseDelayVersion 0xFFFFFFFF
#else
#define kPulseDelayVersion 0x00010000	
#endif
#endif

#endif