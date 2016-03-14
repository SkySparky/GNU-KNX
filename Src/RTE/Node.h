#ifndef KNX_NODE
#define KNX_NODE

#include "Settings.h"

#include "../SDK/headers/Node.h"

/*
defines node structure, methods, and node-thread procedure
*/

struct tNode;
struct tReg;

typedef struct tNode
{
  nodeBase * base;
  Settings*settings;
}Node;

typedef struct tReg
{
  Settings settings;
  Node**node_registry;
  unsigned length;
}Registrar;

Registrar * makeRegistry();
int freeRegistrar(Registrar*);
Node * registerNode(Registrar*);

//same returns as deletNode + -2: Reference not found
int deregisterNode(Node*,Registrar*);
//-1: Null input 0: Success
int deleteNode(Node*);

//node procedure
//0 Success
//1 Crash
//2 Max node limit reached
//-1 Failure to register
int NodeProc(Registrar*);

#endif
