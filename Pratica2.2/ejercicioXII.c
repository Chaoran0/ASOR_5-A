#include <unistd.h>
#include <fcntl.h>           /* Definition of AT_* constants */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


int main(int argc, char *argv[]){
    int oldfd, newfd;

    if (argc != 2){
        printf("Poner la ruta del fichero para realizar el enlace\n");
        exit(1);
    }
    
    oldfd = open(argv[1], O_CREAT|O_WRONLY|O_WRONLY, 0777);

    //int dup(int oldfd);
    //int dup2(int oldfd, int newfd);

    if(dup(oldfd) == -1)
        printf("Error en la duplicacion.\n");

    if(dup2(oldfd, 1) == -1)
        printf("Error en la duplicacion 2.\n");

    return 0;
}
