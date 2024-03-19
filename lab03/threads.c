#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char var = 'A';

// ==== FUNCTION ON THREAD ====
static void *func() {
  var = 'C';
  printf("THREAD --> Valor: %c\n", var);
  return NULL;
}

int main(void) {
   var = 'B';
  printf("PROCESSO PAI (ANTES DO THREAD) --> Valor: %c\n", var);

  // ==== THREAD ====
  pthread_t t;
  pthread_create(&t, NULL, func, NULL); // Cria a thread
  pthread_join(t, NULL); // Espera a thread terminar

  printf("PROCESSO PAI (DEPOIS DO THREAD) --> Valor: %c\n", var);

  exit(0);
}
