#include "Interpreter.h"



token*runFunction(token*args,interpreter*intr)
{
  //printf("Running function\n");
  if (_isKeyword(args->type))
  {
    token * ret = invokeKeyword(args, intr);
    return ret;
  }

return NULL;
}
//[S1][S2][S3] -->> [S1]x[S2]x[S3]
token*isolate(token*cut1, token*cut2)
{
  if (cut1==NULL)
    return NULL;
  if (cut2==NULL)
    return cut1;

  token * ret = NULL;
  if (cut1->next!=cut2)
    ret = cut1->next;

  //decouple cut 2
  cut2->prev=NULL;
  //decouple cut 1
  cut1->next=NULL;

  if (ret!=NULL)
  {
    ret->prev=NULL;
    ret->next=NULL;
  }

  return ret;
}

void splice(token*LP1, token*LP2, token*LP3)
{
  if (LP1==NULL)
    return;

  if (LP2!=NULL)
  {
    LP1->next=LP2;
    LP2->prev=LP1;
    if (LP3!=NULL)
      LP1=getTail(LP2);
    else return;
  }

  if (LP3!=NULL)
  {
    LP1->next=LP3;
    LP3->prev=LP1;
  }
}

token*recExecute(interpreter*intr, token*start, token**_rEnd)//_rEnd sets calling functions address to endpoint of heirarchy
{
  //if undefined token found, attempt to re-identify: data type string
token * trash = NULL;//link dead tokens for deletion

if (start==NULL)
  return NULL;

  token * current = start;

  while (current!=NULL)
  {
    //Support for single non-nested execution only for now
    if (_isActable(current->type))
    {
      token*rval = runFunction(current,intr);
      printf("***");
      trash=start;
      start=rval;
      break;
    }

    current=current->prev;
  }

  token * ret = NULL;

  //perform body calculations

  //delete uneeded tokens
  printf(">");
  freeStrand(trash);
  printf("<");
  return ret;
}

void execute(interpreter* intr)
{

if (intr->st->options.prntDbg)
	prntTokens(intr->head);

token * dummy = NULL;
//free tokens
freeStrand(recExecute(intr,intr->current/*tail*/, &dummy));
}
