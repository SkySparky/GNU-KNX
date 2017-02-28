#ifndef KNX_NODE
#define KNX_NODE

#include "Node.h"

int NodeProc(Node * parent);
int RegisterNode(Node * node);

extern NodeRegistry * _nodeReg;

extern unsigned * _primeList;

#endif
