#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>
#include <string.h>

int main(int argcc, char **argv){
    char *tub1 = "tub1";
    char *tub2 = "tub2";
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
    int rc, actualpipe;
    int tub;
    while(rc != -1){
        FD_ZERO(&rpipes);//inicializa un conjunto como conjunto vacío
        FD_SET(pipe1, &rpipes);//añade un pipe1 al conjunto rpipes
        FD_SET(pipe2, &rpipes);//añade un pipe2 al conjunto rpipes

        rc = select((pipe1 < pipe2) ? pipe2 + 1 : pipe1 + 1, &rpipes, NULL, NULL, NULL);

        if(FD_ISSET(pipe1, &rpipes)){
            actualpipe = pipe1;
            tub = 1;
        }
        else if(FD_ISSET(pipe2, &rpipes)){
            actualpipe = pipe2;
            tub = 2;
            
        }
        ssize_t readsize = 256;
        while (readsize == 256) {

            readsize = read(actualpipe, buffer, 256);

            if (readsize == -1) {
                perror("Error: Read failed.\n");
                close(pipe1);
                close(pipe2);
                exit(-1);
            }

            buffer[readsize] = '\0';
            printf("Tuberia %d: %s", tub, buffer);
        }

        if(tub == 1 && readsize != 256){
            close(pipe1);
            pipe1 = open(tub1, O_RDONLY | O_NONBLOCK);
            if(pipe1 == -1){
                perror("Error: open failed. \n");
                exit(-1);
            }
        }
        else if(tub == 2 && readsize != 256){
            close(pipe2);
            pipe2 = open(tub2, O_RDONLY | O_NONBLOCK);
            if(pipe2 == -1){
                perror("Error: open failed. \n");
                exit(-1);
            }
        }
    }


    close(pipe1);
    close(pipe2);

    return 0;
}
