/*
 * Manuel Gomes 11-10375
 * Archivo con el flujo principal del programa.
 */



#include <signal.h>
#include "listing.h"

int main(int argc, char const *argv[]) {

  signal(SIGINT, SIG_IGN);
  char *currentp = ".";
  char actualpath [PATH_MAX];
  char *ptr;
  int i;
  ptr = realpath(currentp, actualpath);

  PDList* pdl;
  pdl=parentlist(ptr);

  int pipes[pdl -> n][2];
  for (i = 0; i < pdl -> n ; i++) {
    close(pipes[i][1]);
  }
  SubDir* sdp = childlist(ptr, 1);
  pid_t childpid;
  for (i = 0; i < pdl -> n; i++) {
    if ((childpid = fork()) < 0) {
      perror("fork:");
      exit(1);
    }
    if (childpid == 0) { // Lo que hacen los hijos
      //printf("Soy el hijo con pid %d\n", i);
      close(pipes[i][0]);
      SubDir* sd = childlist(getNth(pdl,i) -> name, 0);
      report(sd);
      write(pipes[i][1],sd,sizeof(SubDir));
      //printSD(sd);
      exit(0);
    }
 }
  if (childpid != 0) { //padre
    SubDir* bsd[pdl -> n];
    for (i = 0; i < pdl -> n; i++) {
      read(pipes[i][0],bsd[i],sizeof(SubDir));
    }
    preport(sdp);
  }

  //}



  return 0;
}
