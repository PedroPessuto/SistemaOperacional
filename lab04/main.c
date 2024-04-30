#include <pthread.h>
#include <stdio.h>

int m[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
int v[3] = {1, 2, 3};
int r[3] = {0};

void *calc(void *arg) {
  int *posicao = (int *)arg;
  for (int j = 0; j < 3; j++) {
    r[*posicao] += m[*posicao][j] * v[j];
  }
  return NULL;
}

int main() {
  pthread_t pid[3];

  for (int i = 0; i < 3; i++) {
    pthread_create(&pid[i], NULL, calc, &i);
    pthread_join(pid[i], NULL);
  }

  printf("Resultado: ");
  for (int i = 0; i < 3; i++) {
    printf("%d ", r[i]);
  }

  return 0;
}
