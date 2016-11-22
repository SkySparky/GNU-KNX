#ifndef KNX_TOKENIZER
#define KNX_TOKENIZER

#include "Token.h"
#include "Node.h"

typedef struct Node Node;

Token * tokenize(char*, Node *);

#endif
