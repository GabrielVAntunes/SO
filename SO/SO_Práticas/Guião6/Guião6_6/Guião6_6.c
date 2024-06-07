#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>


#define MAX_COMMANDS 10

// parse do argumento e execvp
// devolve o resultado do exec
int exec_command(char* arg){

	//Estamos a assumir numero maximo de argumentos
	char *exec_args[10];

	char *string;	
	int exec_ret = 0;
	int i=0;

	char* command = strdup(arg);

	string=strtok(command," ");
	
	while(string!=NULL){
		exec_args[i]=string;
		string=strtok(NULL," ");
		i++;
	}

	exec_args[i]=NULL;
	
	exec_ret=execvp(exec_args[0],exec_args);
	
	return exec_ret;
}


int main(int argc, char** argv){
	
	int number_of_commands=4;
	
	char * commands[] = {
		"grep -v ^# /etc/passwd",
		"cut -f7 -d:",
		"uniq",
		"wc -l"
	};

	// Criamos N - 1 pipes, sendo N o número de comandos - 1, para podermos trocar dados entre cada o comando e o seguinte
	int pipes[number_of_commands -1][2];

	for(int i = 0; i < number_of_commands; i++){
		
		// Caso estajamos a iterar o 1º comando: 
		if(i == 0){

			pipe(pipes[i]);
			switch(fork()){

				case -1:
					return -1;

				// O processo filho vai fechar o seu pipe de leitura, e redirecionar o output para
				//o seu pipe de escrita, garantindo que ao executar o comando os dados vão para o pipe e não para o STDOUT
				case 0:
					close(pipes[i][0]);

					dup2(pipes[i][1], 1);
					close(pipes[i][1]);
					
					exec_command(commands[i]);

					_exit(EXIT_FAILURE);

				// O processo pai vai fechar logo as entradas dos pipes pois não as vai utilizar,
				//só os processos filho é que vão comunicar entre si
				default:
					close(pipes[i][1]);
			}

		// Caso estejamos a iterar o último comando:
		} else if(i == number_of_commands -1){
			pipe(pipes[i]);
			switch(fork()){

				case -1:
					return -1;

				// O Processo filho vai redirecionar o input para o pipe de leitura anterior, garantindo
				//que obtém os dados que foram escritos pelo comando anterior em vez de os obter do STDIN
				case 0:
					dup2(pipes[i - 1][0], 0);
					close(pipes[i - 1][0]);

					exec_command(commands[i]);

					_exit(EXIT_FAILURE);

				default:
					close(pipes[i - 1][0]);
			}
		
		// Caso estejamos a iterar algum dos comandos intermédios:
		} else {
			pipe(pipes[i]);
			switch(fork()){

				case -1:
					return -1;

				// Neste caso o Processo Filho vai redirecionar tanto o input para o pipe de leitura anterior
				//como o output para o pipe de escrita atual, garantindo assim que ele recebe os dados do comando anterior
				//e envia os dados resultandes da execução do comando atual para o proximo
				case 0:
					dup2(pipes[i - 1][0],0);
					close(pipes[i - 1][0]);

					dup2(pipes[i][1], 1);
					close(pipes[i][1]);

					exec_command(commands[i]);

					_exit(EXIT_FAILURE);
				
				default:
					close(pipes[i-1][0]);
					close(pipes[i][1]);
			}
		}

		for(int i = 0; i < number_of_commands; i++){
			wait(NULL);
		}
	}

	printf("\nTerminei a execução da PipeLine!\n\n");
	return 0;
}

