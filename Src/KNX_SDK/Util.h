#ifndef KNX_SDK_UTIL
#define KNX_SDK_UTIL

#include "Defs.h"

#include <stdio.h>
#include <stdlib.h>

//Get FNV-1a hash
long long unsigned FNV_1a(char*str);
//Generate Prime number >2 at starting point
unsigned long long prime(unsigned long long);//deprecated until further notice

#endif