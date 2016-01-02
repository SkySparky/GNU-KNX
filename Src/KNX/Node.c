#include "Node.h"
#include "Interpreter.h"
#include <stdlib.h>

node*nodeGen()
{
node*ret = (node*) malloc(sizeof(node));

if (ret==NULL)
	{
	printf("Node Gen Failed\n");
	return NULL;
	}

//construct super class
genBaseNode(&ret->nb);

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
interpreter*intr = genInterpreter(sys,current);
if (intr==NULL)
	{
	invalidateNode(sys,current);
	return 0;
	}
//begin loop procedure
bool activeReading = false;
unsigned length = 0;
char * string = malloc (10);

while (current->nb.active)
{
if (sys->stdin_hndle==current)
{
	if (!activeReading)
	{
	printf("%u >> ",current->nb.handle);
	activeReading=true;
	}
int chr = fgetc(stdin);
//update buffer
	if (chr==EOF || chr=='\n')
	{
		//send to interpreter
		interpret(string,length,intr);
		//clear buffer
		length=0;
		string = realloc(string,0);
		activeReading=false;
	}else if (chr==INTERRUPT)
	{
		length=0;
		string = realloc(string,0);
		//listen for second command
		chr=getchar();
		//switch activity
	}else
	{
		//if ((length+1)%10==0)
		//	realloc(string, length+11);
		string[length]=(char)chr;
		++length;
	}
}
}

unsigned rec = current->nb.handle;
//invalidate loop
do{
if (!invalidateNode(sys,current))
	if (sys->prntSys)
		printf("Deregistration failed\n");
//implement attempt to resolve invalidation

}while (false);
printf("Node %u invalidated\n", rec);
printRegistrar(sys);
free(intr);
return 0;
};