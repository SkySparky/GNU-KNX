#include <stdio.h>

#include "Init.h"
#include "KNode.h"


void InitInterfaces()
{
  _nodeProc = &NodeProc;
  _registerNode = &RegisterNode;
}
