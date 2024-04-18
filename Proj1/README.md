# Projeto Escada Rolante Dupla


# 1. Estratégia para evitar que duas pessoas acessem a escada rolante ao mesmo tempo em cada abordagem

Em amabas abordagens a função escada_rolante() controla o acesso à escada por pessoas de duas direções alternadas. Ela verifica se o próximo na fila pode avançar, baseado no tempo de partida e na presença ou ausência de pessoas na direção oposta. Se possível, o índice da direção atual é incrementado; se não, a função ajusta o tempo e avança na direção oposta. A última partida é sempre incrementada em 10 unidades para evitar acessos simultâneos.

# 2. Como garantir que somente uma das direções está ativa de cada vez em cada uma das abordagens?

Foi feita uma variável de direção ativa, que é alternada a cada iteração do loop. A validação do tempo de partida e a verificação de pessoas na direção oposta, são usadas para controlar o acesso. A função também ajusta os tempos e incrementa os índices de maneira a prevenir acessos simultâneos de direções opostas.

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
