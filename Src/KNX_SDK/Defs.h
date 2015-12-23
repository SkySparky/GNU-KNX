/*
Sets up important macros
*/

//Determine bit version and platform
#if _WIN32 || _WIN64
#define PLATFORM_WINDOWS
#if _WIN64
#define ENVIORNMENT64
#else
#define ENVIORNMENT32
#endif
#endif

#if __GNUC__
#define PLATFORM_LINUX
#if __x86_64__ || __ppc64__
#define ENVIORNMENT64
#else
#define ENVIORNMENT32
#endif
#endif

#ifndef KNX_SDK_MACROS
#define KNX_SDK_MACROS

//define booleans
typedef unsigned char bool;
#define true 1
#define false 0

//type simplifications
typedef unsigned long long llui;

#endif