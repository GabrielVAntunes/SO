#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv){

    pid_t pid;

    if ((pid = fork()) == -1) return -1;

    /* Para que seja possível utilizar exec's de forma a não prejudicar a execução do programa, utilizamos um fork() para 
    executar o comando, assim no fim de executar o comando apenas o processo filho irá ser terminado e o processo pai pode 
    prosseguir a programa normalmente
    */
    if(pid == 0){
        
        execlp("ls", "ls", "-l", NULL);

        // Ao correr o programa podemos ver que tal como previsto esta mensagem não será impressa
        printf("Processo Filho %d: Cheguei aqui!\n\n", getpid());

        /* Podemos acrescentar este _exit() neste ponto do programa para informar o processo pai que a execução do
        comando incorreu num erro (visto que caso contrário o programa não chegaria aqui)
        */
        _exit(EXIT_FAILURE);
    }

    if(wait(NULL) == -1) return -1;

    // Tal como previsto apenas esta mensagem será impressa no ecrã depois do comando ser executado
    printf("Processo Pai %d: Cheguei aqui!\n\n", getpid());

    return 0;
}