#include <string.h>
#include <stdlib.h>

#include "Lang.h"

Token * BuildToken(char * raw_start, char * raw_end, Lexeme lx){
  Token * token = malloc(sizeof(Token));

  token->next = 0;
  token->previous = 0;
  token->lexeme = lx;
  token->raw = malloc((raw_end - raw_start)+2);
  strncpy(token->raw, raw_start, (raw_end - raw_start)+2);
  token->raw[(raw_end - raw_start) + 1] = 0;

  return token;
}

void DeleteToken(Token * tkn){

    if (tkn->previous!=NULL && tkn->next!=NULL){
        tkn->previous->next = tkn->next;
        tkn->next->previous = tkn->previous;
    } else {
        if (tkn->next == NULL) tkn->previous->next = NULL;
        if (tkn->previous == NULL) tkn->next->previous = NULL;
    }

    if (tkn->raw != NULL) free(tkn->raw);

    free(tkn);
}