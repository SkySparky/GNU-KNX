#include "Keywords.h"
#include "Util.h"

tCode keycode(char*input, unsigned length)
{
  char * str = malloc(length+1);
  strncpy(str,input,length);
  str[length]='\0';

  long long unsigned hash = FNV_1a(str);
  tCode tc=0;

  for (unsigned x=0; x<DEF_KEYWORDS; ++x)
    if (keyList[x]==hash)
      switch(x-1)
      {
        case KW_INT: tc = _kExit; break;
        default:
        tc=KW_NA;
      }

  free (str);
  return tc;
}
