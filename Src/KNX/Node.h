#ifndef KNX_NODE
#define KNX_NODE

#include "KNX.h"

/*
Stores node instance state information

A node contains a multiply linked list

*/
typedef struct node
{

} node;


//Node message loop
//parent, command, global databases
int nodeProc(node*parent, char*cmd);

#endif