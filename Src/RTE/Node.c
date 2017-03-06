//From RTE

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <string.h>

#include "KNode.h"
#include "Processing.h"

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

void * NodeProc(void * vnode){

  Node * self = (Node *) vnode;

  char * buffer = malloc(256);

  while(self->isActive){

    printf("<%u> ", self->id);

    //reserve last two characters for NULL - simplifies operator select
    if ((buffer = fgets(buffer, 254, stdin)) == NULL) continue;

    size_t len = strlen(buffer);

    //remove endline character
    #ifdef __WINDOWS
    buffer[len-1] = 0;
    #else
    buffer[len + 1]
    #endif

    if (Tokenize(self, buffer, len) != 0) continue;

    //execute current cache
    if (self->cache->head == NULL) continue;
    ExecuteInstructions(self);
  }

  free(buffer);

  return NULL;
}
