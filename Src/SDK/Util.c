#include "headers/Util.h"

#include <string.h>
#include <stdlib.h>
#include <limits.h>

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

int isNumber(char*raw, unsigned sIndex, unsigned eIndex)
{
    char rb = 0;
    char neg = 0;

    if (!(sIndex<eIndex))
      return 0;

    if (raw[sIndex]=='-')
    {
      neg=1;
      ++sIndex;
    }

    for (unsigned x=sIndex; x<eIndex; ++x)
    {
      if ((raw[x]<'0' || raw[x]>'9') && (raw[x]!='.'))
        return 0;
      if (raw[x]=='.')
        {
          if (rb==1)
            return 0;
          else
            rb=1;
        }
    }

    if (rb)//decimal
      return 3;
    else
      return neg?2:1;
    return 0;
}
