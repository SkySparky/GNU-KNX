#ifndef KDK_CONTRACT
#define KDK_CONTRACT

#include <stdio.h>
#include "Macro.h"

/*
Provides an interface for modules to call
Implemented by the runtime engine
*/

extern char * RegisterModule();
extern bool RegisterObject();

#endif
