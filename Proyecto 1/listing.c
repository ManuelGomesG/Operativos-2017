/* Manuel Gomes 11-10375
 * Rutinas utilizadas para la resolver el problema (manejo de Estructuras y
 * de sistema de archivos
 */





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


Directory* getNth(PDList* pdl, int i) {
  if (i > (pdl -> n) - 1  || i < 0)
    perror(NULL);
  else {
    int j;
    Directory* aux = pdl -> first;
    for (j = 0; j < i; j++) {
      aux = aux -> next;
    }
    return aux;
  }
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

void printSDFiles(SubDir* sd) {
  RegFile* aux = sd -> first;
  while (aux -> next != NULL) {
    printf("-");
    printf("%c",aux -> iRUSR);
    printf("%c",aux -> iWUSR);
    printf("%c",aux -> iXUSR);
    printf("%c",aux -> iRGRP);
    printf("%c",aux -> iWGRP);
    printf("%c",aux -> iXGRP);
    printf("%c",aux -> iROTH);
    printf("%c",aux -> iWOTH);
    printf("%c",aux -> iXOTH);

    printf(" %s", aux -> oname);
    printf(" %s", aux -> gname);

    printf(" %s", aux -> mdate );
    printf(" %s", aux -> adate );


    printf(" %s\n", aux -> path);
    aux = aux -> next;
  }
  printf("-");
  printf("%c",aux -> iRUSR);
  printf("%c",aux -> iWUSR);
  printf("%c",aux -> iXUSR);
  printf("%c",aux -> iRGRP);
  printf("%c",aux -> iWGRP);
  printf("%c",aux -> iXGRP);
  printf("%c",aux -> iROTH);
  printf("%c",aux -> iWOTH);
  printf("%c",aux -> iXOTH);

  printf(" %s", aux -> oname);
  printf(" %s", aux -> gname);

  printf(" %s", aux -> mdate );
  printf(" %s", aux -> adate );


  printf(" %s\n", aux -> path);
}


void printSD(SubDir*  sd) {
  printf("d");
  printf("%c",sd -> iRUSR);
  printf("%c",sd -> iWUSR);
  printf("%c",sd -> iXUSR);
  printf("%c",sd -> iRGRP);
  printf("%c",sd -> iWGRP);
  printf("%c",sd -> iXGRP);
  printf("%c",sd -> iROTH);
  printf("%c",sd -> iWOTH);
  printf("%c",sd -> iXOTH);

  printf(" %s", sd -> oname);
  printf(" %s", sd -> gname);

  printf(" %s", sd -> mdate);
  printf(" %s", sd -> adate);

  printf(" %d", sd -> files);
  printf(" %d", sd -> sumSize);

  printf(" %s \n", sd -> path);

  if (sd -> first != NULL)
    printSDFiles(sd);


  if (sd -> firstSD == NULL)
    return;
  else{
    SubDir* aux = sd -> firstSD;
    while (aux -> next != NULL) {
      printSD(aux);
      aux = aux -> next;
    }
    printSD(aux);
  }
}



void addFileToSubDir(SubDir* sd, char iRUSR, char iWUSR, char iXUSR, char iRGRP, char iWGRP,
  char iXGRP, char iROTH, char iWOTH, char iXOTH,char oname[128],char gname[128],
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


        }
        closedir(directory);
        return pdl;
    }
    else{
        perror(NULL);
    }
}

SubDir* createSD(char iRUSR, char iWUSR, char iXUSR, char iRGRP, char iWGRP,
  char iXGRP, char iROTH, char iWOTH, char iXOTH,char oname[128],char gname[128],
  char mdate[10], char adate[10], char* path) {
    SubDir* sd = (SubDir*)malloc(sizeof(SubDir));
    sd -> first = NULL;
    sd -> firstSD = NULL;
    sd -> iRUSR = iRUSR;
    sd -> iWUSR = iWUSR;
    sd -> iXUSR = iXUSR;
    sd -> iRGRP = iRGRP;
    sd -> iWGRP = iWGRP;
    sd -> iXGRP = iXGRP;
    sd -> iROTH = iROTH;
    sd -> iWOTH = iWOTH;
    sd -> iXOTH = iXOTH;
    strcpy(sd -> oname, oname);
    strcpy(sd -> gname, gname);
    strcpy(sd -> mdate, mdate);
    strcpy(sd -> adate, adate);
    strcpy(sd -> path, path);
    return sd;
  }

