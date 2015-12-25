#include "State.h"
#include <math.h>

//state factory
state*genState()
{
state * ret = malloc(sizeof(struct state));
ret->registrar = (node**) malloc(0);
ret->registered=0;
ret->prntWrn=1;
ret->prntErr=1;
ret->prntSys=1;
ret->maxNodes=SYSTEM_MAX_NODES;
ret->stdin_hndle=NULL;
ret->sizeLevel=0;
return ret;
}

//register new node
node* validateNode(state*st,node*parent)
{
return NULL;
}

//deregister node
node* invalidateNode(state*st, node*target)
{
return NULL;
}

void printRegistrar(state*st)
{
if (st==NULL)
	return;

printf("\t\tREGISTRAR : %d\n\n",st->registered);
for (unsigned x=0; x<st->registered; ++x)
{
if (st->stdin_hndle==NULL)
	printf("STDIN : NULL >> %p\n",st->stdin_hndle);
else
	printf("STDIN : %d >> %p\n",st->stdin_hndle->nb.handle, st->stdin_hndle);

node*curr = st->registrar[x];
if (curr==NULL)
	{
	printf("NULL");
	continue;
	}
//handle, number of children, prntErr, prntWrn, active
printf("Node %u\t|%u\t|%d\t|%d\t|%d\n",curr->nb.handle,curr->nb.numChildren, curr->nb.prntErr, curr->nb.prntWrn, curr->nb.active);
for (unsigned y=0; y<curr->nb.numChildren; ++y)
	if (curr->nb.children[y]!=NULL)
		printf("\t\tCHILD >> %u %p\n",curr->nb.children[y]->handle, curr->nb.children[y]);
	else
		printf("\t\tCHILD >> NULL\n");
}
}