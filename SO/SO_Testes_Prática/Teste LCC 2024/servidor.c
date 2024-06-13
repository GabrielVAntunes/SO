/*Considere um motor de pesquisa baseado em Inteligência Artificial que dada a interrogação de utlizadores (argumento prompt)
responde em formato textual. Este motor é composto por um conjunto encadeado de programas.

• Para cada pedido, o ficheiro executável filter (Le, Eliter «prompt ») seleciona ficheiros que contêm conteúdo relacionado com a interrogação,
escrevendo em formato binário para o stdout os seus caminhos.

• Entretanto, o ficheiro executável execute (ie, execute «prompt.») lé do stdin os caminhos dos ficheiros fitrados.
um a um, e gere conteúdo em binário de acordo com a interrogação do utilizador, o qual é escrito no stdout.

• O ficheiro executável merge (ie, merge <prompt>) lê do stdin conteúdo binário resultante de interrugações e gera uma resposta 
para o utilizador  em formato textual (escrita no stdout).

1.
 Escreva o programa SOGPT de forma a implementar o comportamento acima descrito.
Valorização: otimize a fase de execute desencadeando o seu processamento concorrente com N procensos.

2.
    Considere o programa cliente(search_prompt) que recorre ao pipe com nome fifo_server para enviar um pedido de pesquisa 
ao programa servidor. o pedido (estrutura req q) contém o pid do programa cliente e o prompt a ser processado pelo servidor .
por fim o programa cliente notifica  o utilizador quando o pedido é completado indicando lhe o seu identificador.

    int main (int argc, char *argv[]{
        Req q;
        q.pid = getpid();
        q.prompt = strdup(argv[1]);

        char fifoc_name[30];
        sprintf(fifoc_name, "fifo_client_%d", q.pid);
        mkfifo(fifoc_name, 0666); // linha 8

        int fds = open("fifo_sever", O_WRONLY);
        write(fds, &q, sizeof(q));

        close(fds);

        int req_id;
        int fdc = open(fifoc_name, O_RDONLY); // linha 15
        read(fdc, &req_id, sizeof(int));
        printf("Request &d completed", req_id);
        close(fdc);

        unlink(fifoc_name);
        return 0;
    })

a). 
    Escreva o programa servidor que, através do pipe nome fifo_server, deverá receber pedidos de pesquisa de 
clientes(i.e search_prompt) e executar os mesmos sequencialmente, utilizando o programa SOGPT. Para cada 
pedido, o servidor deve atribuir-lhe um identificador único, a ser enviado ao cliente assim que o mesmo termina.*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>

// Não tenho a certeza se esta resolução está bem, não entendi 
//muito bem o proposito de exercicio

// não soube responder á alínea b) mas penso que neste caso funcionaria
//porque o servidor vai esperar dentro do loop que o fifo seja aberto no cliente

int servidor(int argc, char *argv[]){

    Req q;
    int c = 1;
    char fifo_name[30];

    int fifo_fd = open("fifo_server", O_RDONLY);
    while(read(fifo_fd, &q, sizeof(Req)) > 0){

        sprintf(fifo_name, "fifo_client_%d", q.pid);
        mkfifo(fifo_name, 0666);
        int return_fd = open(fifo_name, O_WRONLY);

        SOGPT(q.prompt);

        write(return_fd, &c, sizeof(int));
        close(return_fd);
        unlink(fifo_name);

        c++;
    }

    close(fifo_fd);
    unlink("fifo_server");
}