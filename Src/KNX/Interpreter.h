#ifndef KNX_INTERPRETER
#define KNX_INTERPRETER

#include "State.h"
#include "Node.h"

#include "KNX.h"

#include <string.h>

typedef struct state _state_;
typedef struct node _node_;
typedef struct comNode _comNode_;

/*
single command node
holds parameters, returns true or false
*/
typedef struct comNode
{
token*data;
_comNode_*parent;
_comNode_*parameters;
_comNode_*success;
_comNode_*failure;
}comNode;

comNode*genComNode(comNode*parent);
void freeComNode(comNode*);

/*
ternary execution tree
controls the execution of commands
and processes parameters
*/
typedef struct
{
comNode**root;

unsigned level;//number of root nodes

}comTree;

comTree*genComTree();
void freeComTree(comTree*);
void clearComTree(comTree*);
byteSequence*createCommand(comNode*);

typedef struct
{
_state_*st;
_node_*nd;

comTree cTree;

//states
bool pending;
bool litOp;//"
int listOp;//()
int blockOp;//{}

//buffers
char*buffer;//block buffer
unsigned buffSize;

}interpreter;

interpreter*genInterpreter(_state_ *,_node_ *);

//raw input, input length, system state, current node, interpreter instance
void interpret(char*,unsigned,interpreter*);

#endif