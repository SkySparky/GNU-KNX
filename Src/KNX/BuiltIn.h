#ifndef KNX_INTERNAL_FNC
#define KNX_INTERNAL_FNC

typedef struct state __state;

#include "KNX.h"

#define FNC_LENGTH     6

#if BITMODE==64
static unsigned long long fncList[FNC_LENGTH] = {
0xf6915548f781cd55,//short
0x2b9fff192bd4c83e,//int
0xcde8c9ad70d16733,//long
0xf2a393910b5b3ebd,//char
0x826e83195d0d60f0,//str
0xe79e4d608e807965//exit
};
#else
static unsigned long long fncList[FNC_LENGTH] = {
0xba226bd5,//short
0x95e97e5e,//int
0xc2ecdf53,//long
0xa84c031d,//char
0xc24bd190,//str
0xcded1a85//exit
};
#endif

bool isFunction(char*,unsigned);

token * _fnc_exit(token*, unsigned terms, __state*);

#endif
