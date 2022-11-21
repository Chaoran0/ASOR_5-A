#include <unistd.h>
#include <fcntl.h>           /* Definition of AT_* constants */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int fd;

    if (argc != 2){
        printf("Poner el nombre del archivo a crear/leer/escribir\n");
        exit(1);
    }
    
    fd = open(argv[1], O_CREAT|O_WRONLY|O_WRONLY, 0777);

    const char fd1 = fd;
    const char x1 = "prob11.txt";
    //const char x2 = "prob11s.txt";
    link(&fd1, &x1);
    //symlink(&fd1, &x2);


    return 0;
}
