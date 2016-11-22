#ifndef KNX_TOKEN
#define KNX_TOKEN

#include "Macro.h"

typedef struct Token Token;

typedef struct Token{
  unsigned char lexeme;
  char * word;
  LUI hash;

  Token * next;
  Token * prev;
}Token;

Token * makeToken(char *);


#endif
