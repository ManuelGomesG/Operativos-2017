/* Estructuras para resolver el problema
 * Manuel Gomes 11-10375
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct _process {
  long pid;
  char status;
  short prio;
  float time;
  char command[128];
  struct _process* next;
} Proceso;

typedef struct _queue {
  struct _process* head;
  struct _process* tail;
} Cola;

typedef struct _queuestruct {
  Cola * q0;
  Cola * q1;
  Cola * q2;
  Cola * q3;
  Cola * q4;
  Cola * q5;
} EstrucSched;


Proceso *construyeProceso(long, short, float, char [128]);
Cola *construyeCola();
void encolar(Cola *, Proceso *);
Cola *seleccionarCola(EstrucSched * ,short );
void InsertarProceso(EstrucSched* , Proceso* , short );
void destruirProceso(Proceso *);
void ElimProceso(EstrucSched *, long , short);
void ElimProcesoE(EstrucSched *);
void eliminarProcs(Proceso *);
void eliminarProcesosCola(Cola *) ;
Proceso *ProxProceso(EstrucSched *);
void CambiarEstado(EstrucSched *, Proceso* , char);
EstrucSched *Construye(char *);
void imprimecola(Cola *);
void Imprime(EstrucSched *);
