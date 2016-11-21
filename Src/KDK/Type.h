#ifndef KDK_TYPE
#define KDK_TYPE

#include "Structures.h"

#include <pthread.h>

/*
Defines core types for use in the core engine
*/

typedef struct KeyPair{
  LUI * key;
  void * value;

  int type;
  int size;
}KeyPair;

typedef struct NodeHandle{

  pthread_t handle;
}NodeHandle;

#endif
