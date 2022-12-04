#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]){
    //int pipe(int fd[2]);
    //./ejercicio1 echo 12345 wc -c: argv[1] argv[2] argv[3] argv[4] => argc = 5

    if(argc < 5){
        perror("Error: Argumento insuficiente. \n");
        exit(0);
    }
    
    int fd[2];
    if(pipe(fd) == -1){
        perror("Error: Función pipe fallida. \n");
        exit(-1);
    }

    pid_t pid = fork();
    switch (pid){
        case -1:
            perror("Error: pid_t pid == -1. \n");
            exit(-1);
        break;
        case 0: 
            printf("Hijo: %d - %d\n", getpid(), getppid());
            close(fd[0]);//importante!!!!!
            dup2(fd[1],1);
            close(fd[1]);
        break;
        default: 
            printf("Padre: %d - %d\n", getpid(), pid);
            close(fd[1]);//importante!!!!!
            dup2(fd[0],0);
            close(fd[0]);
        break;
    }



    return 0;
}
