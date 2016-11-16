#include <stdlib.h>

#include "ObjectSearch.h"
#include "Util.h"

#include <string.h>

//TODO account for member.member nesting
//currently does not check for nested members
//implement object search recursion or whatever in getMember

//get in a standard method from a list
ObjectLeaf * getFromList(ObjectLeaf * root, LUI hashname){

  return NULL;
}

//get from a standard binary tree
ObjectLeaf * getFromBinary(ObjectLeaf * root, LUI hashname){

  return NULL;
}

//get from a splay binary tree
ObjectLeaf * getFromSplay(ObjectLeaf * root, LUI hashname){


  return NULL;
}

//get from a standard list, but move accessed element to front
ObjectLeaf * getFromRepeat(ObjectLeaf * root, LUI hashname){

  return NULL;
}

Object * getMember(ObjectTree * tree, char * name){

  if (tree == NULL) return NULL;

  LUI hash = _FNV_1A(name);
  ObjectLeaf * newRoot = NULL;

  //check for nested members
  switch(tree->memScheme){
    case _list:
      newRoot = getFromList(tree->root, hash);
      break;
    case _binary:
      newRoot = getFromList(tree->root, hash);
      break;
    case _splay:
      newRoot = getFromList(tree->root, hash);
      break;
    case _repeat:
      newRoot = getFromRepeat(tree->root, hash);
      break;
  }

  tree->root = newRoot != NULL ? newRoot : tree->root;

  return newRoot->target;
}

bool addToList(ObjectTree * tree, Object * object){

  return true;
}

bool addToBinary(ObjectTree * tree, Object * object){

  return false;
}

bool addToSplay(ObjectTree * tree, Object * object){

  return true;
}

bool addToRepeat(ObjectTree * tree, Object * object){

  return true;
}

bool addMember(ObjectTree * tree, Object * object){
  switch (tree->memScheme){
    case _list:
      return addToList(tree, object);
      break;
    case _binary:
      return addToList(tree, object);
      break;
    case _splay:
      return addToList(tree, object);
      break;
    case _repeat:
      return addToList(tree, object);
      break;
  }

  return false;
}
