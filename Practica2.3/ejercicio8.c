#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main (int argc, char *argv[]){
    //int execve(const char *filename, char *const argv[], char *const envp[]);
    if (argc < 2) {
        printf("ERROR: Introduce el comando.\n");
        exit(1);
    }

    pid_t pid = fork();
    switch(pid){
        case -1:
            perror("Error");
            exit(1);
        case 0:
            setsid();
            chdir("/tmp");
            printf("Hijo %i (padre: %i)\n", getpid(), getppid());
            int fd = open("/tmp/daemon.out",O_CREAT | O_RDWR, 0777);
            int err = open("/tmp/daemon.err",O_CREAT | O_RDWR, 0777);
            int dn = open("/dev/null",O_CREAT | O_RDWR, 0777);
            /*tanto execl como execv ignoran la variable PATH, que contiene las rutas de búsqueda. 
            Para tener en cuenta esta variable pueden usarse las versiones execlp o execvp. */
            //char *newargv[] = {argv[1], NULL};
            dup2(fd, 1); //dup hace que el fichero no solo tenga un descriptor sino tambien otro que en este caso es 2
            dup2(err, 2);
            dup2(dn, 0);
            if (execvp(argv[1], argv+1) == -1) {
                printf("ERROR execvp\n");
                exit(-1);
            }

            
        break;
        default:
            printf("Padre %i (hijo: %i)\n", getpid(), pid);
        break;
    }
    return 0;
}
