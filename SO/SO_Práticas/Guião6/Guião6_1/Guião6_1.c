#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

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

    
    char buffer[1024];
    int bytes_lidos;
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