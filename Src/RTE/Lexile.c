#include "Lexile.h"
#include <string.h>
#include <stdio.h>


//**********************Factories
Interpreter * makeInterpreter(Node * node, Registrar * reg)
{
  Interpreter * intr = malloc(sizeof(Interpreter));

  if (intr==NULL)
    return NULL;

  intr->host=node;
  intr->reg=reg;

  intr->root=NULL;
  intr->cRoot=NULL;
  intr->cursor=NULL;

  intr->pOrder=0;

  return intr;
}

int freeInterpreter(Interpreter * intr)
{
  dissolveTree(intr->root);
  free(intr);
  return 0;
}


//**********************Analysis
Token * parseExpression(char*string, unsigned sIndex, unsigned eIndex, Interpreter*intr)
{

  return NULL;
}

Token * analyze(char*string, Interpreter * intr)
{


  return NULL;
}

int delToken(Token * tk)
{

  return 0;
}

int dissolveTree(Token * tree)
{

  return 0;
}
