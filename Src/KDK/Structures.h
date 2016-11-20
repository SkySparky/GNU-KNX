#ifndef KDK_STRUCTURE
#define KDK_STRUCTURE

/*
Defines basic structures for transversals and memory objects
*/

#include "Macro.h"
#include "MemScheme.h"

#include "Var.h"


//basic object model
typedef struct Object{
  LUI         hash;
  int         typeId;
  void     *  value;
  //Castable *  castMethods;
} Object;


#endif
