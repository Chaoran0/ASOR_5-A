#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>


int main (int argc, char *argv[]){
    //int execve(const char *filename, char *const argv[], char *const envp[]);
    if (argc < 2) {
        printf("ERROR: Introduce el comando.\n");
        exit(1);
    }

    char *newargv[] = {"/bin/ls", "-l", NULL};
    char *envp[] = {NULL};
    //if(execve("/bin/ls", newargv, NULL) == -1){
    if(execve(argv[1], argv+1, NULL) == -1){
        perror("Error execve: ");
        exit(1);
    }
    else printf("El comando terminó de ejecutarse\n");
    return 0;
}
