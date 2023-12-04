#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>



int main (int argc, char **argv){
    if (argc != 1) {
        printf("Usage: %s <string>\n", argv[0]);
        exit(-1);
    }

    int p_h[2], h_p[2];

    if(pipe(p_h) == -1 || pipe(h_p) == -1){
        perror("Error: Función pipe fallida. \n");
        exit(-1);
    }

    pid_t pid = fork();

    switch(pid){
        case -1:
            perror("Error: pid_t pid == -1\n");
            exit(-1);
            break;
        case 0:
            //printf("Hijo:%d - %d\n", getpid(), getppid());
            char buff_message[256];
            close(h_p[0]);
            close(p_h[1]);
            for(int i = 0; i<10; i++){
                read(p_h[0], buff_message, 256);
                printf("[Hijo]Read: %s\n", buff_message);
                sleep(1);
                write(h_p[1], "l", 1);
            }
            write(h_p[1], "q", 1);

            close(h_p[1]);
            close(p_h[0]);
            break;
        default:
            //printf("Padre:%d - %d\n", getpid(), pid);
            close(h_p[1]);
            close(p_h[0]);
            char buff_h[1];
            char buff_p[256];
            while(buff_h[0] != 'q'){
                printf("[Padre]Write: ");
                scanf("%s", buff_p);
                write(p_h[1], buff_p, 256);
                read(h_p[0], buff_h, 1);
                
            }
            close(h_p[0]);
            close(p_h[1]);
            break;
    }
        
    return 0;






}
