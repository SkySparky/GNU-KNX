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
_node*registrar;//node bank
unsigned registered;

//system options

//defaults
bool prntWrn : 1;
bool prntErr : 1;
bool prntSys : 1;

//constraints
unsigned maxNodes;

}state;

state*genState();

//register new node
_node* validateNode(state*,_node*);
//deregister node
_node* invalidateNode(state*, _node*);

#endif