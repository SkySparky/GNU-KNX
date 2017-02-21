#ifndef KDK_MEMORY
#define KDK_MEMORY

typedef struct Object{
  unsigned typeId;

  void * value;
} Object;

typedef struct Scope{

  unsigned structureType;//TODO
  Object * memory;

} Scope;

#endif
