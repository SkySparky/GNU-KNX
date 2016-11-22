#ifndef KDK_TYPE
#define KDK_TYPE

#include "Structures.h"

#include <pthread.h>

/*
Defines core types for use in the core engine
*/

typedef enum{
  _eVoid,
  _eInt,
  _eUInt,
  _eLong,
  _eULong,
  _eReal,
  _eChar,
  _eUChar,
  _eWChar,
  _eString,
  _eWString,
  _eBit,
  _eClass,
  _eDynamic,
  _eFunction,
  _eArray,
  _eCol,
  _eKeypair,
  _eFile,
  _eStream,
  _eNode
}BasicTypeId;

typedef struct KeyPair{
  LUI * key;
  void * value;

  int type;
  int size;
}KeyPair;

typedef struct NodeHandle{
  int nodeId;
  pthread_t handle;

  //node functions
}NodeHandle;

#endif