SubDir* childlist(char* path, int seg){
    DIR * directory;
    char mdate[10];
    char adate[10];
    struct stat dirstats;
    stat(path, &dirstats);
    struct group *grp;
    struct passwd *pwd;

    pwd = getpwuid(dirstats.st_uid);
    grp = getgrgid(dirstats.st_gid);
    strftime(mdate, 20, "%d-%m-%y", localtime(&(dirstats.st_mtime)));
    strftime(adate, 20, "%d-%m-%y", localtime(&(dirstats.st_atime)));
    SubDir* sd = createSD(
      (dirstats.st_mode & S_IRUSR) ? 'r' : '-',
      (dirstats.st_mode & S_IWUSR) ? 'w' : '-',
      (dirstats.st_mode & S_IXUSR) ? 'x' : '-',
      (dirstats.st_mode & S_IRGRP) ? 'r' : '-',
      (dirstats.st_mode & S_IWGRP) ? 'w' : '-',
      (dirstats.st_mode & S_IXGRP) ? 'x' : '-',
      (dirstats.st_mode & S_IROTH) ? 'r' : '-',
      (dirstats.st_mode & S_IWOTH) ? 'w' : '-',
      (dirstats.st_mode & S_IXOTH) ? 'x' : '-',
      (pwd -> pw_name),
      (grp -> gr_name),
      mdate,
      adate,
      path);
    struct dirent *filei;
    struct stat stats;
    directory = opendir(path);
    int size = 0;
    int n = 0;
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
              addSubDir(sd,childlist((buf),0));



            }
          else {

            n++;
            //printf("size %d blksize %d \n", stats.st_blocks, stats.st_blksize );
            size = size+stats.st_size;
            pwd = getpwuid(stats.st_uid);
            grp = getgrgid(stats.st_gid);
            strftime(mdate, 20, "%d-%m-%y", localtime(&(stats.st_mtime)));
            strftime(adate, 20, "%d-%m-%y", localtime(&(stats.st_atime)));
            addFileToSubDir(sd,
             (stats.st_mode & S_IRUSR) ? 'r' : '-',
             (stats.st_mode & S_IWUSR) ? 'w' : '-',
             (stats.st_mode & S_IXUSR) ? 'x' : '-',
             (stats.st_mode & S_IRGRP) ? 'r' : '-',
             (stats.st_mode & S_IWGRP) ? 'w' : '-',
             (stats.st_mode & S_IXGRP) ? 'x' : '-',
             (stats.st_mode & S_IROTH) ? 'r' : '-',
             (stats.st_mode & S_IWOTH) ? 'w' : '-',
             (stats.st_mode & S_IXOTH) ? 'x' : '-',
             pwd->pw_name,
             grp->gr_name,
             mdate,
             adate,
             buf);
          }

          free(buf);
        }
        sd -> files = n;
        sd -> sumSize = size;
        closedir(directory);
        if (seg == 1) {
          printSD(sd);
        }
        return sd;
    }
    else{
        perror(NULL);
    }
}

void report(SubDir* sd ) {
  FILE* fp;
  char* token;
  char aux[PATH_MAX];
  token = strtok(sd -> path, SEPARATOR);
  strcpy(aux,token);
  while (token != NULL) {
    token = strtok(NULL, SEPARATOR);
    if (token == NULL)
      break;
    strcpy(aux,token);
  }
  char *buf = malloc(strlen("/tmp")+strlen(aux)+2);
  strcpy(buf,"/tmp/");
  strcat(buf,aux);
  fp = fopen(buf,"w");

  fprintf(fp, "d");
  fprintf(fp, "%c",sd -> iRUSR);
  fprintf(fp, "%c",sd -> iWUSR);
  fprintf(fp, "%c",sd -> iXUSR);
  fprintf(fp, "%c",sd -> iRGRP);
  fprintf(fp, "%c",sd -> iWGRP);
  fprintf(fp, "%c",sd -> iXGRP);
  fprintf(fp, "%c",sd -> iROTH);
  fprintf(fp, "%c",sd -> iWOTH);
  fprintf(fp, "%c",sd -> iXOTH);

  fprintf(fp, " %s", sd -> oname);
  fprintf(fp, " %s", sd -> gname);

  fprintf(fp, " %s", sd -> mdate);
  fprintf(fp, " %s", sd -> adate);

  fprintf(fp, " %d", sd -> files);
  fprintf(fp, " %d", sd -> sumSize);

  fprintf(fp, " %s \n", sd -> path);

  if (sd -> firstSD == NULL)
    return;
  else{
    SubDir* aux = sd -> firstSD;
  while (aux -> next != NULL) {
    fprintf(fp, "d");
    fprintf(fp, "%c",aux -> iRUSR);
    fprintf(fp, "%c",aux -> iWUSR);
    fprintf(fp, "%c",aux -> iXUSR);
    fprintf(fp, "%c",aux -> iRGRP);
    fprintf(fp, "%c",aux -> iWGRP);
    fprintf(fp, "%c",aux -> iXGRP);
    fprintf(fp, "%c",aux -> iROTH);
    fprintf(fp, "%c",aux -> iWOTH);
    fprintf(fp, "%c",aux -> iXOTH);

    fprintf(fp, " %s", aux -> oname);
    fprintf(fp, " %s", aux -> gname);

    fprintf(fp, " %s", aux -> mdate);
    fprintf(fp, " %s", aux -> adate);

    fprintf(fp, " %d", aux -> files);
    fprintf(fp, " %d", aux -> sumSize);

    fprintf(fp, " %s \n", aux -> path);

    aux = aux -> next;
  }
  fprintf(fp, "d");
  fprintf(fp, "%c",aux -> iRUSR);
  fprintf(fp, "%c",aux -> iWUSR);
  fprintf(fp, "%c",aux -> iXUSR);
  fprintf(fp, "%c",aux -> iRGRP);
  fprintf(fp, "%c",aux -> iWGRP);
  fprintf(fp, "%c",aux -> iXGRP);
  fprintf(fp, "%c",aux -> iROTH);
  fprintf(fp, "%c",aux -> iWOTH);
  fprintf(fp, "%c",aux -> iXOTH);

  fprintf(fp, " %s", aux -> oname);
  fprintf(fp, " %s", aux -> gname);

  fprintf(fp, " %s", aux -> mdate);
  fprintf(fp, " %s", aux -> adate);

  fprintf(fp, " %d", aux -> files);
  fprintf(fp, " %d", aux -> sumSize);

  fprintf(fp, " %s \n", aux -> path);
  }
  fclose(fp);
  free(buf);

}


