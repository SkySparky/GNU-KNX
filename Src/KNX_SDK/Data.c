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
ret->order=0;
ret->next=NULL;
ret->prev=NULL;

return ret;
}

//add memory deletion
void freeToken(token*target)
{
if (target==NULL)
	return;
//delete non-managed data types
if (target->raw)
{
switch (target->type)
{
	case _mInt: free((int*)target->data); break;
	case _mShort: free((short*)target->data); break;
	case _mLong: free((long*)target->data); break;
	case _mDbl: free((double*)target->data); break;
	case _mBool: free((bool*)target->data); break;
	case _mChar: free((char*)target->data); break;
	case _mStr: free((char*)target->data); break;
	case _mStruct:
	//collapse structure
	break;
	default:break;
}
}
free(target);
}

void freeStrand(token*target)
{
if (target==NULL)
	return;

do {
	token*next=target->next;
	freeToken(target);
	target=next;
} while(target!=NULL);
}

token*getTail(token*ret)
{
	if (ret==NULL)
		return NULL;

	while (ret->next!=NULL)
		ret=ret->next;

	return ret;
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
