#ifndef KNX_NODE
#define KNX_NODE

#include "Node.h"

void * NodeProc(void * parent);
int RegisterNode(Node * node);

extern NodeRegistry * _nodeReg;

extern unsigned * _primeList;

#endif
