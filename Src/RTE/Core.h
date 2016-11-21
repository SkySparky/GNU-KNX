#ifndef KNX_CORE
#define KNX_CORE

#include "Node.h"
#include "Registry.h"

/*
Defines system wide configurations and registries
*/

typedef struct _nodeReg{
  //TODO consider optimized structure
  Node * root;

  //id used if corresponding index is true
  bool * idList;

}_nodeReg;

typedef struct _typeReg{
  int * typeId;
  LUI * hashId;
  Object ** objectMap;
}_typeReg;

typedef struct _core{

  //IO permissions
  Node * oStreamOwner;
  Node * iStreamOwner;

}_core;

//system configuration variables
typedef struct _config{
  unsigned maxNodes;

  char * rteVersion;
  char * kdkVersion;

  //system data
  unsigned objRegCount;
  unsigned maxObjCount;//maximum unique types. Can be resized
}_config;

_core * Core;
_nodeReg * NodeReg;
_config * Config;
_typeReg * TypeReg;

//component generation
void initializeCore();
void initializeNodeRegistry();
void initializeConfig();
void intitializeTypeRegistry();
void initializeInterfaces();

//registration procedures
bool registerNode(Node *);

#endif
