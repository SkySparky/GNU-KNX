#ifndef KNX_NODE
#define KNX_NODE

#include <pthread.h>

#include "Macro.h"
#include "Memory.h"

typedef struct Node Node;

typedef enum {
  _npPublic,
  _npPrivate,
  _npProtected,
  _npLegacy
} NodePolicy;

typedef struct Node{

  char*     name;         //symbolic name
  LUI       hash;
  int       id;           //index id
  int*      secureGroup;  //prime factor policy group
  int       secureMode;   //visibility policy mode

  //TODO add local, global memory
  //TODO add policy access method reference

  Node *    children;
  Node *    prevSibling;
  Node *    nextSibling;

  Node *    parent;

  //thread handle
  pthread_t handle;

  //Memory access
  Memory * global;
  Memory * local;

}Node;

//initialize new node from parent
Node * buildNode(char *, Node *);

void * nodeProc();

#endif
