#include <stdio.h>
#include <string.h>

#include "Errors.h"
#include "Config.h"

int LogErr(unsigned code, char * msg)
{
  if (code <= MAX_WARNINGS && _config->_suppressWarnings){
    return 0;
  }

  switch(code){

  }

  printf("\r\n");

  return (code >= MIN_ERRORS && code <= MAX_ERRORS) || (code <= MIN_WARNINGS && _config->_fatalWarnings);
}
