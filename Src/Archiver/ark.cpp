#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

//global
string outputName;
string tableFile;
string objectFile;
string outputPath;

#define VERSION "1.0.0\0"

bool tSpec=false;//table file specified
bool lSpec=false;//library file specified
bool nSpec=false;//output file name specified
bool doValidate=false;
bool debug=false;
bool fatal=false;

void help()
{
printf("HELP\n\n");
printf("-v : Display program version\n");
printf("-h : Display this dialogue. Glad to be of assistance.\n");
printf("-c : Do a table validity check (TODO)\n");
printf("-d : Print operations for debugging\n");
printf("-t : Set table file\n");
printf("-l : Set library function\n");
printf("-n : Set output name\n");
printf("-p : Set output path\n");
}

string getExtension(string input)
{
  int index = input.find_last_of(".", 0);
  if (index==string::npos)
    return input;

  string output(input.begin()+index, input.end());
  return output;
}

void setExtension(string&input)
{
  printf("^^%s\n",input.c_str());

  if (getExtension(input)==".ark")
    return;
  int index = input.find_last_of(".", 0);
  if (index==string::npos)
    input+=".ark";
  else
  {
    input.erase(input.begin()+index, input.end()-1);
    input+=".ark";
  }

}

string getFileName(string input)
{
  int index = input.find(".", 0);
  if (index==string::npos)
    return input;

  string output(input.begin(), input.begin()+index-1);
  return output;
}

bool isValidName(string name)
{
  for (unsigned x=0; x<name.size(); ++x)
    if (!((name[x] >='A' && name[x]<='Z') || (name[x] >='a' && name[x]<='z') || (name[x] >='0' && name[x]<='9' && x>0) || name[x]=='_'))
      return false;
  return true;
}

void getCmd(int argc, char**argv)
{
for (unsigned x=1; x<argc; ++x)
  {
    if (argv[x][0]=='-')
    {
      if (strlen(argv[x])<2)
        {
          printf("Blank option\n");
          fatal=true;
        }
      switch(argv[x][1])
      {
        case 'v': printf("%s\n",VERSION);break;
        case 'h': help(); break;
        case 'c': doValidate=true;break;
        case 'd': debug=true;break;
        case 'p':
        if (x+1==argc)
          {
            printf("Missing argument\n");
            fatal=true;
          }
          else
            outputPath=argv[++x];
        break;
        case 't':
          if (x+1==argc)
            {
              printf("Missing argument\n");
              fatal=true;
            }
          else if (tSpec)
          {
            printf("Table file already defined\n");
            fatal=true;
          }
          else
            {
              tableFile=argv[++x];
              tSpec=true;
            }
          break;
          case 'l':
          if (x+1==argc)
            {
              printf("Missing argument\n");
              fatal=true;
            }else if (lSpec)
            {
              printf("Object file file already defined\n");
              fatal=true;
            }
            else
              {
                objectFile=argv[++x];
                lSpec=true;
              }
          break;
          case 'n':
          if (x+1==argc)
            {
              printf("Missing argument\n");
              fatal=true;
            }
          else if (nSpec)
          {
            printf("Output file file already defined\n");
            fatal=true;
          }
          else
            {
              outputName=argv[++x];
              nSpec=true;
            }
          break;
      }
    }
  }
}

int main(int argc, char**argv)
{

getCmd(argc, argv);

if (fatal)
  {
    printf("Unable to continue. Terminating\n");
    exit(-1);
  }

  if (tSpec ^ lSpec)
  {
    printf("Both the table and object file must be defined\n");
    exit(1);
  }

if (tSpec && lSpec)
{
  printf("%s~%s\n", tableFile.c_str(), objectFile.c_str());

  ifstream tblFle(tableFile);
  ifstream objFle(objectFile);

  if (!tblFle)
  {
    printf("Table file not found: %s\n", tableFile.c_str());
    exit(1);
  }

  if (!objFle)
  {
    printf("Object file not found: %s\n", tableFile.c_str());
    exit(1);
  }

  //create output file
  string out=nSpec?outputPath+outputName:outputPath+getFileName(objectFile);
  setExtension(out);
  ofstream outFile(out,ios::out);
  printf(">> %s\n", out.c_str());
  if (!outFile)
    {
      printf("Failed to generate path %s\n", out.c_str());
      exit(1);
    }
  //begin writing
  while(!tblFle.eof())
  {
    printf("...");
    string buffer;
    getline(tblFle, buffer);

    if (debug)
      printf("%s >> %s\n", tableFile.c_str(), buffer.c_str());

    if (buffer.size()==0)
      continue;
    if (buffer[0]=='#')
      continue;

    outFile<<buffer;
  }

  outFile<<endl;

  while(!objFle.eof())
  {
    string buffer;
    getline(objFle, buffer);

    if (debug && 0)
      printf("%s >> %s\n", objectFile.c_str(), buffer.c_str());

    outFile<<buffer<<endl;
  }

  tblFle.close();
  objFle.close();
}


return 0;
}
