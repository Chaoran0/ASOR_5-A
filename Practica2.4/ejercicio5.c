#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>

int main(int argcc, char **argv){
    char tub1 = "tub1";
    char tub2 = "tub2";
    char buffer[256];
    if(mkfifo("tub1", 0777) == -1){
        perror("Error: mkfifo failed. \n");
        exit(-1);
    }
    if(mkfifo("tub2", 0777) == -1){
        perror("Error: mkfifo failed. \n");
        exit(-1);
    }

      //Abrimos ambas tuberias, el parametro O_NONBLOCK sirve evitar el el archivo se abra para lectura y se bloquee para escritura.
    int pipe1 = open(tub1, O_RDONLY | O_NONBLOCK);
    int pipe2 = open(tub2, O_RDONLY | O_NONBLOCK);
    if(pipe1 == -1 || pipe2 == -1){
        perror("Error: open failed. \n");
        exit(-1);
    }

    /*void FD_CLR(int fd, fd_set *set);
       int  FD_ISSET(int fd, fd_set *set);
       void FD_SET(int fd, fd_set *set);
       void FD_ZERO(fd_set *set);*/
    fd_set rpipes;
    while(1){
        FD_ZERO(&rpipes);//inicializa un conjunto como conjunto vacío
        FD_SET(pipe1, &rpipes);//añade un pipe1 al conjunto rpipes
        FD_SET(pipe2, &rpipes);//añade un pipe2 al conjunto rpipes

        int rc = select((pipe1 < pipe2) ? pipe2 + 1 : pipe1 + 1, &rpipes, NULL, NULL, NULL);




    }


    close(pipe1);
    close(pipe2);

    return 0;
}
