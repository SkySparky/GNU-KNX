#include "State.h"
#include <math.h>
#include "../KNX_SDK/Defs.h"

//state factory
state*genState()
{
state * ret = malloc(sizeof(struct state));
ret->global = (database*) genDatabase();
ret->registrar = (node**) malloc(0);
ret->registered=0;
ret->options.prntWrn=1;
ret->options.prntErr=1;
ret->options.prntSys=1;
ret->options.prntEcho=1;
ret->options.prntDbg=0;
ret->options.tabAssist=1;
ret->options.dbgLog=0;
ret->tabSize=4;
ret->maxNodes=SYSTEM_MAX_NODES;
ret->stdin_hndle=NULL;
ret->sizeLevel=0;

ret->dirPath=malloc(256);

#if PLATFORM == PLATFORM_LINUX
#include <unistd.h>
readlink("/proc/self/exe", ret->dirPath, 255);
strncpy(ret->dirPath+strlen(ret->dirPath)-3, "std/\0", 5);
#else
#include <windows.h>//ADD SUPPORT FOR WINDOWS
ret->dirPath=NULL;
#endif

return ret;
}

void freeState(state * st)
{
free (st->global);
free (st);
}

//register new node
node* validateNode(state*st,node*parent)
{
if (st==NULL || (st->registered==st->maxNodes))
	return NULL;

node*curr = nodeGen(st->global);
if (curr==NULL)
	return NULL;

//assign handle
bool validID=false;
unsigned idIndex=0;
for (;idIndex<st->maxNodes && idIndex<st->registered && !validID; ++idIndex)
{
	if (st->options.prntDbg)
		printf(">> %u %u\n", idIndex, st->registered);
	validID=true;
	if (primeList[idIndex]==st->registrar[idIndex]->nb.handle)
		{
		validID=false;
		continue;
		}
}

node**tmpReg = st->registrar;

//reallocate memory
tmpReg=realloc(tmpReg,st->registered+1 * sizeof(node*));
if (tmpReg==NULL)
	return NULL;
st->registrar=tmpReg;
++st->registered;

curr->nb.handle=primeList[idIndex];
curr->nb.parent=parent==NULL?NULL:(baseNode*)parent;

//check for root control
st->stdin_hndle=st->stdin_hndle==NULL?curr:NULL;

st->registrar[st->registered-1]=curr;

return curr;
}

//deregister node
bool invalidateNode(state*st, node*target)
{
if (st==NULL)
	return false;

for (unsigned x=0; x<st->registered; ++x)
{
	if (st->options.prntDbg)
		printf("%p _>>_ %p\n", target, st->registrar[x]);
	if (st->registrar[x]==target)
	{
		//deregister all children
		for (unsigned c=0; c<target->nb.numChildren; ++c)
			if (!invalidateNode(st, (node*)target->nb.children[c]) && st->options.prntSys)
				printf("Node at location %p failed to collapsed\n",target->nb.children[c]);

		free(target);
		for (unsigned y=x+1; y<st->registered-1; ++y)//shift nodes down
			st->registrar[y-1]=st->registrar[y];
		--st->registered;
		node**tmpReg = st->registrar;
		tmpReg=realloc(tmpReg, st->registered*sizeof(node*));
		if (tmpReg==NULL && st->registered!=0)
			return false;
		break;
	}
}

return true;
}

void printRegistrar(state*st)
{
if (st==NULL)
	return;

printf("\t\tREGISTRAR : %d\n\n",st->registered);
for (unsigned x=0; x<st->registered; ++x)
	printf("\t\t\t%u\n", st->registrar[x]->nb.handle);

}
