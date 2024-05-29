#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define BUFFER_SIZE 100

int main(){

    // O ficheiro já criado origem.txt é ficheiro onde vamos buscar a informação
    // O comando open vai abrir o ficheiro e a flag: O_RDONLY sinaliza que apenas  
    //o abrimos para ler o que este ficheiro contém.
    int fd_origin = open("origem.txt",O_RDONLY);

    // Algumas Flags: 
    // - O_RDONLY - Apenas para leitura;
    // - O_WRONLY - Apenas para escrita;
    // - O_TRUNC - Se o ficheiro já existir será truncado para 0 (apaga o que já estiver no ficheiro);
    // - O_RDWR - Tanto para leitura como para escrita;
    // - O_CREAT - Se o ficheiro não existir cria-o;
    
    // Aqui estamos a verificar se ocorreu algum erro ao abrir o ficheiro
    if (fd_origin == -1) return 1;

    // Criamos estas varíaveis de tamanho em bytes para utilizar depois 
    ssize_t bytes_lidos, bytes_recebidos;
    // Este buffer é como se fosse uma porção de memória que nós preservamos para guardar informação
    char buffer[BUFFER_SIZE];

    // Aqui abrimos o ficheiro destino ou caso ele ainda não exista criamos o mesmo 
    // (o Código 0600 indica que ao criar o ficheiro o utilizador tem permissões para ler, escrever e executar o ficheiro)
    int fd_destination = open("destino.txt", O_WRONLY | O_TRUNC | O_CREAT, 0600);
    if(fd_destination == -1) return 1;

    // Este ciclo vai ler o que está dentro do ficheiro enquanto houver alguma coisa para ler
    while( (bytes_lidos = read(fd_origin,buffer, BUFFER_SIZE)) > 0){

        // O comando write efetivamente escreve para no novo ficheiro
        if(write(fd_destination, buffer, bytes_lidos) == -1) return 1;

    }

    //  Depois de os utilizarmos fechamos ambos os ficheiros
    close(fd_destination);
    close(fd_origin);

}