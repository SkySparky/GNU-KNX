#include "Interpreter.h"

#include "../KNX_SDK/Debug.h"

#include <string.h>


#define isOp(c)(\
((c<'0' || c>'9') && (c<'a' || c>'z') && (c<'A' && c>'Z'))\
&& c!='_')


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


token * addToken(token*parent, void*data, tCode type, bool raw)
{

if (parent==NULL)
{
	parent=genToken(parent);
	parent->data=data;
	parent->type=type;
	parent->raw=raw;
	return parent;
}

token * curr = genToken(parent);
curr->data=data;
curr->type=type;
curr->raw=raw;
curr->previous=parent;
parent->next=curr;

return curr;
}

//identify symbolic identifiers
token* identify(char*string, unsigned length, interpreter*intr, token*tail)
{
void*data=NULL;
tCode type=0;
bool raw=true;

return addToken(tail, data, type, raw);
}

token * tokenize(char* string,unsigned length,interpreter*intr)
{
unsigned lIndex=0;

//0=normal, 1=string, 2=comment
unsigned readMode=0;
token*current=NULL;

for (unsigned x=0; x<=length; ++x)
{
//ending value
	if (x==length)
	{
		if (lIndex==length)
			break;
		if (readMode==2)
			break;
		if (readMode==1)
		{
			char*buff = malloc((x-lIndex)+1);
			strncpy(buff, string, x-lIndex);
			buff[x-lIndex]='\0';
			current=addToken(current,(void*) buff, _mStr, true);
			break;
		}
		else
		{
			current = identify(string+lIndex, x-lIndex, intr, current);
			break;
		}
	}
	
	if (isOp(string[x]))
		switch (string[x])
		{
		case ' ':
		if (x==lIndex)
			continue;
		current = identify(string+lIndex, x-lIndex, intr, current);
		
		break;
		
		}
//
}
current=getHead(current);
prntTokens(current);

return current;
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
	
token*tokenStream=tokenize(string, length, intr);
	
//determine whether or not to continue waiting
intr->pending=!intr->litOp && !intr->listOp && !intr->blockOp? false: true;

freeToken(tokenStream);
}