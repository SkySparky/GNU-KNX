#ifndef KDK_INTERFACE
#define KDK_INTERFACE

/*
Implements functions interfaces between KDK and KNX
*/

typedef struct Object Object;

//left: current data
//right: cast to type
typedef Object* (*castable)(Object*, Object*);

//register a custom class with the system. Stores default value
//1) Type name
//2) Default value
typedef int (*__registerObject)(char *, void *, castable);
__registerObject registerObject;
//TODO add registerModule
#endif
