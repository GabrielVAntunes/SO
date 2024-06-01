#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

#define SENDNUMS 5

int main(int argc, char *argv){

    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) return -1;

    if((pid = fork()) == -1) return -1;

    if(pid == 0){

        if(close(fd[0]) == -1) _exit(EXIT_FAILURE);

        for(int i = 0; i < SENDNUMS; i++){
            if(write(fd[1], &i, sizeof(int)) == -1) _exit(EXIT_FAILURE);
            printf("Processo Filho %d: Enviei o valor %d\n\n", getpid(), i);
        }

        if(close(fd[1]) == -1) _exit(EXIT_FAILURE);

        _exit(0);
    }

    wait(NULL);

    int received;

    if(close(fd[1]) == -1) return -1;

    int i = 0;
    int eof;

    // ALINEA B
    // O EOF (End Of File) ocorre quando a entrada de escrita do pipe é fechada pelo processo que está a escrever
    //ou seja é sinalizado que não vamos receber mais dados deste pipe, neste caso a system call read(); retorna 0
    // Desta forma podemos criar pipes que leiam indefinidamente enquanto houver dados a ser lidos
    while((eof = read(fd[0], &received, sizeof(int))) != -1){
        if(eof == 0){
            printf("! EOF !\n");
            break;
        } else {
            printf("Processo Pai %d: Recebi o valor %d\n\n", getpid(), received);
            i++;
        }
    }

    // Eu fiz desta forma para que fosse mais percetivel a chegada ao fim do ficheiro, para representar esta ideia de 
    //uma forma mais prática poderíamos fazer por exemplo:
    /*  
        while(read(fd[0], &received, sizeof(int)) > 0){
            ... Instruções ...
        }
    */

    if(close(fd[0]) == -1) return -1;

    return 0;
}