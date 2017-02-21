#ifndef KDK_LANG
#define KDK_LANG

typedef enum {
  _placeholder
}_lexeme;

//basic input identifier
typedef struct Token{

  struct Token * head;
  struct Token * next;

  char * raw;
  _lexeme lexeme;

} Token;

//statement cache for intermediate parsing
typedef struct TCache{
  Token * cache;
  Token * head;

  unsigned nestLevel;//current () nest level open. Don't execute until 0
} TCache;

Token * BuildToken(char * raw, _lexeme type);

#endif
