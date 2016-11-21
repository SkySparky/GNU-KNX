#ifndef KDK_STRUCTURE
#define KDK_STRUCTURE

/*
Defines basic structures for transversals and memory objects
*/
#include "Interfaces.h"
#include "Macro.h"

#include "Var.h"

typedef struct Object Object;

//basic object model
typedef struct Object{
  LUI         hash;
  int         typeId;
  void     *  value;
  castable    cast;
} Object;


#endif
