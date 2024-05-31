#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv){


    /* A função exec vai substituir este programa em execução num determinado processo 
    é substituído pelo programa recebido como argumento
    Diferentes tipos de Exec's:
    - execl(Path para o executável, nome do executável, argumentos necessários ... NULL);
    - execlp(Ficheiro com o executável, nome do exevutável, argumentos necessários ... NULL);
    - execv(Path para o executável, argv[])
    - execvp(Ficheiro com o executável, argv[])  
       A diferença do execv() e do execvp() para os restantes é que eles recebem os argumentos do exectável
    já num vetor de argumentos (Este vetor deve iniciar pelo nome do executável e terminar em NULL)
    */
    execlp("ls", "ls", "-l", NULL);

    /* Este exercicio foi proposto para demonstrar que no fim de um exec o processo que o executou "morre"
    pois o programa em execução neste processo é substituido pelo programa recebido como argumento daí
    o print seguinte não ser escrito (só será escrito em caso de falha do exec)
    */
    printf("O programa chegou aqui!");

    return 0;
}