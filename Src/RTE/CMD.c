#include <string.h>

#include "CMD.h"
#include "Config.h"

struct Config * _config;

void Help(){
  printf("\n");
  printf("-h            Display help text\r\n");
  printf("-w            Warnings suppressed\r\n");
  printf("-e            Warnings treated as errors\r\n");
  printf("-v            Print version information\r\n");
  printf("-V            Verbose message printing\r\n");
}

void VersionInfo(){
  printf("KDK Version : \r\n");
  printf("RTE Version : \r\n");
}

int ExecuteCMD(int argc, char ** argv, char ** argx){

  int rCode = 0;

  for (int itemNum = 1; itemNum < argc; ++itemNum){
    printf("%s\n", argv[itemNum]);

    int optMode = (argv[itemNum][0] == '-') + (argv[itemNum][1] == '-');

    if (optMode == 0){
      printf("Unrecognized option: %s\r\n", argv[itemNum]);
      ++rCode;
      continue;
    }

    size_t len = strlen(argv[itemNum]);

    if (optMode == 1){
      for (size_t i = 1; i < len; ++i){
        switch (argv[itemNum][i]){
          case 'h': Help(); break;
          case 'w': _config->_suppressWarnings = 1; break;
          case 'e': _config->_fatalWarnings = 1; break;
          case 'v': VersionInfo(); break;
          case 'V': _config->_verbose = 1; break;
          default:
          printf("Unrecognized option: -%c\r\n", argv[itemNum][i]);
          ++rCode;
          break;
        }
      }
    } else {
      if (strncmp("", argv[itemNum], 255) == 0){

      } else {
        printf("Unrecognized option: %s\r\n", argv[itemNum]);
        ++rCode;
        continue;
      }
    }
  }

  return rCode;
}
