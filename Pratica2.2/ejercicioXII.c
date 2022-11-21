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

    newfd = dup(oldfd);
    printf("Redireccionamiento dup: %d\n", newfd);
    int result = dup2(oldfd, result);
    printf("Redireccionamiento dup2: %d\n", result);

    return 0;
}
