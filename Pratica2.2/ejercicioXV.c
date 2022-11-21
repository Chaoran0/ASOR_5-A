#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[]){
    //int lockf(int fd, int cmd, off_t len);
    //unsigned int sleep(unsigned int seconds);

    int fd;

    if(argc != 2){
        printf("Error: argumento incorrecto \n");
        exit(1);
    }

    fd = open(argv[1], O_CREAT|O_TRUNC|O_WRONLY, 0777);

    if(fd != -1){
        if(lockf(fd, F_TLOCK, (off_t)0) != -1){
            printf("Se ha activado el cerrojo\n");
            sleep(10);
            lockf(fd, F_ULOCK, (off_t)0);
            printf("Se ha desactivado el cerrojo\n");
            sleep(10);
        }
        else
            perror("Error: no se ha podido activar el cerrojo\n");
    }
    else{
        printf("Error: no se ha podido acceder a l fichero");
        exit(1);
    }

    return 0;
}
