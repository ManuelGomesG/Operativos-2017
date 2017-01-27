/* Estructuras para resolver el problema
 * Manuel Gomes 11-10375
 */

typedef struct _process {
  long pid;
  char status;
  short prio;
  float time;
  char[128] command;
  struct _process* next;
} Proceso;

typedef struct _queue {
  struct _process* head;
  struct _process* tail;
} Cola;

typedef struct _queuestruct {
  struct _queue* q0;
  struct _queue* q1;
  struct _queue* q2;
  struct _queue* q3;
  struct _queue* q4;
  struct _queue* q5;
} EstrucSched;
