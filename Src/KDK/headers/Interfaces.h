#ifndef KDK_INTERFACE
#define KDK_INTERFACE

#include "Node.h"
#include "Lang.h"

void * (*_nodeProc)(void*parent);//return node specific return code
int (*_registerNode)(Node*node);//return non-0 if registration failure

void (*_KFunction)(Token*stream, Node*node);

#endif
