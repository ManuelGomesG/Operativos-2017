/* Manuel Gomes 11-10375
 * Rutinas utilizadas para la resolver el problema
 */

Proceso *construyeProceso(long p, short pri, float t, char[128] c) {
  Proceso *proc = (Proceso*)malloc(sizeof(Proceso));
  proc -> pid = p;
  proc -> status = 'L';
  proc -> prio = pri;
  proc -> time = t;
  proc -> command = c;
  proc -> next = NULL;
}

Cola *construyeCola() {
  Cola *q = (Cola*)malloc(sizeof(Cola));
  q -> head = NULL;
  q -> tail = NULL;
}

void encolar(Cola *q, Proceso *p) {
  if (q -> head == NULL) {
    q -> head = p;
    q -> last = p;
    p -> next = NULL;
  }
  else {
    q -> last -> next = p;
    q -> last = p;
  }
}

Cola *seleccionarCola(short n) {
  Cola *q;
  switch(p -> prio) {
    case 0 :
    q = q0;
    break;
    case 1 :
    q = q1;
    break;
    case 2 :
    q = q2;
    break;
    case 3 :
    q = q3;
    break;
    case 4 :
    q = q4;
    break;
    case 5 :
    q = q5;
    break;
    default :
    printf("Prioridad inválida\n" );
  }
  return q;
}

void InsertarProceso(EstrucSched* s, Proceso* p, short prioridad) {
  encolar(seleccionarCola(p -> prio), p);
}

void destruirProceso(Proceso *p) {
  if (p == NULL)
    return;
  free(p);
}

void ElimProceso(EstrucSched *s, long pid, short prio) {
  Cola q = seleccionarCola(prio);
  Proceso *aux = q -> head;
  if (aux -> pid == pid) {
    q -> head = aux -> next;
    destruirProceso(aux);
  }
  else {
    while (aux -> next -> pid != pid) {
      if (aux -> next == NULL) {
        printf("El proceso de PID:%d no está en la cola\n", pid);
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
  /* Buscar en todo? al final de cada cola? como funciona el cambio de estado,
  o como salen de ejecucion los procesos*/
}



EstrucSched *Construye(char *filename) {

}
