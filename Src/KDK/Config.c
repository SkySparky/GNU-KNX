#include <stdlib.h>

#include "Config.h"

struct Config * _config;

Config * InitConfig(){
  _config = malloc(sizeof(Config));

  _config = malloc(sizeof(Config));

  _config->_suppressWarnings = 0;
  _config->_fatalWarnings = 0;

  _config->_verbose = 0;
  _config->_maxNodes = 1000;

  return _config;
}
