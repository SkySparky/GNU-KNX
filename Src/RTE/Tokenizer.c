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
  printf("%d\r\n", raw[0]);
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

      //operators
      //math
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
      case '/':
      if (raw[x+1]=='='){
        AddToken(node->cache, BuildToken(raw+x, raw+x+2, _lSetDiv));
        ++x;
      } else {
        AddToken(node->cache, BuildToken(raw+x, raw+x+1, _lDiv));
      }
      break;
      case '*':
      if (raw[x+1]=='='){
        AddToken(node->cache, BuildToken(raw+x, raw+x+2, _lSetMult));
        ++x;
      } else {
        AddToken(node->cache, BuildToken(raw+x, raw+x+1, _lMult));
      }
      break;
      case '%':
      if (raw[x+1]=='='){
        AddToken(node->cache, BuildToken(raw+x, raw+x+2, _lSetModu));
        ++x;
      } else {
        AddToken(node->cache, BuildToken(raw+x, raw+x+1, _lModu));
      }
      break;
      case '^':
        AddToken(node->cache, BuildToken(raw+x, raw+x+1, _lPow));
      break;
      case -30://root
        AddToken(node->cache, BuildToken(raw+x, raw+x+1, _lRoot));
      break;

      //logic
      case '&':
      if (raw[x+1]=='&'){
        AddToken(node->cache, BuildToken(raw+x, raw+x+2, _lAnd));
        ++x;
      } else if (raw[x+1]=='=') {
        AddToken(node->cache, BuildToken(raw+x, raw+x+2, _lSetAnd));
        ++x;
      } else {
        AddToken(node->cache, BuildToken(raw+x, raw+x+1, _lBAnd));
      }
      break;
      case '|':
      if (raw[x+1]=='|'){
        AddToken(node->cache, BuildToken(raw+x, raw+x+2, _lOr));
        ++x;
      } else if (raw[x+1]=='!') {
        AddToken(node->cache, BuildToken(raw+x, raw+x+2, _lXOr));
        ++x;
      } else if (raw[x+1]=='=') {
        AddToken(node->cache, BuildToken(raw+x, raw+x+2, _lSetOr));
        ++x;
      } else {
        AddToken(node->cache, BuildToken(raw+x, raw+x+1, _lBOr));
      }
      break;
      case '!':
      if (raw[x+1]=='='){
        AddToken(node->cache, BuildToken(raw+x, raw+x+2, _lNEqu));
        ++x;
      } else if (raw[x+1]=='|') {
        AddToken(node->cache, BuildToken(raw+x, raw+x+2, _lNOr));
        ++x;
      } else {
        AddToken(node->cache, BuildToken(raw+x, raw+x+1, _lNot));
      }
      break;
      case '=':
      if (raw[x+1]=='='){
        AddToken(node->cache, BuildToken(raw+x, raw+x+2, _lEqu));
        ++x;
      } else {
        AddToken(node->cache, BuildToken(raw+x, raw+x+1, _lSet));
      }
      break;
      case '<':
      if (raw[x+1]=='='){
        if (raw[x+2]=='>'){
          AddToken(node->cache, BuildToken(raw+x, raw+x+3, _lOutsideInc));
          x+=2;
        }else{
          AddToken(node->cache, BuildToken(raw+x, raw+x+2, _lLssEqu));
          ++x;
        }
      } else if (raw[x+1]=='<') {
        AddToken(node->cache, BuildToken(raw+x, raw+x+2, _lLShift));
        ++x;
      } else if (raw[x+1]=='>') {
        AddToken(node->cache, BuildToken(raw+x, raw+x+2, _lOutsideEx));
        ++x;
      } else {
        AddToken(node->cache, BuildToken(raw+x, raw+x+1, _lLss));
      }
      break;
      case '>':
      if (raw[x+1]=='='){
        if (raw[x+2]=='<'){
          AddToken(node->cache, BuildToken(raw+x, raw+x+3, _lWithinInc));
          x+=2;
        } else {
          AddToken(node->cache, BuildToken(raw+x, raw+x+2, _lGtrEqu));
          ++x;
        }
      } else if (raw[x+1]=='>') {
        AddToken(node->cache, BuildToken(raw+x, raw+x+2, _lRShift));
        ++x;
      } else if (raw[x+1]=='<') {
        AddToken(node->cache, BuildToken(raw+x, raw+x+2, _lWithinEx));
        ++x;
      } else {
        AddToken(node->cache, BuildToken(raw+x, raw+x+1, _lGtr));
      }
      break;

      //indexing
      case ':':
        AddToken(node->cache, BuildToken(raw+x, raw+x+1, _lIndex));
      break;
      case ';':
        AddToken(node->cache, BuildToken(raw+x, raw+x+1, _lList));
      break;

      //encapsulation
      case '{':
        AddToken(node->cache, BuildToken(raw+x, raw+x+1, _lOBrace));
        node->cache->nestType[node->cache->nestLevel++] = '{';
      break;
      case '[':
        AddToken(node->cache, BuildToken(raw+x, raw+x+1, _lOBrack));
        node->cache->nestType[node->cache->nestLevel++] = '[';
      break;
      case '(':
        AddToken(node->cache, BuildToken(raw+x, raw+x+1, _lOParan));
        node->cache->nestType[node->cache->nestLevel++] = '(';
      break;
      case '}':
        AddToken(node->cache, BuildToken(raw+x, raw+x+1, _lCBrace));
        node->cache->nestType[--node->cache->nestLevel] = 0;
      break;
      case ']':
        AddToken(node->cache, BuildToken(raw+x, raw+x+1, _lCBrack));
        node->cache->nestType[--node->cache->nestLevel] = 0;
      break;
      case ')':
        AddToken(node->cache, BuildToken(raw+x, raw+x+1, _lCParan));
        node->cache->nestType[--node->cache->nestLevel] = 0;
      break;

      //Misc
      case '$':
        AddToken(node->cache, BuildToken(raw+x, raw+x+1, _lLambda));
      break;
      case '~':
        if (raw[x+1]=='|'){
        AddToken(node->cache, BuildToken(raw+x, raw+x+2, _lXNor));
        ++x;
      } else {
        AddToken(node->cache, BuildToken(raw+x, raw+x+1, _lBNot));
      }
      break;

      default:
      break;
    }

    itr = raw + x + 1;
  }

  return 0;
}
