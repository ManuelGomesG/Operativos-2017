/*Universidad Simón Bolívar
 * Manuel Gomes 11-10375
 * Código del programa principal.
 */


#include "queues.h"

void imprimirOpciones(){
  printf("Para insertar un proceso ingrese 1.\n");
  printf("Para eliminar un proceso ingrese 2.\n");
  printf("Para cambiar el estado del proceso que está en ejecución ingrese 3.\n");
  printf("Para imprimir el contenido de la estructura de datos ingrese 4.\n");
  printf("Para salir ingrese 5.\n");

}



int main(int argc, char *argv[]) {
  Proceso *ejecutando;
  short op;
  long auxpid;
  //char auxstatus;
  short auxprio;
  float auxtime;
  char auxcommand[128];
  Proceso *auxproc;
  EstrucSched *s = Construye(argv[1]);
  ejecutando = ProxProceso(s);
  while (1) {
    imprimirOpciones();
    scanf("%hu", &op);
    if (op == 1) {
      printf("Ingrese el PID del proceso.\n");
      scanf(" %ld", &auxpid);
      //printf("%ld \n", auxpid );
      printf("Ingrese la prioridad del proceso.\n");
      scanf(" %hu", &auxprio);
      printf("Ingrese el tiempo de ejecución del proceso.\n");
      scanf(" %f", &auxtime);
      printf("Ingrese el nombre del proceso o comando.\n");
      scanf(" %s", auxcommand);
      auxproc = construyeProceso(auxpid, auxprio, auxtime, auxcommand);
      InsertarProceso(s, auxproc, auxprio);
    }
    else if ( op == 2 ) {
      printf("Para eliminar proceso en ejecución ingrese 1.\n");
      printf("Para eliminar otro proceso ingrese 2.\n");
      scanf(" %hu", &op);
      if ( op == 2 ) {
        printf("Ingrese el PID del proceso.\n");
        scanf(" %ld", &auxpid);
        printf("Ingrese la prioridad del proceso\n");
        scanf(" %hu", &auxprio);
        ElimProceso(s, auxpid, auxprio);
      }
      else if ( op == 1 ) {
        ElimProcesoE(s);
        ejecutando = ProxProceso(s);
      }
      else
        printf("Opción inválida.\n" );
    }
    else if (op == 3) {
      CambiarEstado(s, ejecutando, 'L');
      ejecutando = ProxProceso(s);
    }
    else if (op == 4) {
      Imprime(s);
    }
    else if (op == 5) {
      FILE *fp = fopen(argv[2], "w");
      imprimeArchivo(s, fp);
      fclose(fp);
      eliminarEst(s);
      break;

    }
  }
  return 0;
}
