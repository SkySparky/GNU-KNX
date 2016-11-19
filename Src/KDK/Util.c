#include "Util.h"

#include <stdio.h>

LUI _FNV_1A(char * str){

#if BITVRS == 64
  LUI FNV_OFFSET  = 14695981039346656037LL;
  LUI FNV_PRIME   = 1099511628211LL;
#else
  LUI FNV_OFFSET  = 2166136261LL;
  LUI FNV_PRIME   = 16777619LL;
#endif

LUI hash = FNV_OFFSET;

char * iter = str;

while (*iter){
  hash = (hash ^ *iter) * FNV_PRIME;
  ++iter;
}

return hash;
}

void printlineC(char * str, char * color){
  printC(str, color);
  printf("\r\n");
}

void printC(char * str, char * color){
  printf("%s%s",color, str);
}

void printReset()
{
  printf(COL_RESET);
}
