#include "Functional.h"

//verify input parameters are correct
bool validParams(unsigned len,token*stream, ...)
{

flag decoy;

va_list lstPtr;
va_start(lstPtr,stream);

for (unsigned x=0; x<len; ++x)
  {
    flag chk = va_arg(lstPtr, flag);
    if (chk!=stream[x].type)
      return false;
  }

va_end(lstPtr);

return true;
}
