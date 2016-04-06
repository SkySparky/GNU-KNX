#include "headers/Error.h"

#include <stdio.h>

void prntErr(unsigned code, char*msg, unsigned char prntWrn)
{

if (prntWrn==0 && code < 0x1000)
  return;

if (code<0x1000)
  printf("Warning (%u):   ", code);
else
  printf("Error (%u):     ", code);

switch(code)
{
  case W_IMP_CAST: printf("Implicit type cast [%s]", msg); break;//FROM > TO
  case W_NEG_ENCAP: printf("Unexpected close encapsulator [%s]", msg); break;//ENCAP
  case W_ENCAP_MSMATCH: printf("Mismatched encapsulator [%s]", msg); break;//Expected ENCAP received ENCAP

  case W_CUSTOM: printf("%s", msg); break;

  case E_REG_INI: printf("Failed to initialize registrar"); break;
  case E_REG_EXT: printf("Failed to deconstruct registrar"); break;
  case E_NODE_LIMIT: printf("Node limit reached"); break;
  case E_INI_NODE: printf("Failed to initialize node"); break;
  case E_EXT_NODE: printf("Failed to deconstruct node"); break;
  case E_DEREG: printf("Failed to de-register node"); break;

  case E_CMD: printf("Unrecognized option: %s", msg); break;

  case E_CUSTOM: printf("%s", msg); break;
}

printf("\n");

}
