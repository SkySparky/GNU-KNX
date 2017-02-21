#ifndef KDK_NODE
#define KDK_NODE

#include "Memory.h"
#include "Lang.h"
#include "Config.h"

typedef enum {PUBLIC, } PrivacyMode;

typedef struct NodeRegistry{

unsigned * idList;


}NodeRegistry;

extern NodeRegistry * _nodeReg;

void InitNodeReg(Config *, NodeRegistry *);

typedef struct Node{

  Scope * local, * global;

  unsigned id;

  PrivacyMode privacyMode;
  unsigned long long policyGroup;

  TCache * cache;

  struct Node * parent;
  struct Node ** children;

} Node;

Node * BuildNode(Node * parent);

int (*_nodeProc)(Node*parent);

#endif
