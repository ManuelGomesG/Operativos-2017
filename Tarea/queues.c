/* Manuel Gomes 11-10375
 * Rutinas utilizadas para la resolver el problema
 */

#include "queues.h"

Proceso *construyeProceso(long p, short pri, float t, char c[128]) {
  Proceso *proc = (Proceso*)malloc(sizeof(Proceso));
  proc -> pid = p;
  proc -> status = 'L';
  proc -> prio = pri;
  proc -> time = t;
  strcpy(proc -> command, c);
  proc -> next = NULL;
}

Cola *construyeCola() {
  Cola *q = (Cola*)malloc(sizeof(Cola));
  q -> head = NULL;
  q -> tail = NULL;
}

EstrucSched *construyeEst(){
  EstrucSched *s = (EstrucSched*)malloc(sizeof(EstrucSched));
  s -> q0 = construyeCola();
  s -> q1 = construyeCola();
  s -> q2 = construyeCola();
  s -> q3 = construyeCola();
  s -> q4 = construyeCola();
  s -> q5 = construyeCola();
}

void encolar(Cola *q, Proceso *p) {
  if (q -> head == NULL) {
    q -> head = p;
    q -> tail = p;
    p -> next = NULL;
  }
  else {
    q -> tail -> next = p;
    q -> tail = p;
  }
}

Cola *seleccionarCola(EstrucSched *s ,short n) {
  Cola *q;
  switch(n) {
    case 0 :
    q = s -> q0;
    break;
    case 1 :
    q = s -> q1;
    break;
    case 2 :
    q = s -> q2;
    break;
    case 3 :
    q = s -> q3;
    break;
    case 4 :
    q = s -> q4;
    break;
    case 5 :
    q = s -> q5;
    break;
    default :
    printf("Prioridad inválida\n" );
  }
  return q;
}

void InsertarProceso(EstrucSched* s, Proceso* p, short prioridad) {
  encolar(seleccionarCola(s, p -> prio), p);
}

void destruirProceso(Proceso *p) {
  if (p == NULL)
    return;
  free(p);
}

void ElimProceso(EstrucSched *s, long pid, short prio) {
  Cola *q = seleccionarCola(s, prio);
  Proceso *aux = q -> head;
  if (aux -> pid == pid) {
    q -> head = aux -> next;
    destruirProceso(aux);
  }
  else {
    while (aux -> next -> pid != pid) {
      if (aux -> next == NULL) {
        printf("El proceso de PID: %ld no está en la cola\n", pid);
        return;
      }
      else{
        aux = aux -> next;
      }
    }
    Proceso *aux2 = aux -> next;
    aux -> next = aux2 -> next;
    destruirProceso(aux2);
  }
}

void ElimProcesoE(EstrucSched *s) {
  Proceso *aux;
  if (s -> q0 -> head != NULL) {
    aux = s -> q0 -> head;
    if ( 'E' == (aux -> status)) {
      ElimProceso(s, aux -> pid, aux -> prio);
      return;
    }
    while (aux -> next != NULL) {
      if ( 'E' == (aux -> status)) {
        ElimProceso(s, aux -> pid, aux -> prio);
        return;
      }
    }
  }
  if (s -> q1 -> head != NULL) {
    aux = s -> q1 -> head;
    if ( 'E' == (aux -> status)) {
      ElimProceso(s, aux -> pid, aux -> prio);
      return;
    }
    while (aux -> next != NULL) {
      if ( 'E' == (aux -> status)) {
        ElimProceso(s, aux -> pid, aux -> prio);
        return;
      }
    }
  }
  if (s -> q2 -> head != NULL) {
    aux = s -> q2 -> head;
    if ( 'E' == (aux -> status)) {
      ElimProceso(s, aux -> pid, aux -> prio);
      return;
    }
    while (aux -> next != NULL) {
      if ( 'E' == (aux -> status)) {
        ElimProceso(s, aux -> pid, aux -> prio);
        return;
      }
    }
  }
  if (s -> q3 -> head != NULL) {
    aux = s -> q3 -> head;
    if ( 'E' == (aux -> status)) {
      ElimProceso(s, aux -> pid, aux -> prio);
      return;
    }
    while (aux -> next != NULL) {
      if ( 'E' == (aux -> status)) {
        ElimProceso(s, aux -> pid, aux -> prio);
        return;
      }
    }
  }
  if (s -> q4 -> head != NULL) {
    aux = s -> q4 -> head;
    if ( 'E' == (aux -> status)) {
      ElimProceso(s, aux -> pid, aux -> prio);
      return;
    }
    while (aux -> next != NULL) {
      if ( 'E' == (aux -> status)) {
        ElimProceso(s, aux -> pid, aux -> prio);
        return;
      }
    }
  }
  if (s -> q5 -> head != NULL) {
    aux = s -> q5 -> head;
    if ( 'E' == (aux -> status)) {
      ElimProceso(s, aux -> pid, aux -> prio);
      return;
    }
    while (aux -> next != NULL) {
      if ( 'E' == (aux -> status)) {
        ElimProceso(s, aux -> pid, aux -> prio);
        return;
      }
    }
  }

}

