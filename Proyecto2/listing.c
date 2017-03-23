#include "listing.h"


Directory* createUDir(char * path) {
  Directory* d =  (Directory*)malloc(sizeof(Directory));
  strcpy(d -> name, path);
  d -> next = NULL;
  return d;
}

ExploredDirectory* createEDir(char * path, long s, long t, long f) {
  ExploredDirectory* d =  (ExploredDirectory*)malloc(sizeof(ExploredDirectory));
  strcpy(d -> name, path);
  d -> size = s;
  d -> tid = t;
  d -> files = f;
  d -> next = NULL;
  return d;
}


ToExplore* createToEList(){
  ToExplore* te = (ToExplore*)malloc(sizeof(ToExplore));
  te -> first = NULL;
  return te;
}

Explored* createEList(){
  Explored* e = (Explored*)malloc(sizeof(Explored));
  e -> first = NULL;
  return e;
}

void addExplored(ExploredDirectory* ed, Explored* e) {
  if (e -> first == NULL)
    e -> first = ed;
  else {
    ExploredDirectory* aux = e -> first;
    while (aux -> next != NULL) {
      aux = aux -> next;
    }
    aux -> next = ed;
  }
}



void addToExplore(Directory* d, ToExplore* te) {
  if (te -> first == NULL)
    te -> first = d;
  else {
    Directory* aux = te -> first;
    while (aux -> next != NULL) {
      aux = aux -> next;
    }
    aux -> next = d;
  }
}

Directory* popFromToExplore(ToExplore* te){
  Directory* aux = te -> first;
  te -> first = te -> first -> next;
  return aux;
}


ExploredDirectory* popFromExplored(Explored* e){
  ExploredDirectory* aux = e -> first;
  e -> first = e -> first -> next;
  return aux;
}

void printExplored(Explored* e) {
  ExploredDirectory* aux = e -> first;
  while (aux -> next != NULL) {
    printf("%s  ", aux -> name);
    printf("%ld  ", aux -> size);
    printf("%ld  ", aux -> files);
    printf("%ld\n", aux -> tid);
    aux = aux -> next;
  }
  printf("%s  ", aux -> name);
  printf("%ld  ", aux -> size);
  printf("%ld  ", aux -> files);
  printf("%ld\n", aux -> tid);
}

void printToExplore(ToExplore* e) {
  Directory* aux = e -> first;
  while (aux -> next != NULL) {
    printf("%s  ", aux -> name);
    aux = aux -> next;
  }
  printf("%s  ", aux -> name);
}



void parentlist(char* path, ToExplore* tel, Explored* el){
    DIR * directory;
    struct dirent *filei;
    struct stat stats;
    directory = opendir(path);
    int n = 0;
    int size = 0;
    if (directory != NULL)  {
        while ((filei=readdir(directory))!=NULL){
          if (strcmp(filei->d_name, ".") == 0 || strcmp(filei->d_name, "..") == 0)
            continue;
          stat(filei->d_name, &stats);
          char *buf = malloc(strlen(path)+strlen(filei->d_name)+2);
          strcpy(buf,path);
          strcat(buf,"/");
          strcat(buf,filei->d_name);
          if (S_ISDIR(stats.st_mode))
            addToExplore(createUDir(buf), tel);
          else{
            n++;
            size = size +  stats.st_size;
          }
        }
        closedir(directory);
        addExplored(createEDir(path,size,0,n),el);
    }
    else{
        perror(NULL);
    }
}
