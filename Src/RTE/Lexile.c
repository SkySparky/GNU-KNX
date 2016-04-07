#include "Lexile.h"
#include "Keyword.h"
#include "../SDK/headers/Error.h"

#include <string.h>
#include <stdio.h>

//returns false if x is special character
#define isSpc(x)  (!((x>='a' && x<='z') || (x>='A' && x<='Z') || (x=='.')))

//read modes
typedef enum {_normal, _string, _char, _comment}readmode;
typedef enum {_none, _ref/*$*/, }spChar;

//**********************Tokens
int addToken(Interpreter * intr, Token * tk)
{

  return 0;
}

Token * genDataToken(mBase*data)
{
  Data * ret = malloc(sizeof(Data));
  ret->super.type=_data_;
  ret->super.parent=NULL;
  ret->super.previous=NULL;
  ret->super.next=NULL;
  ret->data=data;
  return &ret->super;
}

Token * genExprToken()
{
  Expression * ret = malloc(sizeof(Expression));
  ret->super.type=_exprss_;
  ret->super.parent=NULL;
  ret->super.previous=NULL;
  ret->super.next=NULL;
  ret->root=NULL;
  ret->scope=malloc(sizeof(mMemory));
  return &ret->super;
}

Token * genUnaryToken(TkType type)
{
  Unary * ret = malloc(sizeof(Unary));
  ret->super.type=type;
  ret->super.parent=NULL;
  ret->super.previous=NULL;
  ret->super.next=NULL;
  ret->channelA=NULL;
  return &ret->super;
}

Token * genBinaryToken(TkType type)
{
  Binary * ret = malloc(sizeof(Binary));
  ret->super.type=type;
  ret->super.parent=NULL;
  ret->super.previous=NULL;
  ret->super.next=NULL;
  ret->channelA=NULL;
  ret->channelB=NULL;
  return &ret->super;
}

Token * genMultiToken(TkType type)
{
  Multi * ret = malloc(sizeof(Multi));
  ret->super.type=type;
  ret->super.parent=NULL;
  ret->super.previous=NULL;
  ret->super.next=NULL;
  ret->args=NULL;
  ret->argLength=0;
  return &ret->super;
}

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

void identify(unsigned sDex, unsigned eDex, char * string, Interpreter * intr, spChar*sc)
{
  char str [64] = {0};
  strncpy(str, string+sDex, (eDex-sDex));
  printf("%s : %d : %u\n", str, *sc, intr->pOrder);

  printf("KW: %s %d \n",str , isKeyword(str, intr));

  *sc=0;
}

//**********************Analysis
Token * parseExpression(char*string, unsigned sIndex, unsigned eIndex, Interpreter*intr)
{

  return NULL;
}

Token * analyze(char*string, Interpreter * intr)
{
  readmode rm=_normal;
  spChar sc=0;

  unsigned len=(unsigned) strlen(string);
  unsigned index=0;
  //normal parsing mode
  for (unsigned x=0; x<len; ++x)
  {
    if (rm==_normal)
    {
      if (isSpc(string[x]))
      {
        if (index<x)
          {
            identify(index, x, string, intr, &sc);
          }
        switch(string[x])
        {
          case '$':
          sc=_ref;
          break;

          //encapse
          case '\'':
          rm=_char;
          break;
          case '\"':
          rm=_string;
          break;
          case '[':
          case '{':
          case '(':
          intr->encapStack[intr->pOrder++]=string[x];
          break;
          case ']':
          case '}':
          case ')':
          if (intr->pOrder==0)
          {
            char msg[2]={0};
            msg[0]=string[x];
            prntErr(W_NEG_ENCAP, msg, intr->reg->settings.prntWrn);
          }
          else
            intr->encapStack[--intr->pOrder]=string[x];
          break;

          //logic
          case '=':
            if (string[x+1]=='=')
          break;
        }
        index=x+1;
      } else if (x+1==len)
      {
        identify(index, len, string, intr, &sc);
      }
    }else if (rm==_string)
    {

    }else if (rm==_char)
    {

    }else if (rm==_comment)
    {

    }
  }


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
