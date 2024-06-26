#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct conta {
  char nome[100];
  int saldo;
};
typedef struct conta conta;

struct transacao {
  conta *recebe;
  conta *envia;
  int valor;
};
typedef struct transacao transacao;

conta conta1;
conta conta2;
pthread_mutex_t semaforo;

void *transferir(void *args) {
  transacao *t = (transacao *)args;
  pthread_mutex_lock(&semaforo);

  printf("==================================================\n");
  if (t->envia->saldo - t->valor >= 0) {
    printf("Transação de %s para %s\n", t->envia->nome, t->recebe->nome);
    printf("Valor da transação: R$ %d,00\n", t->valor);

    printf("%s - Saldo Anterior: R$ %d,00\n", t->envia->nome, t->envia->saldo);
    t->envia->saldo = t->envia->saldo - t->valor;
    printf("%s - Saldo Posterior: R$ %d,00\n", t->envia->nome, t->envia->saldo);

    printf("%s - Saldo Anterior: R$ %d,00\n", t->recebe->nome,
           t->recebe->saldo);
    t->recebe->saldo = t->recebe->saldo + t->valor;
    printf("%s - Saldo Posterior: R$ %d,00\n", t->recebe->nome,
           t->recebe->saldo);

  } else {
    printf("Saldo Insuficiente\n");
  }

  pthread_mutex_unlock(&semaforo);
  free(t);
  return NULL;
}

int main(void) {
  srand(time(NULL));
  strcpy(conta1.nome, "Conta 1");
  conta1.saldo = 1000;
  strcpy(conta2.nome, "Conta 2");
  conta2.saldo = 1000;

  pthread_mutex_init(&semaforo, NULL);

  int totalDeTransacoes = 1000;
  int totalDeLoops = totalDeTransacoes / 100 + (totalDeTransacoes % 100 != 0);
  int count = 0;

  for (int i = 0; i < totalDeLoops; i++) {
    pthread_t thread_id[100];

    printf("==================================================\n");
    printf("Processando até 100 transações simultâneas");
    printf("==================================================\n");
    for (int j = 0; j < 100; j++) {
      if (count >= totalDeTransacoes) {
        break;
      }

      transacao *t = (transacao *)malloc(sizeof(transacao));
      int n = rand() % 2;
      if (n == 0) {
        t->envia = &conta1;
        t->recebe = &conta2;
      } else {
        t->envia = &conta2;
        t->recebe = &conta1;
      }
      t->valor = rand() % 500 + 1;

      pthread_create(&thread_id[j], NULL, transferir, (void *)t);
      count++;
    }

    for (int j = 0; j < 100; j++) {
      if (j < count) {
        pthread_join(thread_id[j], NULL);
      }
    }
  }

  pthread_mutex_destroy(&semaforo);
  printf("Total de Transações: %d\n", totalDeTransacoes);

  return 0;
}
