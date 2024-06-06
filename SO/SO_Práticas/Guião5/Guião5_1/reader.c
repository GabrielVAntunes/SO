#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 100

// Nota* - O writer e o reader devem correr em simultaneo depois da criação do fifo
/*  Para compilar: gcc reader.c -o reader.c
    Para compilar: gcc writer.c -o writer.c

    Para correr: ./reader
    Para correr: ./writer
*/

int main(){

    char *fifo_name = "fifo_reader_writer";
    char buffer[BUFFER_SIZE];
    ssize_t bytes_lidos;

    int fifo_fd = open(fifo_name, O_WRONLY);
    if(fifo_fd == -1) return -1;

    // Lemos os dados do input para o buffer
    if((bytes_lidos = read(0, buffer, BUFFER_SIZE)) == -1) return -1;
    // Escrevemos os dados do buffer para o fifo
    if(write(fifo_fd, buffer, bytes_lidos) == -1) return -1;
    close(fifo_fd);

}