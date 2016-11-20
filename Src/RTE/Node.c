#define _GNU_SOURCE

#include "Node.h"
#include "Core.h"
#include "Util.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//construct a node and register it
Node * buildNode(char * name, Node * parent){
  Node * node = malloc(sizeof(Node));

  size_t nameLen = strlen(name);
  node->name = malloc(nameLen + 1);
  strncpy(node->name, name, nameLen + 1);

  node->hash = _FNV_1A(name);

  if (!node || !registerNode(node)){
    return NULL;
  }

  node->parent = parent;
  node->nextSibling = NULL;
  node->children = NULL;
  //assign as sibling
  if (parent){//if not root
    if (!parent->children){//create first child
      parent->children = node;
      node->prevSibling = NULL;
    }else{//create unloved children
      Node * lastChild = parent->children;
      while(lastChild->nextSibling)
        lastChild = lastChild->nextSibling;

      lastChild->nextSibling = node;
      node->prevSibling = lastChild;
    }
  }

  //assign default security settings
  node->secureGroup = 0;
  node->secureMode = _npPublic;

  //launch node thread
  pthread_create(&node->handle, NULL, nodeProc, (void*)node);

  if (node->id == 0){
    pthread_join(node->handle, NULL);
  }

  return node;
}

void * nodeProc(void * vnode){

  Node * node = (Node *) vnode;

  printf("Node start: %d\r\n", node->id);

  char * line;
  size_t len;

  printf("%s(%u) | ", node->name, node->id);
  getline(&line, &len, stdin);

  printf(">>%s\r\n", line);

  printf("Node end: %d\r\n", node->id);

  return NULL;
}
