#ifndef KNX_SDK_UTIL
#define KNX_SDK_UTIL

#include "Defs.h"
#include "Data.h"

#include <stdio.h>
#include <stdlib.h>

//Get FNV-1a hash
long long unsigned FNV_1a(char*str);
//Generate Prime number >2 at starting point
unsigned long long prime(unsigned long long);//deprecated until further notice
//0=non numeric, 1=floating 2=short 3=integer 4=long long
unsigned isNumeric(char*string, unsigned length);
//return false if div/0
bool math(token*start, unsigned length);

#endif