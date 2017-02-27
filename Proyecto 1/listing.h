
/*
 * Manuel Gomes 11-10375
 * Estructuras para resolver el problema.
 */




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
  char name[PATH_MAX];
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
  char oname[128];
  char gname[128];
  char mdate[10];
  char adate[10];
  char path[PATH_MAX];
  struct _regfile* next;
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
  char oname[128];
  char gname[128];
  char mdate[10];
  char adate[10];
  char path[PATH_MAX];
  int files;
  int sumSize;
  struct _subDir* next;
} SubDir;


PDList* parentlist(char*);
void printPDL(PDList*);
SubDir* childlist(char*, int);
void printSD(SubDir*);
Directory* getNth(PDList*, int);
void report(SubDir*);
void preport(SubDir*);
