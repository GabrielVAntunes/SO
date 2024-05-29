#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pessoa.h"

// Este código apenas tem o proposito de interpretar os argumentos de entrada 
//e consoante os mesmos decidir a função auxiliar adequada
int main(int argc, char *argv[]){

    if(argc < 3){
        printf("Usage:\n");
        printf("Add new person to the list: ./pessoas -i [name] [age]\n");
        printf("List N people: ./pessoas -l [N]\n");
        printf("Change person age: ./pessoas -u [name] [age]\n");
        printf("Change person age (v2): ./pessoas -o [position] [age]\n");
        return 1;
    }

    if (strcmp(argv[1], "-i") == 0){
        // atoi: converte String para int
        int res = add_person((argv[2]), atoi(argv[3]));
        printf("adicionei %d pessoa\n", res);
    }

    if (strcmp(argv[1], "-i2") == 0){
        int res = add_person_give_position(argv[2], atoi(argv[3]));
        printf("Adicionei a pessoa na posição %d", res);
    }

    if (strcmp(argv[1], "-l") == 0){
        int res = list_people(atoi(argv[2]));
        printf("atualizei %d pessoas\n", res);
    }

    if (strcmp(argv[1], "-u") == 0){
        int res = update_age(argv[2], atoi(argv[3]));
        printf("atualizei %d pessoas\n", res);
    }

    if (strcmp(argv[1], "-o") == 0){
        int res = update_age_by_num(atoi(argv[2]), atoi(argv[3]));
        printf ("atualizei %d pessoas\n", res);
    }
}