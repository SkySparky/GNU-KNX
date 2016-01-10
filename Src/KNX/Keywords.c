#include "Keywords.h"

//convert symbol to token code
tCode keycode(long long unsigned hash)
{
  tCode tc=0;

  for (unsigned x=0; x<DEF_KEYWORDS; ++x)
  {
    //printf("%llu >> %llu\n",hash, keyList[x]);
    if (keyList[x]==hash)
      switch(x)
      {
        case KW_EXIT: tc = _kExit; break;
        case KW_SHORT: tc = _kShort; break;
        case KW_INT: tc = _kInt; break;
        case KW_LONG: tc = _kLong; break;
        default:
        tc=KW_NA;
      }
    }
  return tc;
}
