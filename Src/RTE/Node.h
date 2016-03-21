#ifndef KNX_NODE
#define KNX_NODE

#include "Settings.h"

#include "../SDK/headers/Node.h"
#include "../SDK/headers/Memory.h"

/*
defines node structure, methods, and node-thread procedure
*/

struct tNode;
struct tReg;

typedef struct tNode
{
  //settings and references
  nodeBase * base;
  Settings*settings;

  //memory space
  mMemory * global;
  mMemory * local;
}Node;

//only allocate one instance at beginning of program
typedef struct tReg
{
  Settings settings;

  Node**node_registry;
  unsigned node_length;

  mBase*modvar_registry;
  unsigned modvar_length;
}Registrar;

Registrar * makeRegistry();
int freeRegistrar(Registrar*);
Node * registerNode(Registrar*, mMemory*);

//same returns as deletNode + -2: Reference not found
int deregisterNode(Node*,Registrar*);
//-1: Null input 0: Success
int deleteNode(Node*);

//node procedure
//0 Success
//1 Crash
//2 Max node limit reached
//-1 Failure to register
int NodeProc(Registrar*, mMemory*);

#endif
