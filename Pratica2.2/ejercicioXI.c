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

    link(argv[1], "x.txt");
    symlink(argv[1], "y.txt");


    return 0;
}

/*
usuario_vms@portatil:~/Descargas$ gcc -o ejer ejer.c
usuario_vms@portatil:~/Descargas$ ./ejer 1.txt
usuario_vms@portatil:~/Descargas$ ls -l
total 31284
-rw-r--r-- 3 usuario_vms users       17 nov 21 12:09 1.txt
-rwxr-xr-x 1 usuario_vms users    16104 nov 21 12:09 ejer
-rw-r--r-- 1 usuario_vms users      424 nov 21 12:09 ejer.c
-rw-r--r-- 3 usuario_vms users       17 nov 21 12:09 x.txt
lrwxrwxrwx 1 usuario_vms users        5 nov 21 12:10 y.txt -> 1.txt

x.txt e y.txt no existían
*/
