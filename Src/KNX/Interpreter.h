#ifndef KNX_INTERPRETER
#define KNX_INTERPRETER

#include "State.h"
#include "Node.h"

typedef struct state _state_;
typedef struct node _node_;

//caches code blocks for execution
typedef struct
{

}cacheBlock;

typedef struct
{
_state_*st;
_node_*nd;

}interpreter;

interpreter*genInterpreter(_state_ *,_node_ *);

//raw input, input length, system state, current node, interpreter instance
void interpret(char*,unsigned,interpreter*);

#endif