#include <stdlib.h>

#include "Structures.h"
#include "Util.h"

extern Object * BuildObject(char * name){

  Object * ret = malloc(sizeof(Object));

  if (ret == NULL) return NULL;

  ret->hash = _FNV_1A(name);

  return ret;
}

extern ObjectLeaf * BuildObjectLeaf(Object * trgt){
  ObjectLeaf * ret = malloc (sizeof(ObjectLeaf));

  if (ret == NULL) return NULL;

  ret->target = trgt;
  ret->left = NULL;
  ret->right = NULL;

  return ret;
}

extern ObjectTree * BuildObjectTree(MemScheme scheme, ObjectLeaf * root){
  ObjectTree * ret = malloc(sizeof(ObjectTree));

  if (ret == NULL) return NULL;

  ret->memScheme = scheme;
  ret->root = root;

  return ret;
}
