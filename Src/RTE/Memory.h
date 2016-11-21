#ifndef KNX_MEMORY
#define KNX_MEMORY

#include "Structures.h"

/*
Define scoped memory structure for nodess
*/

typedef enum {
_list,      //Standard linked list
_binary,    //Binary tree
_splay,     //Binary splay tree
_repeat     //Last-use-first linked list
} MemScheme;

typedef enum{
_public,
_private,
_protected,
_legacy
}VisPolicy;

typedef struct MLeaf MLeaf;

typedef struct MLeaf{
  Object * var;
  MLeaf * lLeaf;
  MLeaf * rLeaf;
}MLeaf;

typedef struct Memory{
  MemScheme scheme;
  MLeaf * root;

  //assigned to methods based on memscheme setting
  Object * (*getObject)(LUI);
}Memory;

#endif
