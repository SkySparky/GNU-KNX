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
ret->nb.active=true;

ret->nb.prntErr=true;
ret->nb.prntWrn=true;

//construct base class

return ret;
};

int nodeProc(state*sys, node*parent, char*cmd)
{
printf("Enter node proc\n");
//validate node
node*current=validateNode(sys,parent);
if (current!=NULL)
	printf("Node %u registered\n",current->nb.handle);
else{
	printf("Registration failed\n");
	return -1;
}

//begin loop procedure
while (current->nb.active)
{

}

//invalidate loop
do{
current=invalidateNode(sys,current);

//implement attempt to resolve invalidation

}while (current!=NULL);

return 0;
};