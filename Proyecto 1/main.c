



#include "listing.h"

int main(int argc, char const *argv[]) {


  char *currentp = ".";
  char actualpath [PATH_MAX];
  char *ptr;
  ptr = realpath(currentp, actualpath);

  PDList* pdl;
  pdl=parentlist(ptr);
  printf("PDL: \n");
  printPDL(pdl);
  printf(" kasjndksjandkas :%d\n",pdl -> n );
  return 0;
}
