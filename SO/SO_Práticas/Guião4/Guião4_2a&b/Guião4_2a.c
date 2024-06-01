#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

#define SENDNUMS 100000

int main(int argc, char *argv){

    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) return -1;

    if((pid = fork()) == -1) return -1;

    if(pid == 0){

        int send = 5;

        if(close(fd[0]) == -1) _exit(EXIT_FAILURE);

        // Para o bloqueio mencionado no enunciado ocorrer temos de ultrapassar o buffer do pipe (64k) para que
        //não exista mais espaço no pipe para escrever ints, para conseguir observar este fenómeno usei um número
        //muito elevado de valores para enviar pelo pipe
        for(int i = 0; i < SENDNUMS; i++){
            if(write(fd[1], &send, sizeof(int)) == -1) _exit(EXIT_FAILURE);
            printf("Processo Filho %d: Enviei o valor %d %dº vez\n\n", getpid(), send, i);
        }

        if(close(fd[1]) == -1) _exit(EXIT_FAILURE);

        _exit(0);
    }

    int received;

    if(close(fd[1]) == -1) return -1;

    // ALINEA a)
    // Este sleep vai ter o proposito de dar tempo ao processo filho de atingir a capicidade máxima do pipe
    //resultando no seu bloqueio, já que se o processo filho e o processo pai estivessem a escrever e a ler (respetivamente)
    //do pipe dificilmente iamos atingir esta capacidade máxima
    sleep(3);

    for(int i = 0; i < SENDNUMS; i++){
    if(read(fd[0], &received, sizeof(int)) == -1) return -1;
    printf("Processo Pai %d: Recebi o valor %d %dº vez\n\n", getpid(), received, i);
    }

    if(close(fd[0]) == -1) return -1;

    wait(NULL);

    return 0;
}