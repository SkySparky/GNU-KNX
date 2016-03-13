#include "headers/Exchange.h"
#include "headers/Memory.h"

dInfo * makeInfo(dType type, void*data)
{
  dInfo * ret = malloc(sizeof(dInfo));
  if (ret==NULL)
    return NULL;

  ret->type=type;
  ret->data=data;

  return ret;
}

//1 input null : -1 general failure
int infoDelete(dInfo*target)
{
  if (target==NULL)
    return 1;

  //stored data, delete
  if (target->type==RawData)
  {
    int rVal = memDelete((mBase*)target->data);

    if (rVal==0)
      free(target);

    return rVal;
  }
  else
    free(target);

  return 0;
}
