




#include "listing.h"



#define SEPARATOR "/"





Directory* createDir(char * path) {
  Directory* d =  (Directory*)malloc(sizeof(Directory));
  strcpy(d -> name, path);
  d -> next = NULL;
}

PDList* createPDList(){
  PDList* pdl = (PDList*)malloc(sizeof(PDList));
  pdl -> first = NULL;
  pdl -> n = 0;
}

void addToPDL(PDList* pdl, Directory* d) {
  if (pdl -> first == NULL)
    pdl -> first = d;
  else {
    Directory* aux = pdl -> first;
    while (aux -> next != NULL) {
      aux = aux -> next;
    }
    aux -> next = d;
  }
  pdl -> n++;
}


void printPDL(PDList* pdl) {
  Directory* aux = pdl -> first;
  while (aux -> next != NULL) {
    printf("%s\n", aux -> name );
    aux = aux -> next;
  }
  printf("%s\n", aux -> name );

}

addFileToSubDir(SubDir* sd, char iRUSR; char iWUSR, char iXUSR, char iRGRP, char iWGRP,
  char iXGRP, char iROTH, char iWOTH, char iXOTH,char* oname,char* gname,
  char mdate[10], char adate[10], char* path) {
    RegFile* rg = (RegFile*)malloc(sizeof(RegFile));
    rg -> iRUSR = iRUSR;
    rg -> iWUSR = iWUSR;
    rg -> iXUSR = iXUSR;
    rg -> iRGRP = iRGRP;
    rg -> iWGRP = iWGRP;
    rg -> iXGRP = iXGRP;
    rg -> iROTH = iROTH;
    rg -> iWOTH = iWOTH;
    rg -> iXOTH = iXOTH;
    strcpy(rg -> oname, oname);
    strcpy(rg -> gname, gname);
    strcpy(rg -> mdate, mdate);
    strcpy(rg -> adate, adate);
    strcpy(rg -> path, path);
    rg -> next = NULL;
    if (sd -> first == NULL)
      sd -> first = rg;
    else {
      RegFile* aux = sd -> first;
      while (aux -> next != NULL) {
        aux = aux -> next;
      }
      aux -> next = rg;
    }
}

void addSubDir(SubDir* sd, SubDir* sdn) {
  if (sd -> firstSD == NULL)
    sd -> firstSD = sdn;
  else {
    SubDir* aux = sd -> firstSD;
    while (aux -> next != NULL) {
      aux = aux -> next;
    }
    aux -> next = sdn;
  }
}

PDList* parentlist(char* path){

    DIR * directory;
    PDList* pdl = createPDList();
    struct dirent *filei;
    struct stat stats;
    directory = opendir(path);
    int size = 0;
    struct group *grp;
    struct passwd *pwd;
    //int i;
    if (directory != NULL)  {
        while ((filei=readdir(directory))!=NULL){
          if (strcmp(filei->d_name, ".") == 0 || strcmp(filei->d_name, "..") == 0)
            continue;
          stat(filei->d_name, &stats);
          char *buf = malloc(strlen(path)+strlen(filei->d_name)+2);
          strcpy(buf,path);
          strcat(buf,"/");
          strcat(buf,filei->d_name);
          if (S_ISDIR(stats.st_mode)){
              /* Añadir el directorio a una lista*/
              addToPDL(pdl, createDir(buf));



                /*
                stat(buf, &stats);
                if (S_ISDIR(stats.st_mode)) {
                    if (strcmp(filei->d_name,".")!=0 && (strcmp(filei->d_name,"..")!=0)) {
                        list(buf);
                    }
                free(buf);
              }*/
            }
          else {
            printf( (S_ISDIR(stats.st_mode)) ? "d" : "-");
            printf( (stats.st_mode & S_IRUSR) ? "r" : "-");
            printf( (stats.st_mode & S_IWUSR) ? "w" : "-");
            printf( (stats.st_mode & S_IXUSR) ? "x" : "-");
            printf( (stats.st_mode & S_IRGRP) ? "r" : "-");
            printf( (stats.st_mode & S_IWGRP) ? "w" : "-");
            printf( (stats.st_mode & S_IXGRP) ? "x" : "-");
            printf( (stats.st_mode & S_IROTH) ? "r" : "-");
            printf( (stats.st_mode & S_IWOTH) ? "w" : "-");
            printf( (stats.st_mode & S_IXOTH) ? "x" : "-");

            pwd = getpwuid(stats.st_uid);
            printf(" %s", pwd->pw_name);
            grp = getgrgid(stats.st_gid);
            printf(" %s", grp->gr_name);
            char date[10];
            strftime(date, 20, "%d-%m-%y", localtime(&(stats.st_mtime)));
            printf(" %s ", date );
            strftime(date, 20, "%d-%m-%y", localtime(&(stats.st_atime)));
            printf(" %s ", date );


            printf(" %s  ", buf);
            printf("\n");
          }

        }
        closedir(directory);
        return pdl;
    }
    else{
        perror(NULL);
    }
}



SubDir* childlist(char* path){

    DIR * directory;
    char mdate[10];
    char adate[10];
    SubDir* sd = createPDList();
    struct dirent *filei;
    struct stat stats;
    directory = opendir(path);
    int size = 0;
    int n = 0;
    struct group *grp;
    struct passwd *pwd;
    //int i;
    if (directory != NULL)  {
        while ((filei=readdir(directory))!=NULL){
          if (strcmp(filei->d_name, ".") == 0 || strcmp(filei->d_name, "..") == 0)
            continue;
          stat(filei->d_name, &stats);
          char *buf = malloc(strlen(path)+strlen(filei->d_name)+2);
          strcpy(buf,path);
          strcat(buf,"/");
          strcat(buf,filei->d_name);
          if (S_ISDIR(stats.st_mode)){
              /* Añadir el directorio a una lista*/
              addSubDir(sd,childlist(buf));



                /*
                stat(buf, &stats);
                if (S_ISDIR(stats.st_mode)) {
                    if (strcmp(filei->d_name,".")!=0 && (strcmp(filei->d_name,"..")!=0)) {
                        list(buf);
                    }
                free(buf);
              }*/
            }
          else {


            n++;
            size = size +(stats.st_blocks/stats.st_blksize);
            pwd = getpwuid(stats.st_uid);
            grp = getgrgid(stats.st_gid);
            strftime(mdate, 20, "%d-%m-%y", localtime(&(stats.st_mtime)));
            strftime(adate, 20, "%d-%m-%y", localtime(&(stats.st_atime)));
            addFileToSubDir(sd,
             (stats.st_mode & S_IRUSR) ? "r" : "-",
             (stats.st_mode & S_IWUSR) ? "w" : "-",
             (stats.st_mode & S_IXUSR) ? "x" : "-",
             (stats.st_mode & S_IRGRP) ? "r" : "-",
             (stats.st_mode & S_IWGRP) ? "w" : "-",
             (stats.st_mode & S_IXGRP) ? "x" : "-",
             (stats.st_mode & S_IROTH) ? "r" : "-",
             (stats.st_mode & S_IWOTH) ? "w" : "-",
             (stats.st_mode & S_IXOTH) ? "x" : "-",
             pwd->pw_name,
             grp->gr_name,
             date,
             date,
             buf)

          }

        }
        closedir(directory);
        return pdl;
    }
    else{
        perror(NULL);
    }
}
