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
  if (target==NULL)
    return -1;

  //TODO iterate through tree, deleting each reference


  free(target);
  return 0;
}

mBase*memSearch(mMemory*mem ,mBranch* target,HASH hash)
{
  if (mem==NULL || target==NULL)
    return NULL;

  mBranch * curr = mem->root;

  while (true)
  {
    if (curr==NULL)
      return NULL;

    if (target->target->hash < curr->target->hash)
      curr=curr->left;
    else if (target->target->hash > curr->target->hash)
      curr=curr->right;
    else
      {
        memSplay(mem, curr);
        return curr->target;
      }
  }
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

  mBranch * newBranch = malloc (sizeof(mBranch));
  newBranch->target=tgt;
  newBranch->parent=NULL;
  newBranch->left=NULL;
  newBranch->right=NULL;

  //append to tree
  if (mem->root==NULL)
    {
      mem->root=newBranch;
      return 1;
    }
  else
  {
    mBranch * current = mem->root;
    while (true)
    {
      if (tgt->hash < current->target->hash)
      {
        if (current->left==NULL)
        {
          current->left=newBranch;
          newBranch->parent=current;
          break;
        }else
        {
          current=current->left;
          continue;
        }
      }else
      {
        if (current->right==NULL)
        {
          current->right=newBranch;
          newBranch->parent=current;
          break;
        }else
        {
          current=current->right;
          continue;
        }
      }
    }
  }

  memSplay(mem, newBranch);
  return 1;
}

int memDelete(mBase*target)
{
  //TODO delete based on target type

  return 0;
}

//TODO
int memSplay(mMemory*memory, mBranch*branch)
{

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

//creates manageable data/variable from input
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
    case mtUInt:
    {
      mUInt * ret = malloc(sizeof(mUInt));
      ret->value=initial==NULL?0:*(unsigned*)initial;
      ret->base=makeBase(name, type, 0, raw);
      return &ret->base;
    }
    break;
    case mtLint:
    {
      mLInt * ret = malloc(sizeof(mLInt));
      ret->value=initial==NULL?0:*(long*)initial;
      ret->base=makeBase(name, type, 0, raw);
      return &ret->base;
    }
    break;
    case mtULint:
    {
      mULInt * ret = malloc(sizeof(mULInt));
      ret->value=initial==NULL?0:*(unsigned long*)initial;
      ret->base=makeBase(name, type, 0, raw);
      return &ret->base;
    }
    break;
    case mtFloat:
    {
      mFloat * ret = malloc(sizeof(mFloat));
      ret->value=initial==NULL?0:*(float*)initial;
      ret->base=makeBase(name, type, 0, raw);
      return &ret->base;
    }
    break;
    case mtDouble:
    {
      mDouble * ret = malloc(sizeof(mDouble));
      ret->value=initial==NULL?0:*(double*)initial;
      ret->base=makeBase(name, type, 0, raw);
      return &ret->base;
    }
    break;
    case mtBool:
    {
      mBool * ret = malloc(sizeof(mBool));
      ret->value=initial==NULL?0:*(unsigned char*)initial;
      ret->base=makeBase(name, type, 0, raw);
      return &ret->base;
    }
    break;
    case mtChar:
    {
      mChar * ret = malloc(sizeof(mChar));
      ret->value=initial==NULL?0:*(char*)initial;
      ret->base=makeBase(name, type, 0, raw);
      return &ret->base;
    }
    break;
    case mtUChar:
    {
      mUChar * ret = malloc(sizeof(mUChar));
      ret->value=initial==NULL?0:*(unsigned char*)initial;
      ret->base=makeBase(name, type, 0, raw);
      return &ret->base;
    }
    break;
    case mtWChar:
    {
      mWChar * ret = malloc(sizeof(mWChar));
      ret->value=initial==NULL?0:*(unsigned short*)initial;
      ret->base=makeBase(name, type, 0, raw);
      return &ret->base;
    }
    break;
    case mtString:
    {
      mString * ret = malloc(sizeof(mString));
      ret->value=initial==NULL?0:(char*)initial;
      ret->base=makeBase(name, type, 0, raw);
      return &ret->base;
    }
    break;
    case mtArray:
    {
      mArray * ret = malloc(sizeof(mArray));
      ret->value=NULL;
      ret->length=0;
      ret->base=makeBase(name, type, 0, raw);
      return &ret->base;
    }
    break;
    case mtStruct:
    {
      mStruct * ret = malloc(sizeof(mStruct));
      ret->value=NULL;
      ret->length=0;
      ret->base=makeBase(name, type, 0, raw);
      return &ret->base;
    }
    break;
    case mtVoid:
    {
      mVoid * ret = malloc(sizeof(mVoid));
      ret->value=NULL;
      ret->type=0;
      ret->base=makeBase(name, type, 0, raw);
      return &ret->base;
    }
    break;
    default:
    printf("Data loader not implemented. Skipping.\n");
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
