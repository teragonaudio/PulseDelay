/*
*	File:		PulseDelay.r
*	
*	Version:	1.0
* 
*	Created:	12.12.05
*	
*	Copyright:  Copyright © 2005 Teragon Audio, All Rights Reserved
* 
*/

#include <AudioUnit/AudioUnit.r>

#ifndef __defaults_H
#include "defaults.h"
#endif

// Note that resource IDs must be spaced 2 apart for the 'STR ' name and description
#define kAudioUnitResID_PulseDelay 1000

#define PulseDelay_COMP_SUBTYPE 'PlDl'
#define PulseDelay_COMP_MANF 'Tera'
#ifdef DEBUG
#define kPulseDelayVersion 0xFFFFFFFF
#else
#define kPulseDelayVersion 0x00010000	
#endif

//////////////////////////////////////////////////////////////////////////////
#define RES_ID kAudioUnitResID_PulseDelay
#define COMP_TYPE kAudioUnitType_Effect
#define COMP_SUBTYPE PulseDelay_COMP_SUBTYPE
#define COMP_MANUF PulseDelay_COMP_MANF	

#define VERSION kPulseDelayVersion
#define NAME "Teragon Audio: PulseDelay"
#define DESCRIPTION "PulseDelay AU"
#define ENTRY_POINT "PulseDelayEntry"

#include "AUResources.r"