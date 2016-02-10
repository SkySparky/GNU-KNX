#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <Windows.h>

using namespace std;

//Windows only

void toClipboard(unsigned long long input, bool m64){
	stringstream strstream;
	string s;
	strstream << input;
	strstream >> s;

	printf("%d bit >> %s\n", m64?64:32, s.c_str());

	OpenClipboard(0);
	EmptyClipboard();
	HGLOBAL hg=GlobalAlloc(GMEM_MOVEABLE,s.size()+1);
	if (!hg){
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg),s.c_str(),s.size());
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT,hg);
	CloseClipboard();
	GlobalFree(hg);
}

long long unsigned FNV_1a(string str, bool m64)
{
	printf("%s\n", str.c_str());
  if (m64)
  {
    unsigned long long hash=14695981039346656037ULL;//64 bit
    for (unsigned x=0; x<str.size(); ++x)
      {
        hash^=str[x];
        hash*=0xb3;
      }

      return hash;
  }else
  {
    unsigned long hash=2166136261;//32 bit
    for (unsigned x=0; x<str.size(); ++x)
      {
        hash^=str[x];
        hash*=0x93;
      }
			printf("\n");

      return (unsigned long long) hash;
  }



	return 0;
}

int main()
{
  string usin, empty;
  do{
    printf(">>\t");
    getline(cin,usin);
    if (usin.size()==0)
      continue;

    toClipboard(FNV_1a(usin, true), true);
    getline(cin, empty);
    toClipboard(FNV_1a(usin, false), false);

  }while (usin!="_quit_");


  return 0;
}
