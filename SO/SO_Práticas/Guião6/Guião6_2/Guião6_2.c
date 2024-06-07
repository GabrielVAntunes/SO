#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {

    // Começamos por abrir todos os descritores que vamos utilizar ao longo do programa
    int fdin = open("/etc/passwd", O_RDONLY);
    int fdout = open("saida.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    int fderr = open("erros.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);

    // Criamos um cópia do fd do STDOUT
    int cout = dup(1);

    // Vamos escolher para onde queremos redirecionar os dados
    // Vamos Indicar ao programa para ler do fdin em vez de ler do STDIN
    dup2(fdin,0);
    close(fdin);

    // Vamos Indicar ao programa para escrever o output no fdout em vez de escrever no STDOUT
    dup2(fdout, 1);
    close(fdout);

    // Vamos Indicar ao programa que escreva as mensagens de erro no fderr em vez de as escrever no STDERR
    dup2(fderr, 2);
    close(fderr);

    pid_t pid;
    pid  = fork(); 
    
    // Como já vimos no guião 2 um processo filho é uma réplica do processo pai, mantém os modos e os dados definidos até ao momento
    //como chamamos o processo filho depois de redirecionar os fd's, dentro do processo filho estas indicações também estão definidas
    if (pid == 0) {

        char buffer_filho[1024];
        char buffer_filho_send[512];
        ssize_t bytes_lidos_filho;
        

        // Além de escrever tudo no buffer_filho_send a função sprintf() vai retornar o tamanho da string resultante
        int len = sprintf(buffer_filho_send, "\n\nProcesso FILHO %d :\n", getpid());

        write(1, buffer_filho_send, len);

        while((bytes_lidos_filho = read(0, buffer_filho, 512)) > 0){
            // Aqui podemos ver que apesar do write estar a escrever para o STDOUT os dados são escritos no
            //ficheiro saida.txt, tal como previsto
            write(1, buffer_filho, bytes_lidos_filho);
        }

        _exit(0);
    }

    // Repare-se que com o processo pai só faz a leitura depois do processo filho terminar, o apontador do ficheiro
    // /etc/passwd vai estar no fim do ficheiro e como tal não vai ser possivel efetuar a leitura

    // Para evitar isto antes da leitura do ficheiro no processo pai teríamos de utilizar a função lseek para 
    //mover o apontador de leitura
    wait(NULL);

    char buffer[1024];
    ssize_t bytes_lidos;
    while((bytes_lidos = read(0, buffer, 1024)) > 0){
        // Como redirecionamos os fd's, mesmo que o write esteja a escrever no STDOUT e no STDERR os dados 
        //vão ser redirecionados para o saida.txt e para o erros.txt respetivamente
        write(1,buffer,bytes_lidos);
        write(2,buffer,bytes_lidos);
    }

    // Agora vamos utilizar o cout, cópia do STDOUT para redirecionar novamente o texto para o STDOUT
    //Caso contrário a mensagem "Terminei" iria ser escrita no saída.txt
    dup2(cout,1);
    close(cout);

    printf("Terminei\n");
    return 0;
}