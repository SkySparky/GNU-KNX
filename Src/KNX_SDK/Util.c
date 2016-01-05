#include "Util.h"

#include "limits.h"

//typedef struct token _token;

#include <string.h>

//Get FNV-1a hash
long long unsigned FNV_1a(char*str)
{
printf(">> %s\n",str);
#ifdef ENVIORNMENT64
unsigned long long _offset=0xcbf29ce484222325;
unsigned long long _prime=0x100000001b3;
printf("x32 %llu\n",_offset);
#else//32 bit
unsigned long long _offset=0x811C9DC5;
unsigned long long _prime=0x93;
printf("x32 %llu\n",_offset);
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

//0=non numeric, 1=floating 2=short 3=integer 4=long long
unsigned isNumeric(char*string, unsigned length)
{
if (string==NULL)
	return 0;

bool decimal=false;

for (unsigned x=0; x<length; ++x)
	if (string[x]>='0' && string[x]<='9')
		continue;
	else if (string[x]=='.')
		if (decimal)
			return 0;
		else
		{
		decimal=true;
		}
			
	else
		return 0;

if (decimal)
	return 1;
	
long long chk = atoll(string);

if (chk<=SHRT_MAX)
	return 2;
if (chk<=INT_MAX)
	return 3;
return 4;
}

//return 0 if div/0 or invalid token
bool math(token*start, unsigned length)
{
if (start==NULL)
	return false;

char**values;
char*operators;
unsigned valueIndex=0;
unsigned operatorIndex;

//sort into lists

//begin calculation


return true;
}