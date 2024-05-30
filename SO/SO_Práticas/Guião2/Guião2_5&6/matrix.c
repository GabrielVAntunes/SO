#include "matrix.h"

int **createMatrix() {

    // seed random numbers
    srand(time(NULL));

    // Allocate and populate matrix with random numbers.
    printf("Generating numbers from 0 to %d...", MAX_RAND);
    int **matrix = (int **) malloc(sizeof(int*) * ROWS);
    for (int i = 0; i < ROWS; i++) {
        matrix[i] = (int*) malloc(sizeof(int) * COLUMNS);
        for (int j = 0; j < COLUMNS; j++) {
            matrix[i][j] = rand() % MAX_RAND;
        }
    }
    printf("Done.\n");

    return matrix;
}

void printMatrix(int **matrix) {

    for (int i = 0; i < ROWS; i++) {
        printf("%2d | ", i);
        for (int j = 0; j < COLUMNS; j++) {
            printf("%7d ", matrix[i][j]);
        }
        printf("\n");
    }
}

/* Usei como base a estrutura do exercicio 4 deste mesmo guião para que fosse possivel correr 
todas as linhas da matriz em simultaneo tornando assim o processo mais rápido
*/
int valueExists(int **matrix, int value) {

    pid_t pid;
    int status;
    int found = 0;

    // Cria N-Processos, sendo N o número de linhas da matriz
    for(int i = 0; i < ROWS; i++){

        if((pid = fork()) == -1) _exit(-1);

        if(pid == 0){
            
            for(int j = 0; j < COLUMNS; j++){
                if(matrix[i][j] == value) _exit(i);
            }

            _exit(-1);
        }
    }

    for(int i = 0; i < ROWS; i++){
        pid_t pid_child = wait(&status);
        if(pid_child == -1) _exit(-1);

        if(WIFEXITED(status)){
            int exit_status = WEXITSTATUS(status);
            /* O wait apenas retorna valores entre 1 e 255 pelo que ao usar _exit(-1) nos casos de erro
            o status resultante será 255, isto não trará problemas desde que o nº de colunas
            da matriz não ultrapasse 255 inclusive
            */
            if(exit_status != 255){
                printf("Processo %d: O valor existe e está na linha %d\n\n",pid_child, exit_status);
                found = 1;
            }
        }
    }
    return found;
}

// As seguintes 2 funções são apenas auxiliares para facilitar a ordenação dos arrays
int compare(const void *a, const void *b){
    return(*(int*)a - *(int*)b);
}

void sortline(int *list, int length, int linha){
    qsort(list, length, sizeof(int), compare);
    printf("Linha %d ordenada: \n", linha);
    for(int i = 0; i < length; i++){
        printf("%d ", list[i]);
    }

    printf("\n\n");
}
// ex.6
// Apenas adaptei um pouco a alínea anterior para que quando o valor seja encontrado uma cópia da linha
//em questão ordenada seja impressa para o utilizador
void linesWithValue(int **matrix, int value) {

    pid_t pid;
    int list[COLUMNS];

    for (int i = 0; i < ROWS; i++){

        if((pid = fork()) == -1) _exit(-1);

        if(pid == 0) {
            
            for(int j = 0; j < COLUMNS; j++){

                if(matrix[i][j] == value){

                    // Apenas ordenamos uma cópia da linha onde foi encontrado o valor para não 
                    //alterar os valores da matriz original
                    memcpy(list, matrix[i], COLUMNS * sizeof(int));
                    sortline(list, COLUMNS, i);
                    _exit(i);
                }
            }

            _exit(-1);
        }
    }

    /* Diferentemente do exercício anterior neste caso apenas usei wait(NULL) porque não
    precisamos de saber nada sobre o status de término dos processos filho, pois a ordenação
    do vetor ocorre no próprio processo filho, o pai não tem de gerir informação posteriormente
    */
    for(int i = 0; i < ROWS; i++){
        
        wait(NULL); 
    }

}