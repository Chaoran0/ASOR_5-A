#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]){
    //int pipe(int fd[2]);
    //./ejercicio1 echo 12345 wc -c: argv[1] argv[2] argv[3] argv[4] => argc = 5

    if(argc < 5){
        perror("Error: Argumento insuficiente. \n");
        exit(-1);
    }

    


    return 0;
}
