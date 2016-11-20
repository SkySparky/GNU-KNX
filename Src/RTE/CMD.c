#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "CMD.h"
#include "Core.h"

#include "Macro.h"

bool parseCMD(int argc, char ** argv){
  bool isFatal = false;
  //generate default values

  //parse command line options
  for (size_t i = 1; i < argc; ++i){
    size_t len = strlen(argv[i]);

    if (argv[i][0]!='-' || len < 2){
      printf("Unrecognized option: %s (%lu)\r\n", argv[i], i-1);
      isFatal = true;
      continue;
    }

    if (argv[i][1] == '-'){//string option

    }else{//char option
      for(size_t j=1; j<len; ++j){
        switch(argv[i][j]){
            case 'h': printHelp();    break;
            case 'v': printVersion(); break;
          default:
          printf("Unrecognized option: %s (%c)\r\n", argv[i], argv[i][j]);
          isFatal=true;
        }
      }
    }
  }

  return isFatal;
}


void printHelp(){
  printf("-h            Print this message\r\n");
  printf("-v            Print KNX and KDK versions\r\n");
}

void printVersion(){
  //printf(">>%s\n", Config->kdkVersion);
  printf("KNX : %s | KDK : %s\r\n", Config->rteVersion, Config->kdkVersion);
}
