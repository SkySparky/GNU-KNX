#include "Node.h"
#include <stdlib.h>

node*nodeGen()
{
node*ret = (node*) malloc(sizeof(node*));

if (ret==NULL)
	{
	printf("Node Gen Failed\n");
	return NULL;
	}

//construct super class
ret->nb.parent=NULL;
ret->nb.children=NULL;

ret->nb.numChildren=0;

ret->nb.handle=0;
ret->nb.active=true;

ret->nb.prntErr=true;
ret->nb.prntWrn=true;

//construct base class
if (ret!=NULL)
	printf("Alloc at %p\n", ret);
else printf("NULL CONSTRUCT\n");


return ret;
};

int nodeProc(state*sys, node*parent, char*cmd)
{
//validate node
node*current=validateNode(sys,parent);
if (current!=NULL)
	printf("Node %u registered\n",current->nb.handle);
else{
	printf("Registration failed\n");
return -1;
}

printRegistrar(sys);

//begin loop procedure
while (current->nb.active && 0)
{

}

unsigned rec = current->nb.handle;
//invalidate loop
do{
current=invalidateNode(sys,current);
if (current!=NULL)
	if (sys->prntSys)
		printf("Deregistration failed\n");
//implement attempt to resolve invalidation

}while (current!=NULL && 0);
printf("Node %u invalidated\n", rec);
printRegistrar(sys);
return 0;
};