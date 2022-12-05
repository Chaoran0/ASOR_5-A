#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc, char **argv){
    int p_h[2], h_p[2];

    if(argc != 2){
        perror("Error: Argumento insuficiente. \n");
        exit(-1);
    }

    if(pipe(p_h) == -1 || pipe(h_p) == -1){
        perror("Error: Función pipe fallida. \n");
        exit(-1);
    }

    pid_t pid = fork();

    switch(pid){
        case -1:
            perror("Error: pid_t pid == -1. \n");
            exit(-1);
        break;
        case 0:
            char bufpadre;
            printf("Hijo: %d - %d\n", getpid(), getppid());
            close(p_h[1]);
            close(h_p[0]);
            for(int i = 0; i < 10; i++){
                ssize_t sizeRead= read(p_h[1], &bufpadre, 256);
                
            }
            close(p_h[0]);
            close(h_p[1]);



        break;
        default:
            printf("Padre: %d - %d\n", getpid(), pid);
            close(p_h[0]);
            close(h_p[1]);
            char *bufhijo[1];
            read(h_p[0], bufhijo, 1);
            char bufmensaje[256];
            while(bufhijo[0] == 'q'){
                printf("[Padre] Write: \n");
                scanf("%s", bufmensaje);
                write(p_h[1], bufmensaje, 256);

            }


    }


    return 0;
}
