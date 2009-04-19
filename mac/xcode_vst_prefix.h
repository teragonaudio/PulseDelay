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

#define USE_NAMESPACE 0

#define TARGET_API_MAC_CARBON 1
#define USENAVSERVICES 1

#define __CF_USE_FRAMEWORK_INCLUDES__

#if __MWERKS__
#define __NOEXTENSIONS__
#endif

#define QUARTZ 1

#define MAC_OS_X_VERSION_MIN_REQUIRED   1020
#define MAC_OS_X_VERSION_MAX_ALLOWED	1030

#include <Carbon/Carbon.h>
#include <AvailabilityMacros.h>

#define VST_FORCE_DEPRECATED 0