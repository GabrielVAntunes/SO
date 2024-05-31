#include "mysystem.h"


// recebe um comando por argumento
// returna -1 se o fork falhar
// caso contrario retorna o valor do comando executado
int mysystem (const char* command) {

	int res = -1;

	// Estamos a assumir numero maximo de argumentos
	// isto teria de ser melhorado com realloc por exemplo
	char *exec_args[20];
	char *string, *cmd, *tofree;
	int i=0;
	tofree = cmd = strdup(command);
	while((string = strsep(&cmd," "))!=NULL){
	   exec_args[i]=string;
	   i++;
	}
	exec_args[i]=NULL;

	/// EXERCICIO 3 ///
	// Para este exercício bastou combinar os conhecimentos sobre como o processo prosegue após a execução de um comando
	//com os conhecimentos de como transmitir informação dos processos filho para o processo pai após a sua terminação
	pid_t pid;
	int status;

	if((pid = fork()) == -1) return -1;

	if(pid == 0){

		execvp(exec_args[0], exec_args);

		// O processo filho só chegará aqui se ocorrer algum erro a executar o comando
		//e através do _exit() vai transmitir informação de que não conseguiu concluir o comando
		_exit(EXIT_FAILURE);
	}

	if(wait(&status) == -1) return -1;

	// Tal como no Guião 2 verificamos os estados de terminação dos processos filho e gerimos a informação
	//conforme o desejado
	if(WIFEXITED(status)){
		if(WEXITSTATUS(status) == 1){
			printf("Ocorreu um erro a executar o comando %s", exec_args[0]);
		} else {
			printf("O comando %s foi executado com sucesso!", exec_args[0]);
			res = 0;
		}
	}

	/// FIM DO EXERCICIO 3 ///

	free(tofree);

	return res;
}