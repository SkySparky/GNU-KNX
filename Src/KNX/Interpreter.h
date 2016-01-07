#ifndef KNX_INTERPRETER
#define KNX_INTERPRETER

#include "State.h"
#include "Node.h"

#include "KNX.h"

#include <string.h>

typedef struct state _state_;
typedef struct node _node_;

typedef struct
{
_state_*st;
_node_*nd;

//states
bool pending;
bool waitExprss;//
bool waitLn;// backslash
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
