#include "Node.h"
#include "Prime.h"
#include "Lexile.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../SDK/headers/Error.h"

#include "../SDK/headers/Memory.h"

extern unsigned primeList [500];

Registrar * makeRegistry()
{
  Registrar * reg = malloc(sizeof(Registrar));
  if (reg==0)
    return 0;

  reg->settings=makeSettings();
  reg->node_registry=malloc(0);
  reg->node_length=0;

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

Node * registerNode(Registrar * reg, mMemory*global)
{
  if (reg==0)
    return 0;

  if (reg->node_length==reg->settings.maxNodes)
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
  for (unsigned x=0; x<reg->node_length; ++x)
  {
    newNode->conId=x;
    if (reg->node_registry[x]->base->id==primeList[iDex])
    {
      ++iDex;
      x=0;
    }
  }

  newNode->base->id=primeList[iDex];

  Node**chk = realloc(reg->node_registry, reg->node_length+1);
  if (chk==0)
    return 0;

  reg->node_registry=chk;
  reg->node_registry[reg->node_length]=newNode;
  ++reg->node_length;

  newNode->global=global;
  newNode->local=makeMemory();

  newNode->base->active=1;

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
  for (unsigned x=0; x<reg->node_length; ++x)
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


int NodeProc(Registrar * reg, mMemory*global)
{
  Node * node = registerNode(reg,global);
  if (node==0)
  {
    prntErr(E_INI_NODE, 0, reg->settings.prntWrn);
    return -1;
  }

  if (reg->settings.dbg)
    printf("Node %llu created\n", node->base->id);

  Interpreter * intr = makeInterpreter(node, reg);

  char * buff = malloc(256);
  size_t nBytes = 256;

  while (node->base->active)
  {
    printf("|%d>>\t", node->conId);
    if (reg->settings.tabAssist)
      for (unsigned x=0; x<reg->settings.tabSize; ++x)
        printf(" ");
    getline(&buff, &nBytes, stdin);
    #ifdef __WINDOWS
    if (buff[strlen(buff)-1]==10)
      buff[strlen(buff)-1]=0;//remove leading NL
    #endif

    Token * stream = analyze(buff, intr);
    if (stream!=0 && intr->pOrder==0)
      break;//TODO replace with execution stage
  }


  unsigned long long id = node->base->id;
  if (deregisterNode(node, reg))
  {
    prntErr(E_EXT_NODE, 0, reg->settings.dbg);
    return 0;
  }

  free(buff);

  if (reg->settings.dbg)
    printf("Node %llu destroyed\n", id);

  return 0;
}
