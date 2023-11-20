#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

int main (int argv, char *argc[]){
    printf("PID: %d\n", getpid());//identificador único (Process ID, PID)
    printf("PPID: %d\n", getppid());//Parent Process ID, PPID
    printf("PGID: %d\n", getpgid(getpid()));//identificador del grupo de procesos
    printf("SID: %d\n", getsid(getpid()));//identificador de sesión

    //int getrlimit(int resource, struct rlimit *rlim);
    struct rlimit rlim;
    if(getrlimit(RLIMIT_NOFILE, &rlim) == -1){
        perror("Error\n");
        exit(1);
    }
    else
        printf("Num Max de ficheros que se puede abrir: %ld\n", rlim.rlim_max);

    //char *getcwd(char *buffer, size_t size); Obtener la ruta absoluta del trabajo
    char buffer[2000];
    int size = 2000;
    printf("Size of buffer: %d\n", size);
    if(getcwd(buffer, (size_t) size) == NULL){
        perror("Error\n");
        exit(1);
    }
    else
        printf("El directorio de trabajo actual: %s\n", buffer);

    return 0;
}
