//From RTE

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "KNode.h"

struct NodeRegistry * _nodeReg;
struct Config * _config;
unsigned * _primeList;

int RegisterNode(Node * node){

  if (_nodeReg->recordCount >= _config->_maxNodes){
    //TODO throw system error
    return -1;
  }

  //establish root node
  if (_nodeReg->recordCount == 0){
    node->id = 1;
  } else {
    node->id = UINT_MAX;

    int isCollision = 0;

    for (unsigned i=0; i < _config->_maxNodes; ++i){
      for (unsigned j=0; j < _nodeReg->recordCount; ++j){
        isCollision = _primeList[i] == _nodeReg->nodeList[j]->id;
        if (isCollision) break;
      }
      if (!isCollision){
        node->id = _primeList[i];
        break;
      }
    }
  }
  _nodeReg->nodeList = realloc(_nodeReg->nodeList, ++_nodeReg->recordCount * sizeof(Node*));
  _nodeReg->nodeList[_nodeReg->recordCount-1] = node;
  printf("Node %u (%u) registered\r\n", node->id, _nodeReg->recordCount);

  return 0;
}

int NodeProc(Node * node){

  return 0;
}
