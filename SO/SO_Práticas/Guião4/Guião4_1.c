#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv){

    // Ao contrário dos ficheiros comuns para criar um pipe vamos utilizar um array com 2 inteiros para ser o fd(File Descriptor)
    // O fd tem duas posições para que possamos guardar as 2 "pontas" do pipe, sendo estas:
    //      - fd[0] - entrada de leitura
    //      - fd[1] - entrada de escrita
    int fd[2];
    pid_t pid;

    int send = 5;

    if (pipe(fd) == -1) return -1;

    if((pid = fork()) == -1) return -1;

    if(pid == 0){

        int received;

        // Como o processo filho não vai enviar nada para o processo pai podemos fechar a entrada 
        //de escrita logo no inicio do processo
        if(close(fd[1]) == -1) _exit(EXIT_FAILURE);

        // Vamos ler o valor enviado pelo processo pai e guarda-lo numa varíavel do processo filho
        if(read(fd[0], &received, sizeof(int)) == -1) _exit(EXIT_FAILURE);
        printf("Processo Filho %d: Recebi o valor %d\n\n", getpid(), received);

        // Depois de ler tudo o que temos a ler podemos fechar a entrada de leitura
        if(close(fd[0]) == -1) _exit(EXIT_FAILURE);

        _exit(0);
    }

    // Como o processo pai não vai receber nada do processo filho, podemos fechar a entrada 
    //de leitura logo no inicio do processo
    if(close(fd[0]) == -1) return -1;

    // ALINEA a)
    // Na alínea a) é proposto que adicionemos um sleep no processo pai antes da escrita
    //do pipe para percebermos que no processo filho enquanto não houver dados a serem lidos o processo bloqueia
    //à espera de que estes dados cheguem ao pipe
    sleep(3);

    // Vamos enviar o valor ao processo filho, escrevendo-o na entrada de escrita do pipe
    if(write(fd[1], &send, sizeof(int)) == -1) return -1;
    printf("Processo Pai %d: Enviei o valor %d\n\n", getpid(), send);

    // Depois de enviar tudo o que temos a enviar podemos fechar a entrada de escrita
    if(close(fd[1]) == -1) return -1;

    wait(NULL);

    return 0;
}