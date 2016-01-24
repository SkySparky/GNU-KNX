#include "NodeSuper.h"

#include <stdlib.h>
#include "XMem.h"

baseNode*genBaseNode(_nsDb*db)
{
baseNode*curr = malloc (sizeof(baseNode));

if (curr==NULL)
	return NULL;

curr->parent=NULL;
curr->children=(baseNode**)malloc(0);
curr->numChildren=0;
curr->handle=0;
curr->active=true;
curr->prntErr=true;
curr->prntWrn=true;

curr->local=malloc(sizeof(database));
curr->global=db;

return curr;
}

bool setupBaseNode(baseNode*curr,_nsDb*db)
{
if (curr==NULL)
	return false;

curr->parent=NULL;
curr->children=(baseNode**)malloc(0);
curr->numChildren=0;
curr->handle=0;
curr->active=true;
curr->prntErr=true;
curr->prntWrn=true;

curr->local=malloc(sizeof(database));
curr->global=db;

return true;
}

bool freeBaseNode(baseNode*target)
{

if (target==NULL)
	return true;

bool scc=true;
//free all children
for (unsigned x=0; x<target->numChildren; ++x)
	if (!freeBaseNode(target->children[x]))
		scc=false;

if (scc)
	free(target);

return scc;
}

bool addChild(baseNode*target)
{

return true;
}

bool removeChild(baseNode*target)
{

return true;
}


bool setParent(baseNode*target)
{

return true;
}
