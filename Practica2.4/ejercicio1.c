#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main (int argc, char *argv[]){
    //int pipe(int fd[2]);
    //./ejercicio1 echo 12345 wc -c: argv[1] argv[2] argv[3] argv[4] => argc = 5
    /*
    @Chaoran0 ➜ /workspaces/ASOR_5-A/Practica2.4 (main ✗) $ gcc -o ejercicio1 ejercicio1.c
    @Chaoran0 ➜ /workspaces/ASOR_5-A/Practica2.4 (main ✗) $ ./ejercicio1 echo 12345 wc -c
    Padre: 16112 - 16113
    Hijo: 16113 - 16112
    6
    */

    if(argc < 5){
        perror("Error: Argumento insuficiente. \n");
        exit(-1);
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
            close(fd[1]);//importante!!!!!
            dup2(fd[0],0);//extremo de lectura de la tubería
            close(fd[0]);
            execlp(argv[3], argv[3], argv[4], NULL);//ejecutará comando2 argumento2
        break;
        default: 
            printf("Padre: %d - %d\n", getpid(), pid);
            close(fd[0]);//importante!!!!!
            dup2(fd[1],1);//extremo de escritura de la tubería
            close(fd[1]);
            //int execlp(const char *file, const char *arg, .../* (char  *) NULL */);
            //comando1 argumento1 | comando2 argumento2
            execlp(argv[1], argv[1], argv[2], NULL);//ejecutará comando1 argumento1
        break;
    }

    return 0;
}
