#ifndef KNX_KEYWORD
#define KNX_KEYWORD

#include "../SDK/headers/Util.h"

#include "Lexile.h"

/*
Defines 32/64 bit FNV-1A hashtable for keywords
Provides method for creating tokens from keywords
*/

#define KW_SIZE 45

#ifndef BITMODE
#error BITMODE not declared
#endif

extern unsigned long long kwTabel[KW_SIZE];


//0 if not keyword, 1 if found
int isKeyword(char*, Interpreter*);

Token * getKeyword(char*, Interpreter*);

#endif
