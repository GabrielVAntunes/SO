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

    char buffer[100];

    pid_t pid = fork();

    if(pid == 0){

        close(pipe_fd[1]);

        // Dentro do processo filho vamos redirecionar o input, para que em vez de ler dados do STDIN 
        //leia diretamente do pipe a informação passada pelo processo pai
        dup2(pipe_fd[0], 0);
        close(pipe_fd[0]);

        execlp("wc", "wc", NULL);

        _exit(EXIT_FAILURE);
    }

    ssize_t bytes_lidos;
    close(pipe_fd[0]);

    // Para testar com várias linhas podemos interromper a leitura com "Ctrl D" 
    // Ctrl D - vai enviar um signal de EOF que retornará 0 no read();
    while((bytes_lidos = read(0, buffer, sizeof(buffer))) > 0){
        write(pipe_fd[1], buffer, bytes_lidos); 
    } 
    close(pipe_fd[1]);

    wait(NULL);

    printf("\nTerminei\n");
    return 0;
}