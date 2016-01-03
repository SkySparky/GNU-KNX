#include "Interpreter.h"

#include <string.h>

comNode*genComeNode(comNode*parent)
{
comNode*ret = malloc(sizeof(comNode));
if (ret==NULL)
	return NULL;

ret->parent=parent;
ret->parameters=NULL;
ret->success=NULL;
ret->failure=NULL;
ret->data=genToken(NULL);

return ret;
}

void freeComNode(comNode*target)
{
if (target->data!=NULL)
	free(target->data);
if (target->parent!=NULL)
	freeComNode(target->parent);
if (target->success!=NULL)
	freeComNode(target->success);
if (target->failure!=NULL)
	freeComNode(target->failure);
free(target);
}

interpreter*genInterpreter(_state_ * st,_node_ * nd)
{
interpreter*ret = (interpreter*) malloc(sizeof(interpreter));
if (ret==NULL)
	return NULL;

ret->st=st;
ret->nd=nd;
ret->pending=false;
ret->litOp=0;
ret->listOp=0;
ret->blockOp=0;

ret->buffSize=0;
ret->buffer=malloc(0);

return ret;
}


comTree*genComTree()
{
comTree*ret = malloc(sizeof(comTree));
if (ret==NULL)
	return NULL;
ret->root = (comNode**) malloc(0);
ret->level=0;

return ret;
}

void clearComTree(comTree*target)
{
//clear branches
while(--target->level>=0)
	freeComNode(target->root[target->level]);
realloc(target->root, 0);
}

void freeComTree(comTree*target)
{
if (target==NULL)
	return;
//free branches
clearComTree(target);
//delete self
free(target->root);
free(target);
}

//converts node into executable statement
byteSequence*createCommand(comNode*target)
{

return NULL;
}


//identify symbolic identifiers
token* identify(char*string, unsigned length, interpreter*intr, token*tail)
{
token*curr=genToken(tail);
tail=curr;




return tail;
}

void tokenize(char* string,unsigned length,interpreter*intr)
{
unsigned lIndex=0;

//0=normal, 1=string, 2=comment
unsigned readMode=0;
token*head=genToken(NULL);
token*tail=NULL;

for (unsigned x=0; x<=length; ++x)
{
//ending value
	if (x==length)
	{
		if (lIndex==length)
			break;
		if (readMode==1)
		{
			token*curr=genToken(tail);
			tail=curr;
			
			tail->raw=true;
			tail->type=_mStr;
			tail->data=malloc((x-lIndex));
			strncpy(tail->data,string+lIndex, lIndex-x);
			((char*)tail->data)[x-lIndex]=(char)0;
			break;
		}
	}
}

}

void interpret(char* string,unsigned length,interpreter*intr)
{
//ensure string size
if (length==0)
	length=strlen(string);
if (length==0)
	return;

if (intr->st->prntSys==true)
	printf("\t\t%.*s\n", length, string);
	
//determine whether or not to continue waiting
intr->pending=!intr->litOp && !intr->listOp && !intr->blockOp? false: true;
}