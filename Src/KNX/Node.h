#ifndef KNX_NODE
#define KNX_NODE

#include "../KNX_SDK/KNX_SDK.h"

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
int nodeProc(node*parent, char*cmd);

#endif