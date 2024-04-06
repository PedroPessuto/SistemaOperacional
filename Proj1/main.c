#include <stdio.h>

#define TEMPO_TRAVESSIA 10
#define MAX_PESSOAS 10000

typedef struct {
  int tempoChegada;
  int direcao;
} Pessoa;

int simularEscadaRolante(Pessoa pessoas[], int numPessoas) {

  // Se tiver ninguém
  if (numPessoas == 0)
    return 0;

  // Iniciar variáveis
  int direcao = pessoas[0].direcao;
  int ultimoDaSeq = pessoas[0].tempoChegada;
  int tempoDeTermino = pessoas[0].tempoChegada + 10;
  int count = 0; // Quantidade de pessoas que já concluiram a viagem
  int aux = 0;

  while (count < numPessoas) {

    
    for (int i = 0; i < numPessoas; i++) {
      if (pessoas[i].direcao == direcao) {
        if (pessoas[i].tempoChegada < tempoDeTermino) {
          ultimoDaSeq = pessoas[i].tempoChegada;
          count++;
        }
        if (i + 1 == numPessoas) {
          if (aux != 1) {
            tempoDeTermino = ultimoDaSeq + 10;
            aux = 1;
          } else {
            tempoDeTermino = tempoDeTermino + 10;
          }
          break;
        }
      }
    }

    for (int i = 0; i < numPessoas; i++) {
      if (pessoas[i].direcao != direcao) {
        if (pessoas[i].tempoChegada < tempoDeTermino) {
          ultimoDaSeq = pessoas[i].tempoChegada;
          count++;
        }
        if (i + 1 == numPessoas) {
          if (aux != 1) {
            tempoDeTermino = ultimoDaSeq + 10;
            aux = 1;
          } else {
            tempoDeTermino = tempoDeTermino + 10;
          }
          break;
        }
      }
    }
  }

  return tempoDeTermino;
}

int main() {
  int numPessoas;
  Pessoa pessoas[MAX_PESSOAS];
  FILE *arquivoEntrada, *arquivoSaida;

  arquivoEntrada = fopen("input.txt", "r");
  if (arquivoEntrada == NULL) {
    printf("Erro ao abrir o arquivo de entrada.\n");
    return 1;
  }

  fscanf(arquivoEntrada, "%d", &numPessoas);
  for (int i = 0; i < numPessoas; i++) {
    fscanf(arquivoEntrada, "%d %d", &pessoas[i].tempoChegada,
           &pessoas[i].direcao);
  }

  fclose(arquivoEntrada);

  arquivoSaida = fopen("output.txt", "w");
  if (arquivoSaida == NULL) {
    printf("Erro ao abrir o arquivo de saída.\n");
    return 1;
  }

  fprintf(arquivoSaida, "%d\n", simularEscadaRolante(pessoas, numPessoas));

  fclose(arquivoSaida);

  return 0;
}
