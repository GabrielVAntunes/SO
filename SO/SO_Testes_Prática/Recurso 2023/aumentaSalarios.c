// Considere uma empresa que utiliza um único ficheiro em formato binário para armazenar todos os registos individuais dos seus
// funcionários. Cada registo contém o nome, cargo e salário na empresa de um funcionário, de acordo com a seguinte estrutura:

// struct RegistoF {
// char nome[20];
// char cargo[20];
// int salário;
// };

// 1. Escreva a função void aumentaSalarios(char* ficheiro, char* cargo, int valor, long N, int
// P) que atualiza o ficheiro com N registos de forma aumentar em valor o salário dos funcionários com um dado cargo.
// Valorização: A função deve desencadear uma atualização concorrente com P processos.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "RegF.h"

void aumentaSalarios(char* ficheiro, char* cargo, int valor, int N, int P){

    int fd;
    int running_tasks = 0;
    int i = 0;
    RegistoF regF;
    
    if((fd = open(ficheiro, O_RDWR)) == -1) return -1;

    while(i < N){

        if(running_tasks < P){

            pid_t pid = fork();

            if(pid == 0){

                lseek(fd, sizeof(RegistoF) * i, SEEK_SET);
                if(read(fd, &regF, sizeof(RegistoF)) == -1) return -1;

                if(strcmp(regF.cargo, cargo) == 0){

                    regF.salário += valor;

                    lseek(fd, sizeof(RegistoF) * i, SEEK_SET);
                    if(write(fd, &regF, sizeof(RegistoF)) == -1);  
                }

                _exit(0);

            } else {

                running_tasks++;
                i++;
            }

        } else {

            wait(NULL);
            running_tasks --;
        }
    }

    close(fd);

    while(running_tasks > 0){

        wait(NULL);
        running_tasks--;
    }
}