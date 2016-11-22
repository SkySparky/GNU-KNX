#ifndef KNX_TOKEN
#define KNX_TOKEN

#include "Macro.h"
#include "Node.h"

typedef struct Token Token;
typedef struct Node Node;

typedef struct Token{
  int lexeme;
  char * word;
  LUI hash;

  Token * next;
  Token * prev;
}Token;

Token * makeToken(char *, Node*);


#endif
