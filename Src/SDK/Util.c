#include "Util.h"

#include <string.h>
#include <stdlib.h>

unsigned long long FNV_1A(const char*input)
{
  unsigned len = (unsigned) strlen(input);

  #if BITMODE == 64
  unsigned long long hash = 14695981039346656037ULL;
  #elif BITMODE == 32
  unsigned long long hash = 2166136261;
  #endif

  for (unsigned x=0; x<len; ++x)
  	{
  		hash^=input[x];
  		#if BITMODE==64
  		hash*=0xb3;
  		#elif BITMODE==32
  		hash*=0x93;
  		#endif
  	}

    return hash;
}

int isNumeric(char*raw, unsigned sIndex, unsigned eIndex)
{
  char * seg = 0;
  size_t len=0;
  if ((sIndex==0) && (eIndex==0))
    {
      len=strlen(raw);
      seg=raw;
    }
  else
    {
      seg=malloc((eIndex-sIndex)+1);
      len=eIndex-sIndex;
    }

    return 0;
}
