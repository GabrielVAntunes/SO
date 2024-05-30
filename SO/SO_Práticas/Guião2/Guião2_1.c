#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv){

    // As funções getpid e getppid retornam o valor pid (Process IDentifier)
    //do processo atual e do seu processo pai respetivamente
    pid_t pid = getpid();
    pid_t ppid = getppid();

    printf("O Pid do processo é: %d\n", pid);
    printf("O Pid do processo pai é: %d\n", ppid);
}

