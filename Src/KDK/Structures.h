#ifndef KDK_STRUCTURE
#define KDK_STRUCTURE

#include "Macro.h"
#include "MemScheme.h"
#include "ObjectSearch.h"

typedef struct Object Object;
typedef struct ObjectTree ObjectTree;
typedef struct ObjectLeaf ObjectLeaf;

typedef struct Object{
  LUI hash;

  ObjectTree * members;

} Object;

typedef struct ObjectLeaf{
  ObjectLeaf * left;
  ObjectLeaf * right;

  Object * target;

} ObjectLeaf;

typedef struct ObjectTree{
  MemScheme memScheme;
  ObjectLeaf * root;
} ObjectTree;

extern Object * BuildObject(char * name);
extern ObjectLeaf * BuildObjectLeaf(Object * trgt);
extern ObjectTree * BuildObjectTree(MemScheme scheme, ObjectLeaf * root);

#endif
