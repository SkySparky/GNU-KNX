#ifndef KNX_SDK_MEM
#define KNX_SDK_MEM

/*
Defines all memory types
*/

enum memTypes{__bool, __uint, __llint, __double, __char, __string, __port, __pipe, __struct};

typedef struct object
{

}object,*_object;

//boolean
typedef struct _bool_ : public object
{

}_bool_;

//unsigned integer
typedef struct _integer_ : public object
{

}_integer_;

//string object
typedef struct _string_ : public object
{

}_string_;

#endif