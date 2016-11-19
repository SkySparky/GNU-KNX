#ifndef KDK_STRUCTURE
#define KDK_STRUCTURE

/*
Defines basic structures for transversals and memory objects
*/

#include "Macro.h"
#include "MemScheme.h"
#include "ObjectSearch.h"


//basic object model
typedef struct Object{
  LUI hash;
  unsigned typeId;
  void * value;
} Object;


#endif
