#include "Node.h"
#include "Prime.h"

#include <stdlib.h>
#include <stdio.h>

#include "../SDK/headers/Error.h"

extern unsigned primeList [500];

Registrar * makeRegistry()
{
  Registrar * reg = malloc(sizeof(Registrar));
  if (reg==0)
    return 0;

  reg->settings=makeSettings();
  reg->node_registry=malloc(0);
  reg->length=0;

  return reg;
}

int freeRegistrar(Registrar * reg)
{
  if (reg==0)
    return -1;

  //TODO Perform checks and clean all components
  free(reg);

  return 0;
}

Node * registerNode(Registrar * reg)
{
  if (reg==0)
    return 0;

  if (reg->length==reg->settings.maxNodes)
    return 0;

  //create new node
  Node * newNode = 0;
  newNode = malloc(sizeof(Node));

  if (newNode==0)
    return 0;

  newNode->base = malloc(sizeof(nodeBase));
  newNode->settings=&reg->settings;

  //register with id
  unsigned iDex=0;
  for (unsigned x=0; x<reg->length; ++x)
  {
    if (reg->node_registry[x]->base->id==primeList[iDex])
    {
      ++iDex;
      x=0;
    }
  }

  newNode->base->id=primeList[iDex];

  Node**chk = realloc(reg->node_registry, reg->length+1);
  if (chk==0)
    return 0;

  reg->node_registry=chk;
  reg->node_registry[reg->length]=newNode;
  ++reg->length;

  return newNode;
}


//deletes target node. Does not operate on child nodes
int deleteNode(Node * node)
{
  if (node==0)
    return -1;

  free(node);

  return 0;
}

//recursively destroy child tree
int deleteNodeTree(Node * root)
{
  if (root==0)
    return -1;

  for (unsigned x=0; x<root->base->numChildren; ++x)
    deleteNodeTree((Node*)root->base->children[x]);

  deleteNode(root);

  return 0;
}

int deregisterNode(Node * node, Registrar * reg)
{
  if (node==0 || reg==0)
    return -1;

  Node * target = 0;

  //find registry reference
  for (unsigned x=0; x<reg->length; ++x)
  {
    if (node->base->id==reg->node_registry[x]->base->id)
      {
        target=reg->node_registry[x];
        break;
      }
  }

  if (target==0)
    return -2;

  //begin collapsing child structure
  //TODO alert children to destruction, lock further operations, watch for hanging



  return 0;
}


int NodeProc(Registrar * reg)
{
  Node * node = registerNode(reg);
  if (node==0)
  {
    prntErr(E_INI_NODE, 0, reg->settings.prntWrn);
    return -1;
  }

  if (reg->settings.dbg)
    printf("Node %llu created\n", node->base->id);

  while (node->base->active)
  {

    break;
  }


  unsigned long long id = node->base->id;
  if (deregisterNode(node, reg))
  {
    prntErr(E_EXT_NODE, 0, reg->settings.dbg);
    return 0;
  }

  if (reg->settings.dbg)
    printf("Node %llu destroyed\n", id);

  return 0;
}
