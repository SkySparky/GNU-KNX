#ifndef KNX_LEXILE
#define KNX_LEXILE

#include "Node.h"
#include "../SDK/headers/Exchange.h"

typedef enum
{
  _raw_,//unrecognized symbol
  //general
  _data_, _exprss_,
  //unary
  _not_, _method_, _jump_, _jmpFlag_,
  //binary
  _and_, _or_, _nor_, _xor_, _xnor_, _nand_,//bi input

  _isEqu_, _gtr_, _lss_, _gtrEqu_, _lssEqu_,//bi input

  _add_, _sub_, _mult_, _div_, _mod_, _pow_, _root_,//bi input

  _set_,//bi input

  _ifElse_,//bi output (also handles ternary)
  //multi
  _list_, _switch_//list (input), switch (output)
}TkType;

/*
  Must use identities below in conjuction with IO mode (channels for input or output)
*/

#define isGeneral (x) (x==_data_ || x==_exprss_)
#define isUnary   (x) (x>=_not_ && x<=_jmpFlag_)
#define isBinary  (x) (x>=_and_ && x<=_ifElse_)
#define isMulti   (x) (x==_list_ || x==_switch_)

/*
Base token
Used for building and transversing trees
Inheriting structures extend form factor
and establish function
*/
typedef struct Token
{
  TkType type;

  struct Token * parent;
  struct Token * previous;
  struct Token * next;
}Token;

/*
Holds managed or raw data via
pointer
*/
typedef struct Data
{
  Token super;

  mBase * data;
}Data;

//Stores a sub-tree independanty from interpreter
typedef struct Expression
{
  Token super;

  Token * root;
  mMemory * scope;
}Expression;

/*
  Basic unit
  Is able to hold a single argument tree
*/
typedef struct Unary
{
  Token super;

  Token * channelA;
} Unary;

/*
  Designed for lVal rVal operations
  Handles ternary operations
*/
typedef struct Binary
{
  Token super;

  Token * channelA;
  Token * channelB;
} Binary;

typedef struct Multi
{
  Token super;

  unsigned argLength;
  Token ** args;
} Multi;


//************************************************

//interpreter instance
typedef struct tInter
{
  Node * host;
  Registrar*reg;

  Token*root;//starting root node
  Token*cRoot;//current root-level token
  Token*cursor;//current waiting token

  unsigned pOrder; //nested order
  char encapStack [256]; //encapsulation operator stack
}Interpreter;

Interpreter * makeInterpreter(Node*, Registrar*);
int freeInterpreter(Interpreter*);

//tokenizes stream
Token * analyze(char*, Interpreter*);

//delete single token
int delToken(Token*);
//delete all nodes in tree
int dissolveTree(Token*);

int addToken(Interpreter*, Token*);

Token * genDataToken(mBase*);
Token * genExprToken();
Token * genUnaryToken(TkType);
Token * genBinaryToken(TkType);
Token * genMultiToken(TkType);

#endif
