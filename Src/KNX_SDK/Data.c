#include "Data.h"

#include <stdlib.h>

token*genToken(token*parent)
{
token*ret = malloc(sizeof(token));
if (ret==NULL)
	return NULL;

ret->type=0;
ret->data=NULL;
ret->raw=true;

return ret;
}

void freeToken(token*target)
{
if (target!=NULL)
	free(target);
}
