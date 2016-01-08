#ifndef KNX_SDK_DEBUG
#define KNX_SDK_DEBUG

#include "NodeSuper.h"
#include "Data.h"

void prntMemory();//print all memory in pushed scope
void prntTree(baseNode*);//print node tree from pushed value
void prntTokens(token**, unsigned);

#endif
