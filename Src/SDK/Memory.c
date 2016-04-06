/*
Memory.c

Defines memory type factories and commong operations
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "headers/Memory.h"
#include "headers/Util.h"

mMemory * makeMemory()
{
  mMemory * ret = malloc(sizeof(mMemory));
  if (ret==NULL)
    return NULL;

  ret->root=NULL;

  return ret;
}

int freeMemory(mMemory * target)
{
  if (target==0)
    return -1;

  //TODO iterate through tree, deleting each reference

  free(target);
  return 0;
}

mBase*memSearch(mBranch* target,HASH hash)
{
  return NULL;
}

mBase * getMember(mMemory*mem, HASH hash)
{
  //Perform binary search to check if target is in scope
  //If found, return

  return NULL;
}

int addBranch(mMemory*mem, mBase*tgt)
{
  /*
    Add to top of tree, if DNE
  */

  if (mem==NULL || tgt==NULL)
    return 0;

  if (getMember(mem, tgt->hash)!=0)
    return -1;

  return 0;
}

int memDelete(mBase*target)
{
  //TODO delete based on target type

  return 0;
}

mBase makeBase(char * name, mType type, unsigned char lock, unsigned char raw)
{
  mBase base;
  base.hash=FNV_1A(name);
  base.type=type;
  base.lock=lock;
  base.raw=raw;

  return base;
}

mBase*makeVar(char*name, mType type, void*initial, unsigned char raw)
{
  switch(type)
  {
    case mtInt:
    {
      mInt * ret = malloc(sizeof(mInt));
      ret->value=initial==NULL?0:*(int*)initial;
      ret->base=makeBase(name, type, 0, raw);
      return &ret->base;
    }
    break;

    default:
    return NULL;
  }
  return NULL;
}

char * getMemberString(char*input, unsigned len)
{
  if (input==NULL)
    return NULL;

  if (len==0)
    len=strlen(input);

    printf("Length = %u\n", len);

  for (unsigned p=0; p<len; ++p)
  {
    if (input[p]=='.')
    {
      char * member = malloc(len-p-1);
      strncpy(member, input+p+1, len-p-1);
      input[p]=0;
      member[(len-p)-1]=0;
      return member;
    }
  }

  return NULL;
}
