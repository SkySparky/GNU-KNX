#ifndef KDK_NODE
#define KDK_NODE

#include "Memory.h"
#include "Lang.h"
#include "Config.h"

typedef enum {PUBLIC, } PrivacyMode;

typedef struct Node{

  Scope * local, * global;

  unsigned id;

  PrivacyMode privacyMode;
  unsigned long long policyGroup;

  TCache * cache;

  struct Node * parent;
  struct Node ** children;

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
