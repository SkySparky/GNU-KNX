#include <stdlib.h>

#include "Prime.h"

unsigned * GeneratePrimeList(unsigned length){

  if (length < 1) return NULL;

  unsigned * primeList = malloc(sizeof (unsigned) * length);
  primeList[0] = 2;

  unsigned count, c, i = 3;

   for ( count = 2 ; count <= length ; ++i)
   {
      for ( c = 2 ; c <= i - 1 ; c++ )
      {
         if ( i%c == 0 ) break;
      }
      if ( c == i )
      {
        primeList[count - 1] = i;
         count++;
      }
   }

  return primeList;
}
