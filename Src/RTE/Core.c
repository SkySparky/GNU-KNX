#include "Core.h"
#include "KDK.h"
#include "Registry.h"

#include <stdlib.h>
#include <string.h>

void initializeCore(){
  Core = malloc(sizeof(_core));

  Core->oStreamOwner = NULL;
  Core->iStreamOwner = NULL;

  Core->defaultOStreamOwner = NULL;
  Core->defaultIStreamOwner = NULL;
}

void initializeNodeRegistry(){
  NodeReg = malloc(sizeof(_nodeReg));
  NodeReg->idList = calloc(Config->maxNodes, sizeof(bool));
}

void initializeConfig(){
  Config = malloc(sizeof(_config));

  //setup initial values
  Config->maxNodes = 128;
  Config->objRegCount = 0;
  Config->maxObjCount = 128;

  size_t vLen = strlen(RTEVERSION);
  Config->rteVersion = (char*) malloc(vLen);
  strncpy(Config->rteVersion, RTEVERSION, vLen);

  vLen = strlen(getKDKVersion());
  Config->kdkVersion = (char*) malloc(vLen);
  strncpy(Config->kdkVersion, getKDKVersion(), vLen);
}

void intitializeTypeRegistry(){

  //build registry
  TypeReg = malloc(sizeof(_typeReg));

  TypeReg->typeId = malloc(Config->maxObjCount * sizeof(int));
  TypeReg->hashId = malloc(Config->maxObjCount * sizeof(LUI));
  TypeReg->objectMap = malloc(Config->maxObjCount * sizeof(Object*));

  for(int i = 0; i < Config->maxObjCount; ++i)
    TypeReg->objectMap[i] = NULL;

  //populate registration table with basic types
  registerBasicTypes();
}

void initializeInterfaces(){
  registerObject = _registerObject;
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


bool allowStdOut(Node * caller){
  return caller == Core->oStreamOwner;
}

bool allowStdIn(Node * caller){
  return caller == Core->iStreamOwner;
}

bool requestOutPerm(Node * caller){
  //TODO
  return true;
}

bool requestInPerm(Node * caller){
  //TODO
  return true;
}
