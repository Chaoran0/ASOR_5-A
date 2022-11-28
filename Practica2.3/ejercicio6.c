#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

void attribute (){
    printf("    PID: %d\n", getpid());//identificador único (Process ID, PID)
    printf("    PPID: %d\n", getppid());//Parent Process ID, PPID
    printf("    PGID: %d\n", getpgid(getpid()));//identificador del grupo de procesos
    printf("    SID: %d\n", getsid(getpid()));//identificador de sesión

    //int getrlimit(int resource, struct rlimit *rlim);
    struct rlimit rlim;
    if(getrlimit(RLIMIT_NOFILE, &rlim) == -1){
        perror("Error\n");
        exit(1);
    }
    else
        printf("    Num Max de ficheros que se puede abrir: %ld\n", rlim.rlim_max);

    //char *getcwd(char *buffer, size_t size);
    char buffer[2000];
    int size = 2000;
    if(getcwd(buffer, (size_t) size) == NULL){
        perror("Error\n");
        exit(1);
    }
    else
        printf("    El directorio de trabajo actual: %s\n", buffer);
}

int main (int argv, char *argc[]){
    pid_t pid = fork();
    switch(pid){
        case -1:
            perror("Error");
            exit(1);
        case 0:
            setsid();
            chdir("/tmp");
            printf("Hijo %i (padre: %i)\n", getpid(), getppid());
            printf("Hijo: \n"); attribute();
            pause();
        break;
        default:
            printf("Padre %i (hijo: %i)\n", getpid(), pid);
            printf("Padre: \n"); attribute();
        break;
    }


    return 0;
}
//Hijo termina antes que padre: su PPID se ha cambiado, antes PPID es PID de padre
/*Padre 54421 (hijo: 54422)
Padre: 
    PID: 54421
    PPID: 49328
    PGID: 54421
    SID: 49328
    Num Max de ficheros que se puede abrir: 1048576
    El directorio de trabajo actual: /home/usuario_vms/Descargas
Hijo 54422 (padre: 54421)
Hijo: 
    PID: 54422
    PPID: 3247
    PGID: 54422
    SID: 54422
    Num Max de ficheros que se puede abrir: 1048576
    El directorio de trabajo actual: /tmp*/
