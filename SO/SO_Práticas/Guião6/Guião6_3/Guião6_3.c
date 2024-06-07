#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){

    int fdin = open("/etc/passwd", O_RDONLY);
    int fdout = open("saida.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    int fderr = open("erros.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);

    int cout = dup(1);

    dup2(fdin,0);
    close(fdin);

    dup2(fdout,1);
    close(fdout);

    dup2(fderr,2);
    close(fderr);

    // Este Exercício mostrou-nos que o resultado do comando executável também pode
    //ser direcionado para um ficheiro
    execlp("wc", "wc", NULL);

    // Como vimos no guião 3 depois de executar um comando o programa termina, logo ao fazer 
    //execlp esta mensagem não vai ser impressa
    printf("\nTerminei\n");
    return 0;
}