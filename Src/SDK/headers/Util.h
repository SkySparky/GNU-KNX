#ifndef KNX_SDK_UTIL
#define KNX_SDK_UTIL

/*
Provides useful operations
*/
//Hashing
unsigned long long FNV_1A(const char*);

//Numerics: 0=NAN, 1=int+,2=int-,3=float
int isNumber(char*,unsigned, unsigned);

#endif
