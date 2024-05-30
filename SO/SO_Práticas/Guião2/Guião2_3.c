#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv){

    pid_t pid;
    int status;

    printf("Processo Pai: %d\n\n", getpid());

    // Com este ciclo for vamos criar 10 processos filho, um por vez
    for(int i = 1; i <= 10; i++){

        /* Em vez de dar return, usamos exit para que futuramente consigamos obter 
        informação do término do processo filho através da variável status
        */
        if((pid = fork()) == -1) _exit(EXIT_FAILURE);

        if(pid == 0){

            printf("Processo filho nº %d:\n "
                    "PID - %d;\n"
                    "PPID - %d;\n\n", i, getpid(), getppid());

            // Caso o processo filho termine corretamente retornará o seu número de ordem de criação
            _exit(i);
        } else {

            /* A função wait além de retornar o pid do processo filho que terminou, atualia o endereço 
            do status com informações sobre o estado de saída do processo filho
            */
            pid_t child_pid = wait(&status);
            if (child_pid == -1) _exit(EXIT_FAILURE);

            // O processo pai vai confirmar o término do processo filho, seja normal ou devido a um erro
            if(WIFEXITED(status)){
                int exit_status = WEXITSTATUS(status);
                printf("Processo pai:\n"
                        "O Processo Filho %d terminou com o código de saída - %d\n\n", child_pid, exit_status);
            } else {
                printf("Processo pai:\n"
                        "O Processo Filho %d não terminou corretamente\n\n", child_pid);
            }
        }
    }
    return 0;
}