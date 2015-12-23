#include "Node.h"
#include <stdlib.h>

node*nodeGen()
{
node*ret = (node*) malloc(sizeof(node*));

//construct super class
ret->nb.parent=NULL;
ret->nb.children=NULL;

ret->nb.numChildren=0;

ret->nb.handle=0;

ret->nb.prntErr=true;
ret->nb.prntWrn=true;

//construct base class

return ret;
};

int nodeProc(node*parent, char*cmd)
{

//validate node

//begin loop procedure

//invalidate loop

return 0;
};