#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

/* Este exercicio é muito parecido ao anterior penso que o seu proposito seja fazer-nos compreender que os processos agem de 
de forma concorrente tornando-se imprevisiveis por vezes como o processo pai apenas espera pelos processos filho no fim 
de os criar a todos, nada garante que a ordem se preserve e que eles cheguem pela ordem que foram criados
*/
int main(int argc, char *argv){

    pid_t pid;
    int status;

    printf("Processo Pai: %d\n\n", getpid());

    // Ciclo que vai criar os 10 processos filho
    for(int i = 1; i <= 10; i++){

        if ((pid = fork()) == -1){
            _exit(EXIT_FAILURE);
        }

        if (pid == 0){

            printf("Processo Filho nº %d\n"
                    "PID: %d;\n"
                    "PPID: %d;\n\n", i, getpid(), getppid());

            _exit(i);
        }
    }

    // Ciclo que vai esperar que os 10 processos criados terminem as suas execuções e imprimam as informações dos mesmos
    for(int i = 1; i <= 10; i++){
        pid_t pid_child = wait(&status);
        if (pid_child == -1) _exit(EXIT_FAILURE);

        if(WIFEXITED(status)){
            int exit_status = WEXITSTATUS(status);
            printf("Processo Pai: \n"
                   "O processo Filho %d terminou com o código de saída %d\n\n", pid_child, exit_status);
        } else {
            printf("Processo Pai:\n"
                   "O processo Filho %d não terminou corretamente\n\n", pid_child);
        }
    }
}
