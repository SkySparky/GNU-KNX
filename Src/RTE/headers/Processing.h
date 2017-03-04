#ifndef KNX_PROC
#define KNX_PROC

#include "Lang.h"

#include "KNode.h"

/*
Return 0 if statement finished
Return 1 if statement incomplete
Return 2 if statement experienced error 
*/
int Tokenize(Node*, char * raw);

#endif
