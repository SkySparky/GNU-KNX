#ifndef KNX_NODE
#define KNX_NODE

#include "Macro.h"

typedef struct Node Node;

typedef struct Node{

  LUI       id;           //index id
  LUI       secureGroup;  //prime factor policy group
  unsigned  secureMode;   //visibility policy mode

  //TODO add local, global memory
  //TODO add policy access method reference

  Node * children;
  Node * prevSibling;
  Node * nextSibling;

  Node * parent;

}Node;

//initialize new node from parent
Node * buildNode(Node *);

#endif