void eliminarProcs(Proceso *p) {
  if (p -> next != NULL)
    eliminarProcs(p -> next);
  destruirProceso(p);
}


void eliminarProcesosCola(Cola *q)  {
  eliminarProcs(q -> head);
  free(q);
}


Proceso *ProxProceso(EstrucSched *s) {
  Proceso *aux;
  if (s -> q0 -> head != NULL) {
    aux = s -> q0 -> head;
    s -> q0 -> head = aux -> next;
    encolar(s -> q0, aux);
    CambiarEstado(s, aux, 'E');
    return s -> q0 -> tail;
  }
  else if (s -> q1 -> head != NULL) {
    aux = s -> q1 -> head;
    s -> q1 -> head = aux -> next;
    encolar(s -> q1, aux);
    CambiarEstado(s, aux, 'E');
    return s -> q1 -> tail;
  }
  else if (s -> q2 -> head != NULL) {
    aux = s -> q2 -> head;
    s -> q2 -> head = aux -> next;
    encolar(s -> q2, aux);
    CambiarEstado(s, aux, 'E');
    return s -> q2 -> tail;
  }
  else if (s -> q3 -> head != NULL) {
    aux = s -> q3 -> head;
    s -> q3 -> head = aux -> next;
    encolar(s -> q3, aux);
    CambiarEstado(s, aux, 'E');
    return s -> q3 -> tail;
  }
  else if (s -> q4 -> head != NULL) {
    aux = s -> q4 -> head;
    s -> q4 -> head = aux -> next;
    encolar(s -> q4, aux);
    CambiarEstado(s, aux, 'E');
    return s -> q4 -> tail;
  }
  else if (s -> q5 -> head != NULL) {
    aux = s -> q5 -> head;
    s -> q5 -> head = aux -> next;
    encolar(s -> q5, aux);
    CambiarEstado(s, aux, 'E');
    return s -> q5 -> tail;
  }
  else {
    printf("No hay procesos en la estructura\n");
    return NULL;
  }
}



void CambiarEstado(EstrucSched *s, Proceso* p, char newestado) {
  p -> status = newestado;
  /* Si me dan un apuntador al proceso no necesito la estructura o las colas*/
}

EstrucSched *Construye(char *filename) {
  FILE *file;
  char *line = NULL;
  size_t len;
  char read;
  file=fopen(filename, "r");
  char *words;
  int i;
  char *eptr;

  EstrucSched *s = construyeEst();
  long auxpid;
  char auxstatus;
  short auxprio;
  float auxtime;
  char auxcommand[128];

  if (file == NULL) {
    printf("Error al abrir el archivo de entrada.\n");
    return NULL;
  }

  while ((read = getline(&line, &len, file)) != -1) {
      words = strtok(line," ");
      i = 0;
      while (words != NULL) {
        if (i == 0)
          auxpid = strtol(words, &eptr, 10);
        else if (i == 2)
          auxprio = atoi(words);
        else if (i == 3)
          auxtime = atof(words);
        else if (i == 4)
          strcpy(auxcommand,words);
        else if (i > 4)
          break;
        i++;

        //printf("%s\n", words);
        words = strtok(NULL, " ");
      }

      encolar(seleccionarCola(s, auxprio), construyeProceso(auxpid, auxprio,
                                          auxtime, auxcommand));
  }

  if (line)
      free(line);
  fclose(file);
  return s;


}

void imprimecola(Cola * q) {
  if (q -> head == NULL) {
    return;
  }
  else {
    Proceso *aux = q -> head;
    printf(" %ld %c %d %f %s  ", aux -> pid, aux -> status, aux -> prio,
                                      aux -> time, aux -> command);
    while (aux -> next != NULL) {
      aux = aux -> next;
      printf(" %ld %c %d %f %s  ", aux -> pid, aux -> status, aux -> prio,
                                        aux -> time, aux -> command);
    }
    printf("\n");
  }
}


void Imprime(EstrucSched *s ) {
  EstrucSched * aux =  s;
  printf("Cola q0:  \n" );
  imprimecola(aux -> q0);
  printf("Cola q1:  \n" );
  imprimecola(aux -> q1);
  printf("Cola q2:  \n" );
  imprimecola(aux -> q2);
  printf("Cola q3:  \n" );
  imprimecola(aux -> q3);
  printf("Cola q4:  \n" );
  imprimecola(aux -> q4);
  printf("Cola q5:  \n" );
  imprimecola(aux -> q5);
}
