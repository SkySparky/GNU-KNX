#include <stdlib.h>
#include <string.h>

#include "Keyword.h"
#include "Token.h"
#include "Util.h"

Token * makeToken(char * str, Node * scope){
  Token * tkn = malloc(sizeof(Token));

  size_t len = strlen(str)+1;

  tkn->word = malloc(len);
  strncpy(tkn->word, str, len);

  tkn->hash = _FNV_1A(str);
  tkn->next=NULL;
  tkn->prev=NULL;

  if (scope){
    //resolve

    tkn->lexeme = _eUndefined;
  }else{
    tkn->lexeme = _eUndefined;
  }

  return tkn;
}
