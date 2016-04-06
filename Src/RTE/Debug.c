#include "Debug.h"

#include <stdio.h>

void printSToken(Token*tk)
{
  if (tk==NULL)
    printf("[NA]");
  else
    printf("[%d]", tk->type);
}

void printToken(Token*tk)
{

  //TODO add transverals
  printSToken(tk);

}
