/*
 *  xcode_vst_prefix.h
 *  KickMaker
 *
 *  Created by Nik Reiman on 16.02.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#define MAC 1
#define MACX 1
#define QUARTZ 1

#define USE_NAMESPACE 0
#define TARGET_API_MAC_CARBON 1
#define USENAVSERVICES 1
#define __CF_USE_FRAMEWORK_INCLUDES__

#if __MWERKS__
#define __NOEXTENSIONS__
#endif

#include <Carbon/Carbon.h>
#include <AvailabilityMacros.h>

#define VST_FORCE_DEPRECATED 0

#define USE_PC_VST 1
#include "defaults.h"