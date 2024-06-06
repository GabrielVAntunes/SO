#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "defs.h"
#include "vector.h"

//FIFO criado pelo servidor
//Cliente pode receber um sigpipe (concorrência!)	//printf("Escrevi o valor %d para o fifo\n\n",resp);

#define fifo_name "fifo_server_client"

// O server tem de ser aberto antes do client
/* make 
   make run_server
   make run_client
*/

int main (int argc, char * argv[]){

	init_vector();
	print_vector();

	mkfifo(fifo_name, 0666);

	int needle, resp;

	int fifo_fd = open(fifo_name, O_RDWR);
	if(fifo_fd == -1) return -1;
	
	// Lemos o valor que o client recebeu como argumento
	if((read(fifo_fd, &needle, sizeof(int))) == -1);
	resp = count_needle(needle);

	// Depois de contar o número de vezes que o valor aparece no vetor 
	//vamos enviar o resultado para que o client o escreva
	if(write(fifo_fd, &resp, sizeof(int)) == -1);

	close(fifo_fd);
	
	return 0;
}
