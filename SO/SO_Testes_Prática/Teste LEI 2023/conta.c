#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int conta(char* imagens[], int n){

    int pipe_fd[2];
    pipe(pipe_fd);

    pid_t pid = fork();

    if(pid == 0){

        close(pipe_fd[0]);

        dup2(pipe_fd[1], 1);
        close(pipe_fd[1]);

        defeitos(imagens, n, 4);

        _exit(0);
    }

    pid = fork();

    if(pid == 0){

        close(pipe_fd[1]);

        dup2(pipe_fd[0], 0);
        close(pipe_fd[0]);

        execlp("wc", "wc", "-l", NULL);

        _exit(EXIT_FAILURE);
    }
    
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    for(int i = 0; i < 2; i++) wait(NULL);

    return 0;
}