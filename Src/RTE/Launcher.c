#include <stdio.h>
#include <stdlib.h>

#include "KDK.h"

#include "CMD.h"
#include "Config.h"
#include "Init.h"

struct Config * _config = NULL;
struct NodeRegistry * _nodeReg = NULL;

void InitConfig(){

  _config = malloc(sizeof(Config));

  _config->_suppressWarnings = 0;
  _config->_fatalWarnings = 0;

  _config->_verbose = 0;
  _config->_maxNodes = 1000;
}

int main(int argc, char ** argv, char ** argx){

  InitConfig();

  if (ExecuteCMD(argc, argv, argx) == -1)
  {
    printf("Errors found in option: terminating...\r\n");
    return -1;
  }

  //setup global structures
  InitNodeReg(_config, _nodeReg);

  InitInterfaces();
  _nodeProc(NULL);

  //create global node

  return 0;
}
