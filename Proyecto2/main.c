#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
int nthreads = 1;
char* dir = ".";
int hflag = 0;
int oflag = 0;
int errflag = 0;
int option = 0;
int h = 0;
char *output;

while ((option = getopt(argc, argv,"hn:d:")) != -1) {
  switch (option) {
  case 'h' : h++;

    if (oflag)
      errflag++;
    else
      hflag++;
    break;
  case 'n' : nthreads = atoi(optarg);
    if (hflag)
      errflag++;
    else
      oflag++;
    break;
  case 'd' : dir = optarg;
    if (hflag)
      errflag++;
    else
      oflag++;
  break;
  case '?': errflag++;
    }
    if (errflag) {
	   (void)fprintf(stderr,
	      "Error sintáctico (uso: tls [-h] | [-n i][-d directorio][ salida ])\n");
	   exit	(2);
   }
  }

printf("Directorio: %s\n",dir );
printf("Nthreads: %d\n",nthreads );
if (h) {
  printf("tls [-h] | [-n i] [-d directorio] [ salida ]\n");
  printf("-n i : Nivel de concurrencia solicitado. Por defecto crea un solo\
hilo trabajador.\n");
  printf("-d directorio: Especifica un directorio desde donde revisa el\
espacio utilizado. Por defecto hace el cálculo desde el directorio\
actual.\n");
  printf("salida : Archivo que contendrá la lista de directorios y el espacio\
en bytes ocupado por los archivos regulares. Valor por defecto es\
la salida estándar.\n");
}

  output = argv[optind];
  if (output == NULL)
    printf("Salida: NULL\n");
  else
    printf("Salida: %s\n",output);
  return 0;
}
