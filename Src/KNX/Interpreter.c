#include "Interpreter.h"

interpreter*genInterpreter(_state_ * st,_node_ * nd)
{
interpreter*ret = (interpreter*) malloc(sizeof(interpreter));
if (ret==NULL)
	return NULL;

ret->st=st;
ret->nd=nd;

return ret;
}

void interpret(char* string,unsigned length,interpreter*intr)
{
intr->nd->nb.active=false;
}