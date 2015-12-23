#include "Util.h"
#include "Defs.h"

#include <string.h>

//Get FNV-1a hash
long long unsigned FNV_1a(char*str)
{
#ifdef ENVIORNMENT64
unsigned long long _offset=0xcbf29ce484222325;
unsigned long long _prime=0x100000001b3;
#else//32 bit
unsigned long long _offset=0x811C9DC5;
unsigned long long _prime=0x93;
#endif

unsigned long long hash=_offset;

unsigned len = strlen(str);

for (unsigned x=0; x<len; ++x)
	{
	hash = hash^str[x];
	hash *= _prime;
	}

	return hash;
}

//Generate Prime number >2 at starting point
unsigned long long prime(unsigned long long offset)
{
unsigned val=3, dex=2;



return 0;

}