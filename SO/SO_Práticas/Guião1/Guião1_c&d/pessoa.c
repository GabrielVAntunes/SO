#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pessoa.h"

#define FILENAME "lista_pessoas.txt"

// Este ficheiro servirá apenas para definir as funções auxiliares que vamos utilizar na main 
// (Estas funções estão abstratamente definidas no ficheiro "pessoas.h")

// Esta função vai receber um nome e uma idade e vai registar a pessoa no ficheiro "lista_pessoas.txt"
int add_person(char *name, int age){

    // Abrimos o ficheiro, neste caso para escrita pois apenas vamos registar a pessoa
    // Expliquei mais sobre estas flags na alínea anterior
    int fd = open(FILENAME, O_WRONLY | O_CREAT | O_APPEND, 0600);
    if (fd == -1) return -1;

    struct Person p;
    p.age = age;
    strcpy(p.name, name);

    ssize_t pessoa_bytes = sizeof(p);

    // Depois de inicializar um objeto pessoa com os valores de entrada desta função, vamos escreve-lo no ficheiro
    ssize_t bytes_escritos = write(fd, &p, pessoa_bytes);
    if (bytes_escritos < 0) return -1;

    printf("Adicionei a pessoa:\n "
            "nome: %s,\n" 
            "idade: %d.\n", p.name, p.age);

    close(fd);

    return 0;
}

// Esta função vai listar as N primeiras pessoas do ficheiro
int list_people(int N) {
    
    // Abrimos o ficheiro apenas para ler 
    int fd = open(FILENAME, O_RDONLY);
    if (fd == -1) return -1;

    // Criamos um objeto pessoa genérico que vamos usar para guardar a informação lida
    struct Person p;

    for(int i = 0; i < N; i++){

        // Vamos ler uma pessoa de cada vez e escrever as suas informações para o utilizador ver
        ssize_t bytes_lidos = read(fd, &p, sizeof(p));
        if(bytes_lidos < sizeof(p)) break;

        printf("Pessoa nº %d:\n", i+1);
        printf("Nome: %s\n", p.name);
        printf("Idade: %d\n", p.age);
        printf("\n");
    }

    close(fd);

    return 0;
}

// Esta função vai procurar um utilizador pelo nome e atualizar a sua idade
int update_age(char *name, int age){

    // Abrimos o ficheiro tanto para ler como para escrever
    int fd = open(FILENAME, O_RDWR);
    if(fd == -1) return -1;

    // Criamos um objeto pessoa genérico para registar a informação
    // Criamos também uma variavel found para confirmar ao utilizador se efetivamente encontramos a pessoa ou não
    Person p;
    int found = 0;
    ssize_t bytes_lidos;

    // Vamos ler continuamente uma pessoa de cada vez enquanto houver pessoas para ler
    while((bytes_lidos = read(fd, &p, sizeof(Person))) > 0) {
        if(bytes_lidos != sizeof(Person)) {
            close(fd);
            return -1;
        }

        //Verificamos se o nome da pessoa atual é igual ao nome que recebemos
        if(strcmp(p.name, name) == 0) {

            p.age = age;

            // A função lseek vai alterar a posição que estamos a ler no ficheiro
            /* 
            Neste caso usamos a flag SEEK_CUR para indicar que estamos a apontar para a posição atual
            e subtraimos uma pessoa para voltarmos atrás uma pessoa ou seja a proxima pessoa que vamos ler
            vai ser a mesma que acabamos de ler
            */ 
            /* lseek Flags:
            - SEEK_CUR - posição atual
            - SEEK_END - final do ficheiro
            - SEEK_SET - inicio do ficheiro
            */
            if(lseek(fd, -sizeof(Person), SEEK_CUR) == -1) {
                close(fd);
                return -1;
            }

            // Depois de mover a posição do apontador vai reescrever a pessoa na lista, agora com o nome atualizado
            if(write(fd, &p, sizeof(Person)) != sizeof(Person)) {
                close(fd);
                return -1;
            }

            found = 1;
            break;
        }
    }
    return found;
}

// As seguintes 2 funções são alterações propostas para a alínea d)
// add_perso_gives_position tem o mesmo proposito que a função add_person 
//mas com a diferença de que devolve a posição onde foi adicionada a pessoa

int add_person_gives_position(char *name, int age){

    int fd = open(FILENAME, O_RDWR | O_CREAT | O_APPEND, 0666);
    if (fd == -1) return -1;

    struct Person put;
    strcpy(put.name, name);
    put.age = age;

    Person p;

    ssize_t bytes_lidos;
    int i = 1;

    while((bytes_lidos = read(fd, &p, sizeof(Person))) > 0){
        if (bytes_lidos < sizeof(Person)) break;

        i ++;
    }

    if(write(fd, &put, sizeof(Person)) == -1){
        close(fd);
        return -1;
    }

    printf("Adicionei a pessoa:\n "
            "nome: %s,\n" 
            "idade: %d.\n", put.name, put.age);

    close(fd);
    return i;
}

// a função update_age_by_num utiliza o valor que retiramos da add_person_gives_position
//e vai alterar a idade consoante a posição da pessoa na lista
int update_age_by_num(int position, int age){

    int fd = open(FILENAME, O_RDWR);
    if (fd == -1) return -1;

    Person p;
    int found = 0;
    ssize_t bytes_lidos;
    int i = 1;

    while((bytes_lidos = read(fd, &p, sizeof(Person))) > 0){

        if (bytes_lidos != sizeof(Person)){
            close(fd);
            return -1;
        } 

        if (i == position) {

            p.age = age;

            if(lseek(fd, -sizeof(Person), SEEK_CUR) == -1){
                close(fd);
                return -1;
            }

            if(write(fd, &p, sizeof(Person)) == -1) {
                close(fd);
                return -1;
            }

            found = 1;
            break;
        }

        i++;
    }
    return found;
}




