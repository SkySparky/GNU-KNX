#ifndef KNX_CORE
#define KNX_CORE

#include "Node.h"

/*
Defines system wide configurations and registries
*/

typedef struct _nodeReg{
  Node * root;

  //id used if corresponding index is true
  bool * idList;

}_nodeReg;

typedef struct _core{

  //IO permissions
  Node * oStreamOwner;
  Node * iStreamOwner;

}_core;

//system configuration variables
typedef struct _config{
  unsigned maxNodes;
}_config;

static _core * Core;
static _nodeReg * NodeReg;
static _config * Config;

//component generation
void initializeCore();
void initializeNodeRegistry();
void initializeConfig();

//registration procedures
bool registerNode(Node *);

#endif
