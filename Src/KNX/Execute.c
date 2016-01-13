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
  if (start==NULL)
    return NULL;

  token * current=start;
  tCode boundType=0;
  unsigned logReg=-1;//-1 (no data) 0 (false) 1 (true)
  token * strand=NULL;

  if (intr->st->options.prntDbg)
  {
    printf("Enter lvl %d : ", start->order);
    prntTokens(start);
  }

  //break up heirarchies
  while(current!=NULL){
    if (_isActable(current->type))
    {
      token * retval=NULL;
      //check for argument
      if (current->next!=NULL){
        if (_isOpenEncap(current->next->type)){//determine aggregation type
          if (current->next->type==_sOpParanth)//parameter list
          {
            token *cut2=current->next->next;
            while (cut2->next!=NULL)
              if (cut2->type==_sClParanth && cut2->order==current->order)
                break;
              else
                cut2=cut2->next;

            retval=runFunction(isolate(current->next,cut2), intr);
          }else if (current->next->type==_sOpBrack)//index
          {

          }else if (current->next->type==_sOpBrace)//body override
          {

          }else
          {

          }
        }else
        {
          token*c2=current->next->next;
          retval=isolate(current, c2);
          retval=runFunction(retval,intr);
        }
        }
    }else if (_isEncap(current->type))
    {

    }

    current=current->next;
  }

  if (intr->st->options.prntDbg)
  {
    printf("Exit lvl %d : ", start->order);
    prntTokens(start);
  }

  //process data
  token * retVal = NULL;

  //free stream memory
  freeStrand(start);

  return retVal;
}

void execute(interpreter* intr)
{

if (intr->st->options.prntDbg)
	prntTokens(intr->head);
//free tokens

freeStrand(recExecute(intr,intr->head));

}
