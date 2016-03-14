/*
Starting point

Initializes global data (from langauge perspective)
First thread is root
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Node.h"

#include "../SDK/headers/Error.h"

int parseCMD(int argc, char**argv, Registrar * reg)
{
  int ret=0;

  for (int x=1; x<argc; ++x)
  {
    int len = strlen(argv[x]);

    if (len==2)//toggle
    {
      if (argv[x][0]!='-')
      {
        prntErr(E_CMD, argv[x], 1);
        ret=-1;
      }
    else
      {
        switch(argv[x][1])
        {
          case 'd': reg->settings.dbg=1; break;
          case 't': reg->settings.tabAssist=1; break;
          case 'w': reg->settings.prntWrn=0; break;

          default:
          prntErr(E_CMD, argv[x], 1);
          ret=-1;
        }
      }
    }else if (len>2)//assignment
    {

    }else//invalid
    {
      prntErr(E_CMD, argv[x], 1);
      ret=-1;
    }
  }

  return ret;
}

#ifndef DEBUG
int main(int argc, char**argv, char **argx)
{
  Registrar * reg = makeRegistry();

  if (reg==0)
  {
    prntErr(E_REG_INI, 0, 1);
    return E_REG_INI;
  }

  parseCMD(argc, argv, reg);

  int rVal = NodeProc(reg);

  if (rVal)
  {
    printf("Error----\n");
  }

  if (freeRegistrar(reg))
  {
    prntErr(E_REG_EXT, 0, 1);
    return E_REG_EXT;
  }

  return 0;
}
#else
int main(int argc, char**argv, char**argx)
{

  return 0;
}
#endif
