#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "defs.h"

#define fifo_name "fifo_server_client"

// Só podemos por o client a correr depois de ter o server aberto

int main (int argc, char * argv[]){

	if (argc < 2) {
		printf("Missing argument.\n");
		_exit(1);
	}

	int resp;
	// O método atoi converte de String para inteiro
	int value = atoi(argv[1]);

	ssize_t bytes_lidos;
	int fifo_fd = open(fifo_name, O_RDWR);
	if(fifo_fd == -1) return -1;

	// Vamos escrever o valor que recebemos como argumento no fifo para que 
	//o server o possa utilizar
	if(write(fifo_fd, &value, sizeof(int)) == -1) return -1;
	// Depois deste ser utilizado vamos ler do fifo a resposta enviada pelo servidor
	if((bytes_lidos = read(fifo_fd, &resp, sizeof(int))) == -1) return -1;

	// A função sprintf vai escrever a string formatada diretamente no buffer
	//Temos de fazer esta conversão pois se escrevessemos um valor int com a 
	//system call write este iria desformatar
	char buffer[100];
	sprintf(buffer, "%d\n", resp);

	// Este write vai escrever do buffer para output 
	if(write(1, buffer, sizeof(int)) == -1) return -1;

	close(fifo_fd);
	unlink(fifo_name);
	return 0;
}

