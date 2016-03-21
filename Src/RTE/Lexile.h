#ifndef KNX_LEXILE
#define KNX_LEXILE

#include "Node.h"
#include "../SDK/headers/Exchange.h"

struct tInter;
struct tToken;

//token operator types
typedef enum {
tdNA,
//unary
tJumpTag,//jump location
tJump,//jump to another node
tNot,//logical NOT
tExpression,//acts as disconnected subtree
//binary
tCond,//if else node
tLoop,//for loop
tReturn,//return node
tSet,// x = y
tAdd, tSub, tMult, tDiv, tPow, tMod, tRoot,
tLss, tGtr, tEqu, tLssEqu, tGtrEqu, tNEqu,
tAnd, tOr, tNand, tNor, tXor, tXnor,
//ternary
tTernary,
//table
tSwitch,
//poly
tMethod,
//data
tData//raw data type
}tOp;

//form factor check macros
#define isUnary(x)  (x>=tJumpTag && x<=tExpression)
#define isBinary(x) (x>=tCond && x<=tXnor)
#define isTernary(x)(x==tTernary)
#define isPoly(x)   (x==tSwitch)
#define isData(x)   (x==tData)

//token superclass
typedef struct tToken
{
  tOp type;//tOp
  struct Token * next;
  struct Token * parent;
}Token;
//sub class token
//these are used to give additional context and functionality
//to a particular token, such as additional functionality or
//storage
//Functionality defined by type, but designed by form factor

typedef struct
{
  Token * super;
  Token * expression;
}TokenUnary;

typedef struct
{
  Token * super;
  Token * L;
  Token * R;
}TokenBinary;

typedef struct
{
  Token * super;

  Token * expression;
  Token * L;
  Token * R;
}TokenTernary;

typedef struct
{
  Token * super;

  Token ** lookup;
  Token ** channel;
}TokenTabel;

typedef struct
{
  Token * super;
  Token ** input;
}TokenPoly;

typedef struct
{
  Token * super;
  mBase * info;
}TokenData;

//interpreter instance
typedef struct tInter
{
  Node * host;
  Registrar*reg;

  Token*root;
  Token*current;

  unsigned pOrder; //nested order
  tOp encapStack [256]; //encapsulation operator stack
}Interpreter;

Interpreter * makeInterpreter(Node*, Registrar*);
int freeInterpreter(Interpreter*);

//tokenizes stream
int analyze(char*, Interpreter*);

#endif
