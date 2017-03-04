#ifndef KDK_NODE
#define KDK_NODE

#include "pthread.h"

#include "Memory.h"
#include "Lang.h"
#include "Config.h"

typedef enum {PUBLIC, } PrivacyMode;

typedef struct Node{

  //Memory
  Scope * local, * global;

  //Prime ID
  unsigned id;

  //Visibility policy
  PrivacyMode privacyMode;
  unsigned long long policyGroup;

  //Token cache
  TCache * cache;

  //Relation tree
  struct Node * parent;
  struct Node ** children;

  //Node destructs when 0
  char isActive;

  //Self thread handle
  pthread_t pThread;
} Node;

typedef struct NodeRegistry{

unsigned recordCount;
unsigned * idList;
Node ** nodeList;

}NodeRegistry;

Node * BuildNode(Node * parent);

extern NodeRegistry * _nodeReg;
NodeRegistry * InitNodeReg();

#endif
