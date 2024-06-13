/*Considere um motor de pesquisa baseado em Inteligência Artificial que dada a interrogação de utlizadores (argumento prompt)
responde em formato textual. Este motor é composto por um conjunto encadeado de programas.

• Para cada pedido, o ficheiro executável filter (Le, Filter «prompt ») seleciona ficheiros que contêm conteúdo relacionado com a interrogação,
escrevendo em formato binário para o stdout os seus caminhos.

• Entretanto, o ficheiro executável execute (ie, execute «prompt.») lé do stdin os caminhos dos ficheiros fitrados.
um a um, e gere conteúdo em binário de acordo com a interrogação do utilizador, o qual é escrito no stdout.

• O ficheiro executável merge (ie, merge <prompt>) lê do stdin conteúdo binário resultante de interrugações e gera uma resposta 
para o utilizador  em formato textual (escrita no stdout).

1.
 Escreva o programa SOGPT de forma a implementar o comportamento acima descrito.
Valorização: otimize a fase de execute desencadeando o seu processamento concorrente com N processos.*/

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5

int SOGPT(char *prompt){

    int pipe_fd[2][2];
    pipe(pipe_fd[0]);

    pid_t pid = fork();

    if(pid == 0){
        close(pipe_fd[0][0]);
        
        dup2(pipe_fd[0][1], 1);
        close(pipe_fd[0][1]);

        execlp("filter", "filter", *prompt, NULL);

        _exit(EXIT_FAILURE);
    }

    close(pipe_fd[0][1]);

    wait(NULL);

    pipe(pipe_fd[1]);

    for (int i = 0; i < N; i++){

        pid = fork();

        if(pid == 0){

            dup2(pipe_fd[0][0], 0);
            close(pipe_fd[0][0]);

            dup2(pipe_fd[1][1], 1);
            close(pipe_fd[1][1]);

            execlp("execute", "execute", NULL);

            _exit(EXIT_FAILURE);
        }

    }

    close(pipe_fd[0][0]);
    close(pipe_fd[1][1]);

    for (int i = 0; i < N; i++){
        wait(NULL);
    }

    pid = fork();

    if(pid == 0){
        
        dup2(pipe_fd[1][0], 0);
        close(pipe_fd[1][0]);

        execlp("merge", "merge", NULL);

        _exit(EXIT_FAILURE);
    }

    close(pipe_fd[1][0]);

    wait(NULL);

    return 0;
}

