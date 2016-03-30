#include "Settings.h"

Settings makeSettings()
{
  Settings ret;
  ret.prntWrn=1;
  ret.tabAssist=1;
  ret.dbg=0;

  ret.maxNodes=500;
  ret.tabSize=2;

  return ret;
}
