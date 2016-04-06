#ifndef KNX_SDK_ERROR
#define KNX_SDK_ERROR

/*
Error and warning macros and console readout
*/

#define OK                0

//Warnings
  //General
  //Access
  //System
  //Parsing
#define W_IMP_CAST        0x0120//Implicit cast (valid)
#define W_NEG_ENCAP       0x0121//pOrder below 0
#define W_ENCAP_MSMATCH   0x0122//encapStack conjugate mismatch
  //Exchange
  //File
  //IO
  //Expression
  //Module
  //Misc
#define W_CUSTOM          0xFFF
//Errors
  //General
#define E_REG_INI         0x1000//failed to initialize registrar
#define E_REG_EXT         0x1001//error closing down registrar
#define E_NODE_LIMIT      0x1002//max node limit reached
#define E_INI_NODE        0x1003//node failed to initialize
#define E_EXT_NODE        0x1004//error closing down node
#define E_DEREG           0x1005//error de-registering node
  //Access
#define E_ACC_DENIED      0x1030//Invalid access permission
#define E_DATA_DNE        0x1031//Requested data does not exist
  //System
  //Parsing
#define E_IMP_CAST        0x1100//Implicit cast (invalid)
  //Exchange
  //File
  //IO
  //Expression
  //Module
  //Misc
#define E_CMD             0x1FFE
#define E_CUSTOM          0x1FFF

//error code, detail message, prntWrn
void prntErr(unsigned, char*, unsigned char);

#endif
