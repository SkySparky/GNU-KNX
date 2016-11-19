#include "Core.h"

#include <stdlib.h>

void initializeCore(){
  Core = malloc(sizeof(_core));
}

void initializeNodeRegistry(){

  NodeReg = malloc(sizeof(_nodeReg));

  NodeReg->idList = calloc(Config->maxNodes, sizeof(bool));

  //initialize root node
  Node * root = buildNode(NULL);
  registerNode(root);
}

void initializeConfig(){
  Config = malloc(sizeof(_config));

  //setup initial values
  Config->maxNodes = 128;
}


bool registerNode(Node * node){

  if (!node) return false;

  return true;
}
