#include <stdlib.h>
#include <stdio.h>

#include "Node.h"
#include "Config.h"

struct Config * _config;
struct NodeRegistry * _nodeReg;

void InitNodeReg(Config * config, NodeRegistry * nodeReg){
  //TODO MOVE TO INDEPENDANT
  _config = config;
  _nodeReg = nodeReg;

  _nodeReg = malloc(sizeof(NodeRegistry));

  _nodeReg->idList = malloc(sizeof(unsigned) * _config->_maxNodes);
}

Node * BuildNode(Node * parent){
  Node * node = malloc(sizeof(Node));

  if (node->global == NULL){
    node->global = malloc(sizeof(Scope));
  }else{
    node->global = parent->global;
  }

  node->local = malloc(sizeof(Scope));

  node->id = 0;
  node->privacyMode = PUBLIC;
  node->cache = malloc(sizeof(TCache));
  node->parent = parent;
  node->children = malloc(sizeof(Node*));
  node->children[0]=NULL;

  return node;
}
