/*
Memory.c

Defines memory type factories and commong operations
*/

#include <stdlib.h>

#include "headers/Memory.h"

mBase * makeBase()
{
  mBase * ret = malloc(sizeof(mBase));
  if (ret==NULL)
    return NULL;

  ret->hash=0;
  ret->type=mNA;
  ret->lock=0;

  return ret;
}

mInt * makeInt()
{
  mInt * ret = malloc(sizeof(mInt));
  if (ret==NULL)
    return NULL;
  ret->base=makeBase();
  if (ret->base==NULL)
  {
    free(ret);
    return NULL;
  }

  ret->value=0;

  return ret;
}

mUInt * makeUInt()
{
  mUInt * ret = malloc(sizeof(mUInt));
  if (ret==NULL)
    return NULL;
  ret->base=makeBase();
  if (ret->base==NULL)
  {
    free(ret);
    return NULL;
  }

  ret->value=0;

  return ret;
}

mLInt * makeLInt()
{
  mLInt * ret = malloc(sizeof(mLInt));
  if (ret==NULL)
    return NULL;
  ret->base=makeBase();
  if (ret->base==NULL)
  {
    free(ret);
    return NULL;
  }

  ret->value=0;

  return ret;
}

mULInt * makeULInt()
{
  mULInt * ret = malloc(sizeof(mULInt));
  if (ret==NULL)
    return NULL;
  ret->base=makeBase();
  if (ret->base==NULL)
  {
    free(ret);
    return NULL;
  }

  ret->value=0;

  return ret;
}

mFloat * makeFloat()
{
  mFloat * ret = malloc(sizeof(mFloat));
  if (ret==NULL)
    return NULL;
  ret->base=makeBase();
  if (ret->base==NULL)
  {
    free(ret);
    return NULL;
  }

  ret->value=0;

  return ret;
}

mDouble * makeDouble()
{
  mDouble * ret = malloc(sizeof(mDouble));
  if (ret==NULL)
    return NULL;
  ret->base=makeBase();
  if (ret->base==NULL)
  {
    free(ret);
    return NULL;
  }

  ret->value=0;

  return ret;
}

mBool * makeBool()
{
  mBool * ret = malloc(sizeof(mBool));
  if (ret==NULL)
    return NULL;
  ret->base=makeBase();
  if (ret->base==NULL)
  {
    free(ret);
    return NULL;
  }

  ret->value=0;

  return ret;
}

mChar * makeChar()
{
  mChar * ret = malloc(sizeof(mChar));
  if (ret==NULL)
    return NULL;
  ret->base=makeBase();
  if (ret->base==NULL)
  {
    free(ret);
    return NULL;
  }

  ret->value=0;

  return ret;
}

mUChar * makeUChar()
{
  mUChar * ret = malloc(sizeof(mUChar));
  if (ret==NULL)
    return NULL;
  ret->base=makeBase();
  if (ret->base==NULL)
  {
    free(ret);
    return NULL;
  }

  ret->value=0;

  return ret;
}

mWChar * makeWChar()
{
  mWChar * ret = malloc(sizeof(mWChar));
  if (ret==NULL)
    return NULL;
  ret->base=makeBase();
  if (ret->base==NULL)
  {
    free(ret);
    return NULL;
  }

  ret->value=0;

  return ret;
}

mString * makeString()
{
  mString * ret = malloc(sizeof(mString));
  if (ret==NULL)
    return NULL;
  ret->base=makeBase();
  if (ret->base==NULL)
  {
    free(ret);
    return NULL;
  }

  ret->string=malloc(0);
  ret->length=0;

  return ret;
}

mArray * makeArray()
{
  mArray * ret = malloc(sizeof(mArray));
  if (ret==NULL)
    return NULL;
  ret->base=makeBase();
  if (ret->base==NULL)
  {
    free(ret);
    return NULL;
  }

  ret->items=malloc(0);
  ret->length=0;
  ret->type=mNA;

  return ret;
}

mStruct * makeStruct()
{
  mStruct * ret = malloc(sizeof(mStruct));
  if (ret==NULL)
    return NULL;

  ret->root=NULL;

  return ret;
}

mMemory * makeMemory()
{
  mMemory * ret = malloc(sizeof(mMemory));
  if (ret==NULL)
    return NULL;

  ret->root=NULL;

  return ret;
}


mBase*memSearch(mBranch* target,HASH hash)
{
  if (target==NULL)
    return NULL;

  if (target->target->hash==hash)
    return target->target;

  //BST search
  while (1)
  {
    if (hash<target->target->hash)
    {
      if (target->left==NULL)
        return NULL;
      else
        target=target->left;
    }
    else if (hash>target->target->hash)
    {
      if (target->right==NULL)
        return NULL;
      else
        target=target->right;
    }

      if (target->target->hash==hash)
        return target->target;
  }

  return NULL;
}

int memDelete(mBase*target)
{


  return 0;
}

mBase*makeVar(char*name, mType type, void*initial)
{

  return NULL;
}
