#include "Node.h"
#include "Core.h"

#include <stdlib.h>

//construct a node and register it
Node * buildNode(Node * parent){
  Node * node = malloc(sizeof(Node));

  if (!node || !registerNode(node)){
    return NULL;
  }

  return node;
}
