#ifndef KDK_OBJECT_SEARCH
#define KNX_OBJECT_SEARCH

#include "Structures.h"

typedef struct Object Object;
typedef struct ObjectLeaf ObjectLeaf;
typedef struct ObjectTree ObjectTree;

//Get
extern ObjectLeaf * getFromList(ObjectLeaf * root, LUI hashname);
extern ObjectLeaf * getFromBinary(ObjectLeaf * root, LUI hashname);
extern ObjectLeaf * getFromSplay(ObjectLeaf * root, LUI hashname);
extern ObjectLeaf * getFromRepeat(ObjectLeaf * root, LUI hashname);

extern Object * getMember(ObjectTree * tree, char * name);

//Add
//return false if item cannot be added
extern bool addToList(ObjectTree * tree, Object * object);
extern bool addToBinary(ObjectTree * tree, Object * object);
extern bool addToSplay(ObjectTree * tree, Object * object);
extern bool addToRepeat(ObjectTree * tree, Object * object);

extern bool addMember(ObjectTree * tree, Object * object);

#endif
