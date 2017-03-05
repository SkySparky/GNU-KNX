#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "KNode.h"

void AddToken(TCache * cache, Token * newToken){

  if (cache->head == NULL){
    cache->head = newToken;
    cache->current = newToken;
    return;
  }

  cache->current->next = newToken;
  newToken->previous = cache->current;
  cache->current = newToken;
}

Token * BuildToken(char * raw_start, char * raw_end, Lexeme lx){
  Token * token = malloc(sizeof(Token));

  token->next = NULL;
  token->previous = NULL;
  token->lexeme = lx;
  token->raw = malloc((raw_end - raw_start)+2);
  strncpy(token->raw, raw_start, (raw_end - raw_start)+2);
  token->raw[(raw_end - raw_start) + 1] = 0;

  printf("[%s %d]\r\n", token->raw, lx);

  return token;
}

int Tokenize(Node*node, char * raw, size_t len){

  char * itr = raw;

  for (size_t x=0; x <= len; ++x){

    char c = raw[x];

    if (c == 0){
      if (itr != raw + x) AddToken(node->cache, BuildToken(itr, raw+x, _lNA));
      break;
    }

    if (node->cache->pMode != _pNormal){
      if (node->cache->pMode == _pSString){
        if (c=='\''){
          //TODO throw warning if multi char
          node->cache->pMode = _pNormal;
          AddToken(node->cache, 
            BuildToken(itr, raw+x-1, 
              (raw+x) - itr == 1 ? 
                _lChar :
                _lText));
          itr = raw + x + 1;
        }
      }else if (node->cache->pMode == _pDString){
        if (c=='\"'){
          node->cache->pMode = _pNormal;
          AddToken(node->cache, 
            BuildToken(itr, raw+x-1, _lText));
          itr = raw + x + 1;
        }
      }else if (node->cache->pMode == _pMComment){
        if (c=='*' && raw[x+1]=='#'){
          node->cache->pMode = _pNormal;
          ++x;
          itr = raw + x + 1;
        }
      }

      continue;
    }

    //regular characters
    if (
      (c>='a' && c<='z') ||
      (c>='A' && c<='Z') ||
      (c>='0' && c<='9') ||
      (c=='_' || c=='.')){
      continue;
    } else if (itr != raw+x) { //pop current buffer

      AddToken(node->cache, BuildToken(itr, raw+x-1, _lNA));
      itr = raw + x + 1;
    }
    switch (c){
      //whitespace
      case ' ':
      case '\t':
      itr = raw + x + 1;
      break;

      //strings
      case '\'':
      itr = raw + x + 1;
      node->cache->pMode = _pSString;
      break;
      case '\"':
      itr = raw + x + 1;
      node->cache->pMode = _pDString;
      break;

      //comments
      case '#':
      if (raw[x+1]=='*') node->cache->pMode = _pMComment;
      else return 0;//rest of line commented, ignore
      break;
      default:

      //operators
      case '+':
      if (raw[x+1]=='+'){
        AddToken(node->cache,
          BuildToken(raw+x, 
            raw+x+2, 
            node->cache->current == NULL || node->cache->current->lexeme!=_lVariable ? _lPostInc : _lPreInc));
        ++x;
      } else if (raw[x+1]=='='){
        AddToken(node->cache, BuildToken(raw+x, raw+x+2, _lSetAdd));
        ++x;
      } else {
        AddToken(node->cache, BuildToken(raw+x, raw+x+1, _lAdd));
      }
      break;
      case '-':
      if (raw[x+1]=='-'){
        AddToken(node->cache,
          BuildToken(raw+x, 
            raw+x+2, 
            node->cache->current == NULL || node->cache->current->lexeme!=_lVariable ? _lPostDec : _lPreDec));
        ++x;
      } else if (raw[x+1]=='='){
        AddToken(node->cache, BuildToken(raw+x, raw+x+2, _lSetSub));
        ++x;
      } else {
        AddToken(node->cache, BuildToken(raw+x, raw+x+1, _lSub));
      }
      break;

      default:
      break;
    }

    itr = raw + x + 1;
  }

  return 0;
}
