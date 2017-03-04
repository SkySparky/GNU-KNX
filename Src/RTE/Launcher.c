#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "KDK.h"

#include "CMD.h"
#include "Init.h"
#include "KNode.h"

struct Config * _config = NULL;
struct NodeRegistry * _nodeReg = NULL;
unsigned * _primeList = NULL;

int main(int argc, char ** argv, char ** argx){

  _config = InitConfig();

  if (ExecuteCMD(argc, argv, argx) == -1)
  {
    printf("Errors found in option: terminating...\r\n");
    return -1;
  }

  //setup global structures
  _nodeReg = InitNodeReg();
  InitInterfaces();
  _primeList = GeneratePrimeList(_config->_maxNodes);

  //create global node
  Node * global = BuildNode(NULL);
  RegisterNode(global);

  pthread_create(&global->pThread, NULL, NodeProc, (void*)global);
  pthread_join(global->pThread, NULL);

  return 0;
}
