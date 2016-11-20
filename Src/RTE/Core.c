#include "Core.h"
#include "KDK.h"
#include "Registry.h"

#include <stdlib.h>
#include <string.h>

void initializeCore(){
  Core = malloc(sizeof(_core));
}

void initializeNodeRegistry(){
  NodeReg = malloc(sizeof(_nodeReg));
  NodeReg->idList = calloc(Config->maxNodes, sizeof(bool));
}

void initializeConfig(){
  Config = malloc(sizeof(_config));

  //setup initial values
  Config->maxNodes = 128;

  size_t vLen = strlen(RTEVERSION);
  Config->rteVersion = (char*) malloc(vLen);
  strncpy(Config->rteVersion, RTEVERSION, vLen);

  vLen = strlen(getKDKVersion());
  Config->kdkVersion = (char*) malloc(vLen);
  strncpy(Config->kdkVersion, getKDKVersion(), vLen);
}

void intitializeTypeRegistry(){
  //populate registration table with basic types
  registerBasicTypes();
}

void initializeInterfaces(){
  int (*registerObject)() = &_registerObject;
  registerObject();
}

bool registerNode(Node * node){

  if (!node) return false;

  for(int i=0; i<=Config->maxNodes; ++i){
    if (!NodeReg->idList[i]){
      NodeReg->idList[i]=true;
      node->id=i;
      return true;
    }
  }

  //register permissions for root
  if (node->id == 0){
    NodeReg->root = node;
    Core->oStreamOwner = node;
    Core->iStreamOwner = node;
  }

  //TODO add error

  return true;
}
