#include "Interpreter.h"
#include <stdlib.h>
#include "KNX.h"
#include "Node.h"

node*nodeGen()
{
node*ret = (node*) malloc(sizeof(node));
//construct super class
if (!setupBaseNode(&ret->nb))
	printf("Fail\n");
return ret;
};

int nodeProc(state*sys, node*parent, char*cmd)
{
//validate node
node*current=validateNode(sys,parent);
if (sys->options.prntSys)
{
	if (current!=NULL)
		printf("Node %u registered\n",current->nb.handle);
	else
	{
		printf("Registration failed\n");
		return -1;
	}
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
unsigned length = 0, maxLength=10;
char * string = malloc (10);
string[0]='\0';

printf("%u\n",current->nb.active);
while (current->nb.active)
{
if (sys->stdin_hndle==current)
{
	if (!activeReading)
	{
	printf("@%u >> ",current->nb.handle);
	activeReading=true;
	if (intr->st->options.tabAssist)
		for (unsigned x=0; x<intr->blockOp; ++x)
			printf("   ");
	}
int chr = fgetc(stdin);
//update buffer
	if (chr==EOF || chr=='\n')
	{
		//send to interpreter
		interpret(string,length,intr);
		//clear buffer
		length=0;
		if (maxLength!=10)
			string=realloc(string, 10);
		maxLength=10;
		memset(string,0,10);
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
		if (length+1 == maxLength)//adjust allocated size
			{
			char*tmpbuff=realloc(string, length*2);
			maxLength*=2;
			if (tmpbuff!=NULL)
				string=tmpbuff;
			else
				prntError("System Error: std-io terminal buffer failure\n",-1,sys->options);
			}
		string[length]=(char)chr;
		string[length+1]='\0';
		++length;
	}
}
}

unsigned rec = current->nb.handle;
//invalidate loop
do{
if (!invalidateNode(sys,current))
	if (sys->options.prntSys)
		printf("Deregistration failed\n");
//implement attempt to resolve invalidation

}while (false);
printf("Node %u invalidated\n", rec);
printRegistrar(sys);
free(intr);
return 0;
};
