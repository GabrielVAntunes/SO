#include <sys/types.h>
#include <stdio.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

#define BUFFER_SIZE 100 //número de bytes que vamos ler no arquivo

int main(){
    
    ssize_t bytes_lidos, bytes_escritos;
    char buffer[BUFFER_SIZE];

    while((bytes_lidos = read(0, buffer, BUFFER_SIZE)) > 0) { 
        /* 0 - canal de entrada (0 - ler / 1 - escrever / 2 - mensagens de erro)
           buffer - Espaço onde os bytes lidos vão ser armazenados
           BUFFER_SIZE - número de bytes que vão ser lidos
        */
        
        printf("li %ld bytes\n", bytes_lidos);

        bytes_escritos = write(1, buffer, bytes_lidos);
        printf("Escrevi %ld bytes\n", bytes_escritos);
        
        if (bytes_lidos != bytes_escritos){
            return 1;
        }
    }
    printf("terminei com %ld \n", bytes_escritos);
    return 0;
}