#include "NodeSuper.h"

#include <stdlib.h>

typedef struct baseNode _bNode;

_bNode*genBaseNode()
{
_bNode*curr = malloc (sizeof(_bNode));

if (curr==NULL)
	return NULL;

curr->parent=NULL;
curr->children=(_bNode**)malloc(0);
curr->numChildren=0;
curr->handle=0;
curr->active=true;
curr->prntErr=true;
curr->prntWrn=true;

return curr;
}

bool setupBaseNode(_bNode*curr)
{
if (curr==NULL)
	return false;

curr->parent=NULL;
curr->children=(_bNode**)malloc(0);
curr->numChildren=0;
curr->handle=0;
curr->active=true;
curr->prntErr=true;
curr->prntWrn=true;

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
