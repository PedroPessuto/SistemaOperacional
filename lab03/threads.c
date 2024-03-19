#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int count = 0;

// ==== FUNCTION ON THREAD ====
static void *func() {
  count = count + 5;
  printf("THREAD --> Valor: %d\n", count);
  return NULL;
}

int main(void) {
  count = 10;
  printf("PROCESSO PAI (ANTES DO THREAD) --> Valor: %d\n", count);

  // ==== THREAD ====
  pthread_t t;
  pthread_create(&t, NULL, func, NULL); // Cria a thread
  pthread_join(t, NULL); // Espera a thread terminar

  printf("PROCESSO PAI (DEPOIS DO THREAD) --> Valor: %d\n", count);

  exit(0);
}
