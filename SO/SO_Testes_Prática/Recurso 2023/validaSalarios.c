// Considere uma empresa que utiliza um único ficheiro em formato binário para armazenar todos os registos individuais dos seus
// funcionários. Cada registo contém o nome, cargo e salário na empresa de um funcionário, de acordo com a seguinte estrutura:

// struct RegistoF {
// char nome[20];
// char cargo[20];
// int salário;
// };

// 2. Escreva a função int validaSalarios(char* ficheiro, char* cargo) que valida o salário de todos os fun-
// cionários com um dado cargo. A função deve retornar 1 caso algum funcionário receba menos do que o salário mínimo. Caso
// contrário, deve retornar 0. Para resolver este exercício, deve tirar proveito dos seguintes ficheiros executáveis:

// • ./filtraCargo <ficheiro> <cargo> - procura no ficheiro de registos os funcionários de um dado cargo
// e escreve para o stdout os respectivos registos.

// • ./validaMin - lê registos do stdin, no mesmo formato produzido pelo ficheiro executável filtraCargo, e termina
// com código de saída 1, caso algum funcionário receba menos que o salário mínimo, ou 0 caso contrário.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "RegF.h"

int validaSalarios(char* ficheiro, char* cargo){

    int pipes[2][2];
    int result;

    pipe(pipes[0]);

    pid_t pid = fork();

    if(pid == 0){

        dup2(pipes[0][1], 1);
        close(pipes[0][1]);

        execlp("./filtraCargo", "./filtraCargo", ficheiro, cargo, NULL);

        _exit(EXIT_FAILURE);
    }

    close(pipes[0][1]);

    pipe(pipes[1]);

    pid = fork();

    if(pid == 0){

        dup2(pipes[0][0], 0);
        close(pipes[0][0]);

        dup2(pipes[1][1], 1);
        close(pipes[1][1]);

        execlp("./validaMin", "./validaMin", NULL);

        _exit(EXIT_FAILURE);
    }

    close(pipes[0][0]);
    close(pipes[1][1]);

    wait(NULL);
    wait(NULL);

    read(pipes[1][0], &result, sizeof(int));
    close(pipes[1][0]);

    return result;
}