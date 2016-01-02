#include "Interpreter.h"

comNode*genComeNode(comNode*parent)
{
comNode*ret = malloc(sizeof(comNode));
if (ret==NULL)
	return NULL;

ret->parent=parent;
ret->parameters=NULL;
ret->success=NULL;
ret->failure=NULL;
ret->data=genToken();

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
ret->roots = (comNode**) malloc(0);
ret->level=0;

return ret;
}

void clearComTree(comTree*target)
{
//clear branches
while(--target->level>=0)
	freeComNode(target->roots[target->level]);
realloc(target->roots, 0);
}

void freeComTree(comTree*target)
{
if (target==NULL)
	return;
//free branches
clearComTree(target);
//delete self
free(target->roots);
free(target);
}

//converts node into executable statement
byteSequence*createCommand(comNode*target)
{

return NULL;
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
	
//find and parse heirarchies
for (unsigned x=0; x<length; ++x)
	{
		if (string[x]=='\\')//preserve next item
		{
			++x;
			break;
		}
		else if (string[x]=='\"')
			intr->litOp = !intr->litOp;
		else if (string[x]=='(')
			++intr->listOp;
		else if (string[x]==')')
			--intr->listOp;
		else if (string[x]=='{')
			++intr->blockOp;
		else if (string[x]=='}')
			--intr->blockOp;
	}
//determine whether or not to continue waiting
intr->pending=!intr->litOp && !intr->listOp && !intr->blockOp? false: true;
}