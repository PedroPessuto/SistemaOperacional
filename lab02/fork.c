#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd[2];
    pid_t pid;
    int valor = 5;
    
    // Cria o pipe
    if (pipe(fd) == -1) {
        fprintf(stderr, "Erro ao criar o pipe\n");
        return 1;
    }

    // Cria um novo processo
    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Erro ao criar o processo\n");
        return 1;
    }

    if (pid > 0) {  // Processo pai
        close(fd[0]);  // Fecha a ponta de leitura do pipe
        
        // Espera um pouco para garantir que o filho tenha tempo de executar
        sleep(1);
        
        // Escreve o valor no pipe
        write(fd[1], &valor, sizeof(valor));
        
        close(fd[1]);  // Fecha a ponta de escrita do pipe
    } else {  // Processo filho
        int valor_filho;
        
        close(fd[1]);  // Fecha a ponta de escrita do pipe
        
        // Lê o valor do pipe
        read(fd[0], &valor_filho, sizeof(valor_filho));
        
        // Incrementa o valor em 15
        valor_filho += 15;
        
        printf("Valor recebido do pai e incrementado: %d\n", valor_filho);
        
        close(fd[0]);  // Fecha a ponta de leitura do pipe
    }

    return 0;
}