void preport(SubDir* sd ) {
  FILE* fp;
  char* token;
  char aux[PATH_MAX];
  token = strtok(sd -> path, SEPARATOR);
  strcpy(aux,token);
  while (token != NULL) {
    token = strtok(NULL, SEPARATOR);
    if (token == NULL)
      break;
    strcpy(aux,token);
  }


  fp = fopen(aux,"w");

  fprintf(fp, "d");
  fprintf(fp, "%c",sd -> iRUSR);
  fprintf(fp, "%c",sd -> iWUSR);
  fprintf(fp, "%c",sd -> iXUSR);
  fprintf(fp, "%c",sd -> iRGRP);
  fprintf(fp, "%c",sd -> iWGRP);
  fprintf(fp, "%c",sd -> iXGRP);
  fprintf(fp, "%c",sd -> iROTH);
  fprintf(fp, "%c",sd -> iWOTH);
  fprintf(fp, "%c",sd -> iXOTH);

  fprintf(fp, " %s", sd -> oname);
  fprintf(fp, " %s", sd -> gname);

  fprintf(fp, " %s", sd -> mdate);
  fprintf(fp, " %s", sd -> adate);

  fprintf(fp, " %d", sd -> files);
  fprintf(fp, " %d", sd -> sumSize);

  fprintf(fp, " %s \n", sd -> path);

  if (sd -> firstSD == NULL)
    return;
  else{
    SubDir* aux = sd -> firstSD;
  while (aux -> next != NULL) {
    fprintf(fp, "d");
    fprintf(fp, "%c",aux -> iRUSR);
    fprintf(fp, "%c",aux -> iWUSR);
    fprintf(fp, "%c",aux -> iXUSR);
    fprintf(fp, "%c",aux -> iRGRP);
    fprintf(fp, "%c",aux -> iWGRP);
    fprintf(fp, "%c",aux -> iXGRP);
    fprintf(fp, "%c",aux -> iROTH);
    fprintf(fp, "%c",aux -> iWOTH);
    fprintf(fp, "%c",aux -> iXOTH);

    fprintf(fp, " %s", aux -> oname);
    fprintf(fp, " %s", aux -> gname);

    fprintf(fp, " %s", aux -> mdate);
    fprintf(fp, " %s", aux -> adate);

    fprintf(fp, " %d", aux -> files);
    fprintf(fp, " %d", aux -> sumSize);

    fprintf(fp, " %s \n", aux -> path);

    aux = aux -> next;
  }
  fprintf(fp, "d");
  fprintf(fp, "%c",aux -> iRUSR);
  fprintf(fp, "%c",aux -> iWUSR);
  fprintf(fp, "%c",aux -> iXUSR);
  fprintf(fp, "%c",aux -> iRGRP);
  fprintf(fp, "%c",aux -> iWGRP);
  fprintf(fp, "%c",aux -> iXGRP);
  fprintf(fp, "%c",aux -> iROTH);
  fprintf(fp, "%c",aux -> iWOTH);
  fprintf(fp, "%c",aux -> iXOTH);

  fprintf(fp, " %s", aux -> oname);
  fprintf(fp, " %s", aux -> gname);

  fprintf(fp, " %s", aux -> mdate);
  fprintf(fp, " %s", aux -> adate);

  fprintf(fp, " %d", aux -> files);
  fprintf(fp, " %d", aux -> sumSize);

  fprintf(fp, " %s \n", aux -> path);
  }
  fclose(fp);
}
