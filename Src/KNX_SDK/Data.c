#include "Data.h"
#include "Util.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

token*genToken(token*parent)
{
token*ret = malloc(sizeof(token));
if (ret==NULL)
	return NULL;

ret->type=0;
ret->data=NULL;
ret->raw=true;
ret->flg=0;

return ret;
}

//add memory deletion
void freeToken(token*target)
{
if (target!=NULL)
	free(target);
}

flag setFlag(flag flg, char*input)
{
unsigned len=strlen(input);
char * tmp = malloc(len+1);
strncpy(tmp,input,len);
tmp[len]='\0';
toLower(tmp);

for (unsigned x=0; x<len; ++x)
	{
		int base=tmp[x]-97;
		flg|=(flag)pow(2,base);
	}
free(tmp);
return flg;
}
