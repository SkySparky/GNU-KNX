#include "Data.h"

#include <stdlib.h>

token*getTail(token*target)
{
if (target==NULL)
	return NULL;

token*tail=target;

while (tail->next!=NULL)
	tail=tail->next;

return tail;
}

token*genToken(token*parent)
{
token*ret = malloc(sizeof(token));
if (ret==NULL)
	return NULL;

ret->type=0;
ret->data=NULL;
ret->raw=true;
ret->next=NULL;
ret->previous=parent;

if (parent!=NULL)
	parent->next=ret;

return ret;
}

void freeToken(token*target)
{
if (target!=NULL)
{
	if (target->next!=NULL)
		freeToken(target->next);
	free(target);
}
	
		
}