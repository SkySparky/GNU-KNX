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

  ret->type=tdNA;
  ret->next=0;
  ret->parent=0;

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

return 0;
}

//form factor specific appends
int appendUnary()
{

  return 0;
}

int appendBinary()
{
  return 0;
}

int appendTernary()
{

  return 0;
}

int appendPoly()
{
  return 0;
}

int appendData()
{
  return 0;
}

//use intr.pOrder to track current execution path
//tkn is node to add
//returns reference to current node
void appendTree(Token*input, Interpreter * intr)
{
  //should never happen
  //TODO throw warning/error
  if (input==0)
    return;

  Token * ret = 0;

  //if root node is null, assign tkn as root
  if (intr->root==0)
  {
    intr->root=input;
    intr->current=input;
    return;
  }



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

  for (size_t x=0; x<=len; ++x)
  {
    //end of stream jumps
    if (x==len)
    {

    }

    switch(input[x])
    {
      //whitespace delimeters
      case ' ':
      case '\t':
      if (Index==x)
      {
        ++x;
      }else
      {
        appendTree(identify(input, x, Index, intr), intr);
        x=Index+1;
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
