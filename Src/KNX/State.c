#include "State.h"

//state factory
state*genState()
{
state * ret = malloc(sizeof(struct state));
ret->registrar = (node*) malloc(0);
ret->registered=0;
ret->prntWrn=1;
ret->prntErr=1;
ret->prntSys=1;
ret->maxNodes=SYSTEM_MAX_NODES;
return ret;
}

//register new node
node* validateNode(state*st,node*parent)
{
if (st->registered==st->maxNodes)
	if (st->prntSys)
		{
		printf("Node limit reached: node generation failed\n");
		return NULL;
		}

//attempt to find available handle prime
unsigned long long handle=0;

unsigned pDex=0;

for (; pDex<SYSTEM_MAX_NODES; ++pDex)
{
	bool collision=false;
	printf("Attempt %u : %u registered\n",primeList[pDex], st->registered);
	for (unsigned y=0; y<st->registered; ++y)
		if (primeList[pDex]==st->registrar[y].nb.handle)
			{
			++pDex;
			collision=true;
			break;
			}
	if (pDex==SYSTEM_MAX_NODES && collision)//no available handles
			if (st->prntSys)
				{
				printf("Node generation failed\n");
				return NULL;
				}
	if (!collision)
		break;
}

//resize child targets
node*tmpReg = (node*) realloc(st->registrar, st->registered + 1);
if (tmpReg==NULL)
	{
		if (st->prntSys)
			printf("Node memory reallocation failed\n");
		return NULL;
	}else
	{
		node*nd = nodeGen();
		nd->nb.handle=primeList[pDex];
		nd->nb.parent=(baseNode*)parent;
		st->registrar=tmpReg;
		++st->registered;
		return nd;
	}
return NULL;
}

//deregister node
node* invalidateNode(state*st, node*target)
{
if (st==NULL)
	return NULL;

	
	
return NULL;
}