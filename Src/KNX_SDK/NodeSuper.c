#include "NodeSuper.h"


bool addChild(nodeBase*nb)
{
if (nb==NULL)
	return false;

//create temporary buffer
baseNode**tmp = baseNode*[numChildren];
//copy contents
for (unsigned x=0; x<numChildren; ++x)
	tmp[x]=children[x];
tmp[numChildren]=nb;
children=tmp;
++numChildren;
return true;
}

bool removeChild(nodeBase*nb)
{

return true;
}

bool setParent(nodeBase*nb)
{
//parents are immutable after generation
if (parent!=NULL || nb==NULL)
	return false;

parent=nb;

return true;
}