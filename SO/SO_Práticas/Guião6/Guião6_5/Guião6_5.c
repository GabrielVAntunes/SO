#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){

    int pipe_fd[2];
    pipe(pipe_fd);

    pid_t pid1 = fork();

    printf("\n");

    if(pid1 == 0){
        // O primeiro processo filho vai executar o comando "ls /etc"

        close(pipe_fd[0]);

        // Redirecionamos o output para que o executável escreva no pipe em vez de escrever no STDOUT
        dup2(pipe_fd[1], 1);
        close(pipe_fd[1]);

        execlp("ls", "ls", "/etc", NULL);

        _exit(EXIT_FAILURE);
    } else {

        pid_t pid2 = fork();

        if(pid2 == 0){
            // O Segundo processo filho vai executar o comando "wc -l"

            close(pipe_fd[1]);

            // Redirecionamos o intput para que o executável leia do pipe em vez de ler do STDIN
            dup2(pipe_fd[0], 0);
            close(pipe_fd[0]);

            execlp("wc", "wc", "-l", NULL);

            _exit(EXIT_FAILURE);

        }
    }    

    // Antes de esperar pelos filhos fechamos ambas as entradas do pipe para evitar que os processos filho 
    //fiquem à espera de receber mais dados
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    wait(NULL);
    wait(NULL);    

    printf("\nTerminei a execução do comando!\n\n");
    return 0;
}