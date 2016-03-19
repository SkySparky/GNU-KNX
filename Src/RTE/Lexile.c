#include "Lexile.h"
#include <string.h>

Interpreter * makeInterpreter(Node*node, Registrar*reg)
{
  Interpreter * ret = malloc(sizeof(Interpreter));

  if (ret==0)
    return 0;

  ret->host=node;
  ret->reg=reg;

  ret->root=0;
  ret->current=0;

  return ret;
}

int freeInterpreter(Interpreter*intr)
{

  if (intr->root!=0)//free any existing structures
    {
      free(intr->root);//TODO replace with tree-deconstruction
    }

  return 0;
}

Token * genToken(void*data, unsigned type)
{
  Token * ret = malloc(sizeof(Token));
  if (ret==0)
    return 0;

  ret->type=type;
  ret->data=data;
  ret->params=0;
  ret->success=0;
  ret->failure=0;

  return ret;
}

Token * identify(char*raw, unsigned sIndex, unsigned eIndex, Interpreter*intr)
{
  if (sIndex>eIndex)
    return 0;

  Token * token = 0;
  char * input = 0;

  input = malloc((eIndex-sIndex)+1);
  strncpy(input, raw+sIndex, eIndex-sIndex);

  //determine if literal


  free (input);
  return token;
}
//querry defined memory scope
Token * queryMemory(char*raw, unsigned sIndex, unsigned eIndex, Interpreter*intr, Node*node, char searchGlobal)
{

}

//use intr.pOrder to track current execution path
void appendTree(Token*tkn, Interpreter * intr)
{

}

int analyze(char*input, Interpreter*intr)
{
  if (input==0)
    return 0;

  //0=normal 1=char 2=string 3=comment 4=reference(variable)
  char readMode=0;

  size_t len = strlen(input);

  //point of last cutoff
  size_t Index=0;

  for (size_t x=len-1; x>=0; ++x)
  {
    //end of stream jumps
    if (x==0)
    {

    }

    switch(input[x])
    {
      //whitespace delimeters
      case ' ':
      case '\t':
      if (Index==x)
      {
        --x;
      }else
      {
        appenTree(identify(input, x, Index, intr), intr);
        x=Index-1;
      }
      break;

      //encapsulation

      //data

      default:

      break;
    }
  }

  return 0;
}
