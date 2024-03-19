#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int count = 0;

static void *thread() {
  count = count + 5;
  printf("THREAD --> Valor: %d\n", count);
  return NULL;
}

int main(void) {
  count = 10;
  printf("PROCESSO PAI (ANTES DO THREAD) --> Valor: %d\n", count);

  pthread_t thread1;

  pthread_create(&thread1, NULL, thread, NULL);
  pthread_join(thread1, NULL);

  printf("PROCESSO PAI (DEPOIS DO THREAD) --> Valor: %d\n", count);

  exit(0);
}
