#include <stdio.h>
#include <unistd.h>

int main() {
    int fd[2];
    pid_t pid;
    int valor = 5;
    
    if (pipe(fd) == -1) {
        fprintf(stderr, "Erro ao criar o pipe\n");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Erro ao criar o processo\n");
        return 1;
    }

    if (pid > 0) {  
        // Processo pai
        int valor_recebido;
        close(fd[1]);
        read(fd[0], &valor_recebido, sizeof(valor_recebido));
        printf("Valor recebido do filho: %d\n", valor_recebido);
        close(fd[0]); 
    } 
    else {  // Processo filho
        int valor_filho = valor;
        
        close(fd[0]); 
        valor_filho += 15;
        write(fd[1], &valor_filho, sizeof(valor_filho));
        printf("Valor recebido do pai e incrementado: %d\n", valor_filho);
        close(fd[1]);
    }

    return 0;
}
