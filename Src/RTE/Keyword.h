#ifndef KNX_KEYWORD
#define KNX_KEYWORD

#define TP_START_INEDX 0
#define KW_START_INDEX 5000
#define SY_START_INDEX 10000

#if BITVRS == 64


#else


#endif

#endif

typedef enum{

  _eVoid = TP_START_INEDX,
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
  _eNode,

  _eIf = KW_START_INDEX,
  _eElse,
  _eFor,
  _eWhile,
  _eSwitch,
  _eCase,
  _eBreak,
  _eThrow,
  _eCatch,
  _ePublic,
  _ePrivate,
  _eProtected,
  _eLegacy,
  _eStatic,
  _eFinal,
  _eGlobal,
  _eAligned,
  _eCache,
  _eShrink,
  _eImport,
  _eInclude,
  _eModule,
  _eThis,
  _eMakeDoc,
  _eReadLine,
  _eReadChar,
  _ePrintLine,
  _ePrint,
  _eRequest_i,
  _eRelease_i,
  _eRequest_o,
  _eRelease_o,

  _eUndefined = SY_START_INDEX
}KeyWordId;
