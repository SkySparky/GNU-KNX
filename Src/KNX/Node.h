//NOTE: Found before state.h

#ifndef KNX_NODE
#define KNX_NODE

#include "../KNX_SDK/KNX_SDK.h"
#include "State.h"

//forward declarations
typedef struct state _state;

/*
Stores node instance state information

A node contains a multiply linked list

*/
typedef struct node
{
baseNode nb;
} node;

node*nodeGen();

//Node message loop
//parent, command, global databases
int nodeProc(_state*,node*parent, char*cmd);

#endif