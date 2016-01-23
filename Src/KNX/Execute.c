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

token*recExecute(interpreter*intr, token*start, token**_rEnd)//_rEnd sets calling functions address to endpoint of heirarchy
{
  //if undefined token found, attempt to re-identify: data type string
token * trash = NULL;//link dead tokens for deletion

if (start==NULL)
  return NULL;

  token * current = start;

  while (current!=NULL)
  {
    //detect and collapse heirarchies
    if (_isOpenEncap(current->type))
    {
      if (current->type==_sOpParanth)
      {
        token*rep = recExecute(intr, current->next, _rEnd);
        isolate(current, *_rEnd);//cut out passed section
        current=current->prev;
        *_rEnd=(*_rEnd)->next;
        //delete heirarchy tokens
        free(current->next);
        free((*_rEnd)->prev);

        //determine whether to splice, or use as parameters
        if (current->prev==NULL)
          splice(current, rep, *_rEnd);
        else if (!_isActable(current->prev->type))
          splice(current, rep, *_rEnd);
        else
        {
          //call function from database

          //splice return value
          splice(current, rep, *_rEnd);
        }
      }
      else if (current->type==_sOpBrack)
      {
        token*rep = recExecute(intr, current->next, _rEnd);
      }
      else if (current->type==_sOpBrace)
      {
        token*rep = recExecute(intr, current->next, _rEnd);
      }
    }
    else if (_isCloseEncap(current->type))
    {
      *_rEnd=current;
      break;
    }
    current=current->next;
  }

  token * ret = NULL;

  //delete uneeded tokens
  freeStrand(trash);

  return ret;
}

void execute(interpreter* intr)
{

if (intr->st->options.prntDbg)
	prntTokens(intr->head);

token * dummy = NULL;
//free tokens
freeStrand(recExecute(intr,intr->head, &dummy));

}
