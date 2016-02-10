#ifndef KNX_STATE
#define KNX_STATE

#include "KNX.h"
#include <stdlib.h>
#include "Node.h"

//forward declarations
typedef struct node _node;

/*
Stores system state information
Defines macros
*/

/*
Directs IO
Stores/validates/manages all nodes
Stores master databases
*/
typedef struct state
{
_node**registrar;//node bank
unsigned registered;
unsigned sizeLevel;//grows exponentially 1=1 cell, 2=2, 3=4, 4=8, ect.. bounded by registererd
//arrSize=2^(n-1)-1


_node*stdin_hndle;//standard input handle

//system options
settings options;

database * global;//global database

//constraints
unsigned maxNodes;
unsigned maxMemory;//implement
unsigned tabSize;

char*dirPath;

}state;

state*genState();
void freeState(state *);

//register new node
_node* validateNode(state*,_node*);
//deregister node
bool invalidateNode(state*, _node*);
//print node data on record
void printRegistrar(state*);

#endif
