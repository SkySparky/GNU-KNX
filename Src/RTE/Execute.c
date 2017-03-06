#include "Processing.h"

void ExecuteInstructions(Node * node){
    
    Token * tkn = node->cache->head;

    while (tkn != NULL){

        

        tkn = tkn->next;
    }

    //cleanup

    //delete nodes
    tkn = node->cache->head;
    node->cache->current = NULL;
    while(tkn != NULL){
        Token * next = tkn->next;
        DeleteToken(tkn);
        tkn = next;
    }

    node->cache->head = NULL;

}