#include "Tokenizer.h"
#include "Keyword.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//helper macros
#define _isWhiteSpace(c) (c<=32)
#define _isNum(c) (c>='0' && c<='9')
#define _isAlpha(c) ((c>='a' && c<='z') || (c>='A' && c<= 'Z'))
#define _isAlphaNum(c) (_isAlpha(c) || _isNum(c))

Token * AppendToken(char * start, char * end, Node * node){
  size_t len = (end - start) + 1;

  char * copy = malloc(len);

  strncpy(copy, start, len);

  printf("|%s|\n", copy);

  return makeToken(copy, node);
}

Token * tokenize(char * raw, Node * node){

  Token * head = NULL;
  Token * current = NULL;

  char * iter = raw;//string iterator
  char * ldex = raw;//last cut index

  do{

    if (_isAlphaNum(*iter)){
      ++iter;
      continue;
    }


    //delimit wide range
    if (_isWhiteSpace(*iter)){

      if (ldex != iter){//ignore repeat whitespace
        Token * newToken = AppendToken(ldex, iter-1, node);
        if (!head){
          head = newToken;
          current = newToken;
          newToken->prev = NULL;
          newToken->next = NULL;
        }else{
          current->next = newToken;
          newToken->prev = current;
          newToken->next = NULL;
          current = newToken;
        }
      }

      ldex = ++iter;
      continue;
    }

    //search for delimiters
    switch(*iter){
      //assignment and math
      case '=':
      break;
      case '!':
      break;
      case '+':
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
      /*case '√': TODO
      break;*/

      default:
        ldex = iter+1;
        break;
    }

    ++iter;
  }while(*iter);

  return head;
}
