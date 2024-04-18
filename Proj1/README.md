# Projeto Escada Rolante Dupla


# 1.  Qual a estratégia que você utilizou para evitar que duas pessoas acessem a escada rolante ao mesmo tempo em cada abordagem?

A estratégia utilizada em amabas das abordagens para evitar acessos simultâneos à escada rolante envolve alternar as direções de acesso a cada iteração e checar se é seguro avançar com base no tempo da última pessoa que utilizou a escada. Caso não seja possível avançar, o controle passa para a direção oposta, ajustando os tempos de partida conforme o necessário.

```
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

      // Atualiza o tempo de todas as pessoas na direção oposta que têm tempo menor que a última partida
      for (int i = indices[direcao_oposta]; i < tamanhos[direcao_oposta] && ultima_partida > pessoas_globais[direcao_oposta][i]; ++i) {
        pessoas_globais[direcao_oposta][i] = ultima_partida;
      }
    }

    ultima_partida = tempo_atual + 10;
    direcao = 1 - direcao;
  }
```

# 2. Como garantir que somente uma das direções está ativa de cada vez em cada uma das abordagens?

Foi feita uma variável de direção ativa, que é alternada a cada iteração do loop. A validação do tempo de partida e a verificação de pessoas na direção oposta, são usadas para controlar o acesso. A função também ajusta os tempos e incrementa os índices de maneira a prevenir acessos simultâneos de direções opostas.

```
// ========== VARIÁVEIS GLOBAIS ==========
int pessoas_globais[2][10000];
int tamanhos[2] = {0, 0};
int direcao;
int tempo_atual;

// ========== FUNÇÃO ==========
int escada_rolante() {

  // ========== VARIÁVEIS AUXILIARES ==========
  int direcao_oposta;
  int indices[2] = {0, 0};
  int ultima_partida = 0;

  tempo_atual = pessoas_globais[direcao][0];

 // ========== LOOP POR TODOS OS ELEMENTOS ==========
  while (indices[0] < tamanhos[0] || indices[1] < tamanhos[1]) {

    direcao_oposta = 1 - direcao; // Verifica qual é a direção oposta
   
    ... Código (Válidações e comparações) ...

    ultima_partida = tempo_atual + 10;
    direcao = 1 - direcao; // Altera a direção
  }

  return ultima_partida + 10;
}

```

# 3. Discorra sobre as diferenças entre as implementações utilizando threads e processos e diga qual foi mais eficiente na solução do problema, justificando sua resposta.

A implementação utilizando threads é mais eficiente que a implementação com processos. Já que, threads compartilham memória e recursos, resultando em menor sobrecarga de criação e troca de contexto em comparação com processos, que necessitam de duplicação do espaço de memória e são mais custosos em termos de recursos do sistema. Portanto, para tarefas que não requerem isolamento estrito de processamento, como a função escada_rolante, o uso de threads oferece uma solução mais rápida e eficiente.

Na implementação de threads, a função compartilha de variáveis globais para a execução da função.
```
  // ========== THREADS ==========

  pthread_t thread_id; // Cria Id
  pthread_create(&thread_id, NULL, escada_rolante, NULL); // Cria Thread com função
  pthread_join(thread_id, NULL); // Espera Thread terminar
```
Enquanto na de processos, foi criado um fork que se é é filho ele executa a função e se é pai cria o arquivo de output. Entretanto, nesse caso existe a duplicação no espaço de memório, sendo assim menos eficiênte.

```
  // ========== PROCESSOS ==========

  pid_t pid = fork();

  // Processo Filho --> Resolve o problema
  if (pid == 0) {
    int resultado = escada_rolante();
    return 0;

  }
  // Processo Pai --> Cria o arquivo de saída após o filho terminar de executar
  else {
    wait(NULL);

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
```
