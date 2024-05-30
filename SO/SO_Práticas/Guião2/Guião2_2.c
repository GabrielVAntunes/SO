#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv){

    int pid;

    // A função fork() vai criar um processo filho que vai correr o programa concorrentemente ao processo que lhe deu origem
    /* Valores de retorno de fork():
    - -1 - Caso tenha ocorrido um erro na criação do processo filho
    - 0 - O processo filho terá associado o valor 0
    - pid_filho - O processo pai vai assumir o valor pid do seu processo filho
    */
    if((pid = fork()) == -1) return -1;

    int value;

    // Apenas o processo pai entra nesta secção do código
    if(pid != 0) {

        /* A função wait fará com que o processo pai não avance deste 
        ponto até que o processo filho termine a sua execução
        */
        // a função wait retornará -1 caso não haja processos filho para esperar ou caso tenha ocorrido algum erro
        if(wait(NULL) == -1) {
            return -1;
        }
        // Queremos que apenas o pai espere pois o processo filho não tem processos filho associados
        /* Como ambos os processos ocorrem concorrentemente se não fizermos com que o processo pai espere 
        pelo processo filho é possivel que o pai acabe primeiro que o filho e nesse caso o processo filho 
        será associado a um novo processo pai
        */
    }

    // Ambos os processos vão passar por aqui e retornar os respetivos valores
    printf("Processo atual: %d \n"
            "Processo Pai:  %d\n\n",getpid(), getppid());

}