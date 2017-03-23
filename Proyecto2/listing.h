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
#define SEPARATOR "/"


typedef struct _directory  {
  char name[PATH_MAX];
  struct _directory* next;
} Directory;

typedef struct _toExplore {
  struct _directory* first;
}ToExplore;

typedef struct _exploredDirectory {
  char name[PATH_MAX];
  struct _exploredDirectory* next;
  long size;
  long tid;
  long files;
} ExploredDirectory;

typedef struct _explored {
  struct _exploredDirectory* first;
}Explored;


void parentlist(char* , ToExplore*, Explored*);
ToExplore* createToEList();
Explored* createEList();
void printExplored(Explored*);
void printToExplore(ToExplore*);
