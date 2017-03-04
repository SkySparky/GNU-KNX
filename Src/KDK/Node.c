//From KDK

#include <stdlib.h>
#include <stdio.h>

#include "Node.h"
#include "Config.h"

struct Config * _config;
struct NodeRegistry * _nodeReg;

NodeRegistry * InitNodeReg(){
  _nodeReg = malloc(sizeof(NodeRegistry));

  _nodeReg->recordCount = 0;

  _nodeReg->idList = malloc(sizeof(unsigned) * _config->_maxNodes);
  _nodeReg->nodeList = malloc(sizeof(Node *));

  return _nodeReg;
}

Node * BuildNode(Node * parent){
  Node * node = malloc(sizeof(Node));

  if (parent == NULL){
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
  node->isActive = 1;
  node->pThread = NULL;

  node->cache = malloc(sizeof(TCache));
  node->cache->nestLevel = 0;
  node->cache->nestType = malloc(256);
  node->cache->current = NULL;
  node->cache->head = NULL;
  node->cache->pMode = _pNormal;

  return node;
}
