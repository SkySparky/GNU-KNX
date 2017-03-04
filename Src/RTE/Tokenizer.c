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

  printf("[%s]\r\n", token->raw);

  return token;
}

int Tokenize(Node*node, char * raw){

  size_t len = strlen(raw);

  //reset from single line comments
  if (node->cache->pMode == _pSComment)
    node->cache->pMode = _pNormal;

  char * iterator = raw;

  for (size_t x = 0; x <= len; ++x){
    char c = raw[x];

    //end of string
    if (c == 0){

      break;
    }

    if (node->cache->pMode == _pSString){
      if (c=='\''){
        node->cache->pMode = _pNormal;
        BuildToken(iterator + 1, raw + x - 1, _lChar);
      }
      continue;
    }else if (node->cache->pMode == _pDString){
      if (c=='\"'){
        node->cache->pMode = _pNormal;
        BuildToken(iterator + 1, raw + x - 1, _lText);
      }
      continue;
    }else if (node->cache->pMode == _pMComment){
      if (c == '*' && raw[x+1] == '#'){
        ++x;
        node->cache->pMode = _pNormal;
      }
      continue;
    }

    //pop current buffer if special found
    if( (c < 'a' && c > 'z') && (c < 'A' && c > 'Z') && //Letters
        (c < '0' && c > '9') && //Numbers
        (c != '_')){  //Standard Characters
          if (iterator == raw + x) continue;//empty buffer
          AddToken(node->cache, BuildToken(iterator, raw+x-1, _lNA));
          iterator = raw + x;
        }

    Lexeme lType = _lNA;
    unsigned popSize = 1;

    switch(c){
      case ' ':
      case '\t':
      iterator = raw + x + 1;
      break;
      //strings
      case '\'':
      node->cache->pMode = _pSString;
      iterator = raw + x;
      break;
      case '\"':
      node->cache->pMode = _pDString;
      iterator = raw + x;
      break;
      //operators : {} yourselves
      case '+':
        if (raw[x+1]=='=') {lType = _lSetAdd; popSize=2;}
        else if (raw[x+1]=='+')//determine if pre or post inc based on last token
        {lType = (node->cache->current == NULL || node->cache->current->lexeme == _lVariable)?
        _lPreInc : _lPostInc; popSize=2;}
        else lType = _lAdd;
      break;
      case '-':

      break;
      case '*':

      break;
      case '/':

      break;
      case '%':

      break;
      case '^':

      break;
      /*case -251://Implement root

      break;*/
      //comments
      case '#':
      if (raw[x+1] == '*') node->cache->pMode = _pMComment;
      else return 0;//line is ended
      break;

      default:
      popSize = 0;
      iterator = raw + x + 1;
      break;
    }

    if (node->cache->pMode != _pNormal)
      continue;

    if (popSize > 0){
      AddToken(node->cache, BuildToken(raw+x, iterator, lType));
      printf("Added %s\r\n", node->cache->current->raw);
    }else{
      //TODO throw warning/error
      printf("I don't understand, Dave\r\n");
    }

  }

  return 0;
}
