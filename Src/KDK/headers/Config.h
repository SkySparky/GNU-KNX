#ifndef KDK_CONFIG
#define KDK_CONFIG

typedef struct Config{

int _suppressWarnings;//Do not print warning messages
int _fatalWarnings;//Treat warnings as errors

int _verbose;

int _maxNodes;

} Config;

extern Config * _config;

Config * InitConfig();

#endif
