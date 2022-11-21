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

    struct stat buffer;
    int status = stat(argv[1], &buffer);

    if(status == -1){
        perror("Error: Status failed \n");
    }
    else{
        if(S_ISDIR(buffer.st_mode)){
            printf("La ruta %s es de un directorio\n");

        }

    }

    return 0;
}
