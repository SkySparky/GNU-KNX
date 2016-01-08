#include "Keywords.h"
#include "Util.h"

tCode keycode(long long unsigned hash)
{
  tCode tc=0;

  for (unsigned x=0; x<DEF_KEYWORDS; ++x)
    if (keyList[x]==hash)
      switch(x-1)
      {
        case KW_EXIT: tc = _kExit; break;
        default:
        tc=KW_NA;
      }
  return tc;
}
