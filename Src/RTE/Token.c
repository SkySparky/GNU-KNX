#include <stdlib.h>
#include <string.h>

#include "Token.h"
#include "Util.h"

Token * makeToken(char * str){
  Token * tkn = malloc(sizeof(Token));

  size_t len = strlen(str)+1;

  tkn->word = malloc(len);
  strncpy(tkn->word, str, len);

  tkn->hash = _FNV_1A(str);
  tkn->next=NULL;
  tkn->prev=NULL;

  return tkn;
}
