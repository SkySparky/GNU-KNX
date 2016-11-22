#ifndef KNX_KEYWORD
#define KNX_KEYWORD

#define KW_START_INDEX 5000

#if BITVRS == 64


#else


#endif

#endif

typedef enum{

  _eVoid = KW_START_INDEX,
  _eInt,
  _eUInt,
  _eLong,
  _eULong,
  _eReal,
  _eChar,
  _eUChar,
  _eWChar,
  _eString,
  _eWString,
  _eBit,
  _eClass,
  _eDynamic,
  _eFunction,
  _eArray,
  _eCol,
  _eKeypair,
  _eFile,
  _eStream,
  _eNode

}KeyWordId;
