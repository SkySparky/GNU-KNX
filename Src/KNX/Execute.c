#include "Interpreter.h"



token*runFunction(token*args,interpreter*intr)
{


return NULL;
}
//[S1][S2][S3] -->> [S1]x[S2]x[S3]
token*isolate(token*cut1, token*cut2)
{
  if (cut1==NULL)
    return NULL;
  if (cut2==NULL)
    return cut1;

  token * ret = cut1->next;
  if (cut2->prev==NULL)
    return NULL;
  //decouple cut 2
  cut2->prev->next=NULL;
  cut2->prev=NULL;

  //decouple cut 1
  cut1->next=NULL;
  ret->prev=NULL;

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

token*recExecute(interpreter*intr, token*start)
{
 
  return NULL;
}

void execute(interpreter* intr)
{

if (intr->st->options.prntDbg)
	prntTokens(intr->head);
	

	
//free tokens
freeStrand(recExecute(intr,intr->head));

}
