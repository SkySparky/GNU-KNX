#ifndef KNX_LEXILE
#define KNX_LEXILE

#include "Node.h"
#include "../SDK/headers/Exchange.h"

struct tInter;
struct tToken;

//token operator types
typedef enum {
tData,//raw data type
tCond,//if else node
tLoop,//for loop
tReturn,//return node

}tOp;

//token superclass
typedef struct tToken
{
  tOp type;//tOp
  struct Token * next;
}Token;
//sub class token
//these are used to give additional context and functionality
//to a particular token, such as additional functionality or
//storage

//controls if/else conditional execution
typedef struct
{
  Token * super;//type, TRUE control
  Token * expression;//TRUE/FALSE input expression
  Token * elseControl;//false, ELSE control
}TokenIf;

//allows a temporary variable, continue expression, and post-cycle expression
typedef struct
{
  Token * super;
  Token * initial;//initial local
  Token * expression;//expression to evaluate to continue cycle
  Token * postOp;//operation to occur after cyle (probably local_init increment/decrement)
  mBase * local_init;//local instantiation
}TokenLoop;

//specifies somewhere in current executation path to jump to
//(only works in current buffer frame)
typedef struct
{
  Token * super;
} TokenJump;

//variable or literal references (non function)
typedef struct
{
  Token * super;
  mBase * data;
}TokenData;

//functional method. Both scripted and modular methods
typedef struct
{
  Token * super;
  void * reference;//reference to method
  Token * parameters;
  char reference;//0=NA 1=scripted, 2=modular
}TokenMethod;

//Binary Operators
typedef struct
{
  Token * super;
  char operation;//0=NA 1=+ 2=- 3=* 4=/ 5=% 6=^ 7=root
  Token * lParam;
  Token * rParam;
}TokenLR;

//unary expressions
typedef struct
{
  Token * super;
  char operation;
  Token * expression;//expression to operate
}TokenU;

//interpreter instance
typedef struct tInter
{
  Node * host;
  Registrar*reg;

  Token*root;
  Token*current;

  //nested order
  unsigned pOrder;
}Interpreter;

Interpreter * makeInterpreter(Node*, Registrar*);
int freeInterpreter(Interpreter*);

//tokenizes stream
int analyze(char*, Interpreter*);

#endif
