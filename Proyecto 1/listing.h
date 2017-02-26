




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>



#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdint.h>


typedef struct _directory  {
  char name[256];
  struct _directory* next;
} Directory;




typedef struct _parentDirList {
  struct _directory* first;
  int n;
}PDList;


typedef struct _regfile {
  char iRUSR;
  char iWUSR;
  char iXUSR;
  char iRGRP;
  char iWGRP;
  char iXGRP;
  char iROTH;
  char iWOTH;
  char iXOTH;
  char* oname;
  char* gname;
  char mdate[10];
  char adate[10];
  char* path;
  struct _file* next;
} RegFile;

typedef struct _subDir {
  struct _regfile* first;
  struct _subDir* firstSD;
  char iRUSR;
  char iWUSR;
  char iXUSR;
  char iRGRP;
  char iWGRP;
  char iXGRP;
  char iROTH;
  char iWOTH;
  char iXOTH;
  char* oname;
  char* gname;
  char mdate[10];
  char adate[10];
  char* path;
  struct _file* next;
  int files;
  int sumSize;
  struct _subDir* next;
} SubDir;


PDList* parentlist(char*);
void printPDL(PDList*);
