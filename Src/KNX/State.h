#ifndef KNX_STATE
#define KNX_STATE

#include "KNX.h"

/*
Stores system state information
Defines macros
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

/*
Directs IO
Stores/validates/manages all nodes
Stores master databases
*/
typedef struct state
{
node*registrar;//node bank

}state;

//register new node
bool validateNode(state*);
//deregister node
bool unvalidateNode(state*);

#endif