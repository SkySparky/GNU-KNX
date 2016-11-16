#include "Util.h"

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

while (iter != 0){
  hash = (hash ^ *iter) * FNV_PRIME;
}

return hash;
}
