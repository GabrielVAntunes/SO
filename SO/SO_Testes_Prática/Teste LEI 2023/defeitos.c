#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int defeitos(char* imagens[], int n, int max){

    int running_tasks = 0;

    pid_t pid;

    int i = 0;
    while(i < n){

        if(running_tasks < max){

            pid = fork();

            if(pid == 0){

                execlp("detectAnom", "detectAnom", imagens[i], NULL);

                _exit(EXIT_FAILURE);

            } else {

                i++;
                running_tasks++;
            }

        } else {

            wait(NULL);
            running_tasks--;
        }
    }

    while(running_tasks > 0){

        wait(NULL);
        running_tasks--;
    }  
    
    return 0;
}

