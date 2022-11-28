#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argv, char *argc[]){
    printf("PID: %d\n", getpid());//identificador único (Process ID, PID)
    printf("PPID: %d\n", getppid());//Parent Process ID, PPID
    printf("PGID: %d\n", getpgid(getpid()));//identificador del grupo de procesos
    printf("SID: %d\n", getsid(getpid()));//identificador de sesión

    return 0;
}
