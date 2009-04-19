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

#if __ppc__
#define VST_FORCE_DEPRECATED 0
#else
#define VST_FORCE_DEPRECATED 1
#endif

#define PLUGGUI 1
#define USE_PC_AU 1
#include "defaults.h"
