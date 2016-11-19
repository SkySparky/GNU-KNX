#ifndef KDK_UTIL
#define KDK_UTIL

#include "Macro.h"

#define COL_RED     "\x1b[31m"
#define COL_GREEN   "\x1b[32m"
#define COL_YELLOW  "\x1b[33m"
#define COL_BLUE    "\x1b[34m"
#define COL_MAGENTA "\x1b[35m"
#define COL_CYAN    "\x1b[36m"
#define COL_RESET   "\x1b[0m"

LUI _FNV_1A(char * str);

void printC(char *, char *);
void printlineC(char *, char *);
void printReset();

#endif
