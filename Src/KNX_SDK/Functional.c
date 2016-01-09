#include "Functional.h"

//verify input parameters are correct
bool validParams(token*stream, unsigned len, ...)
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

/*
int i;
  va_list al;
  va_start(al,num_count);
  for(i=1;i<=num_count;i++){
     int val=va_arg(al,int);
     printf("%d ",val);
*/
