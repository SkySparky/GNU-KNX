#ifndef KNX_SETTINGS
#define KNX_SETTINGS

struct tSettings;

typedef struct tSettings
{
  unsigned char prntWrn:1;
  unsigned char tabAssist:1;
  unsigned char dbg:1;

  unsigned maxNodes;
  unsigned short tabSize;

}Settings;

Settings makeSettings();

#endif
