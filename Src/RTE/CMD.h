#ifndef KNX_CMD
#define KNX_CMD

#include "Macro.h"

/*
Defines methods used in command line interpretation
*/


bool parseCMD(int, char **);

void printHelp();
void printVersion();

#endif
