#ifndef KNX_STATE
#define KNX_STATE

#include "Node.h"

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
node*registrar;//node bank
unsigned registered;

}state;

//register new node
bool validateNode(state*);
//deregister node
bool invalidateNode(state*);

#endif