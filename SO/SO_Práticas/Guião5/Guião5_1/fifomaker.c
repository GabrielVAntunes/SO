#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

// Este código só tem o propósito de criar o fifo
int main(int argc, char *argv[]){

    char *fifo_name = "fifo_reader_writer";

    // Criamos o fifo com permissões de leitura e de escrita
    if(mkfifo(fifo_name, 0666) == -1) return -1;
    printf("FIFO: \"%s\" criado com sucesso!\n\n", fifo_name);
    
    return 0; 
}