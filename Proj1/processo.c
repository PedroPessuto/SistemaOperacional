#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int pessoas_globais[2][10000];
int tamanhos[2] = {0, 0};
int direcao;
int tempo_atual;

int escada_rolante() {

  // ========== VARIÁVEIS ==========
  int direcao_oposta;
  int indices[2] = {0, 0};
  int ultima_partida = 0;

  tempo_atual = pessoas_globais[direcao][0];

  while (indices[0] < tamanhos[0] || indices[1] < tamanhos[1]) {
    direcao_oposta = 1 - direcao;

    if (pessoas_globais[direcao][indices[direcao]] <= ultima_partida) {
      // Atualiza o tempo atual para o tempo de partida da pessoa na posição atual
      tempo_atual = pessoas_globais[direcao][indices[direcao]];

      // Avança o indice
      indices[direcao]++;
    } 
    else {
      // Determina o novo tempo atual baseado na comparação entre a última partida e a próxima pessoa na direção oposta
      int proxima_partida_oposta = pessoas_globais[direcao_oposta][indices[direcao_oposta]];

      tempo_atual = (ultima_partida > proxima_partida_oposta) ? ultima_partida : proxima_partida_oposta;

      // Avança o índice na direção oposta
      indices[direcao_oposta]++;
    }

    ultima_partida = tempo_atual + 10;
    direcao = 1 - direcao;
  }

  return ultima_partida + 10;
}

int main() {

  // ========== INPUT ==========
  FILE *arquivo_entrada, *arquivo_saida;

  // Abre o arquivo
  arquivo_entrada = fopen("input.txt", "r");
  if (arquivo_entrada == NULL) {
    printf("Erro ao abrir o arquivo de entrada.\n");
    return 0;
  }

  // Pega a quantidade de pessoas
  int numero_pessoas;
  fscanf(arquivo_entrada, "%d", &numero_pessoas);

  // Pega o tempo e direção de cada pessoa e adiciona na matriz certa
  int tempo, direcao_aux;
  for (int i = 0; i < numero_pessoas; i++) {
    fscanf(arquivo_entrada, "%d %d", &tempo, &direcao_aux);

    // Ver por qual posição começa
    if (i == 0) {
      direcao = direcao_aux;
    }

    pessoas_globais[direcao_aux][tamanhos[direcao_aux]] = tempo;
    tamanhos[direcao_aux]++;
  }

  // Fecha o arquivo
  fclose(arquivo_entrada);

  // ========== PROCESSOS ==========

  pid_t pid = fork();

  // Processo Filho --> Resolve o problema
  if (pid == 0) {
    int resultado = escada_rolante();
    return 0;

  }
  // Processo Pai --> Cria o arquivo de saída após o filho terminar de executar
  else {
    wait(NULL); // Espera o filho terminar
    
    // ========== OUTPUT ==========
    
    // Cria o arquivo
    arquivo_saida = fopen("output.txt", "w");
    if (arquivo_saida == NULL) {
      printf("Erro ao abrir o arquivo de saída.\n");
      return 0;
    }

    // Adiciona no tempo de execução certa
    int tempo_execucao = escada_rolante();
    fprintf(arquivo_saida, "%d\n", tempo_execucao);

    // Fecha o arquivo
    fclose(arquivo_saida);
  }

 

  return 0;
}
