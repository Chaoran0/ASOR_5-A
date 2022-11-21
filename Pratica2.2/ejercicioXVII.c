#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[]){
    //int lockf(int fd, int cmd, off_t len);
    //unsigned int sleep(unsigned int seconds);

    int fd;

    if(argc != 2){
        printf("Error: argumento incorrecto \n");
        exit(1);
    }

    struct stat buffer;
    int status = stat(argv[1], &buffer);

    if(status == -1){
        perror("Error: Status failed \n");
    }
    else{
        if(S_ISDIR(buffer.st_mode)){
            printf("La ruta %s es de un directorio\n", argv[1]);
            DIR *diropen = opendir(argv[1]);
            struct dirent *now = readdir(diropen);
            while (now != NULL){
                
                char *path = (char *) malloc(sizeof(char)*(strlen(argv[1]) + strlen(now->d_name) + 3));//or char path[PATH_MAX];
                struct stat estatus;
                stat(now->d_name, &estatus);
                if(S_ISLNK(estatus.st_mode)){
                    strcpy(path, argv[1]);
                    strcat(path, "/");
                    strcat(path, now->d_name);
                    printf("%s es un fichero simbólico: ", path);

                    char buff[_PC_PATH_MAX];
                    readlink(path, buff, (size_t)_PC_PATH_MAX);
                    printf("%s -> %s\n", now->d_name, buff);
                    //free(buff);
                }
                else if(S_ISREG(estatus.st_mode)){
                    strcpy(path, argv[1]);
                    strcat(path, "/");
                    strcat(path, now->d_name);
                    printf("%s es un fichero regular: ", path);
                    printf("%s*\n", now->d_name);
                }
                else if(S_ISDIR(estatus.st_mode)){
                    strcpy(path, argv[1]);
                    strcat(path, "/");
                    strcat(path, now->d_name);
                    printf("%s es un directorio: ", path);
                    printf("%s/\n", now->d_name);
                }
                else printf("Error: %s", now->d_name);
                free(path);
                
                now = readdir(diropen);
            }
            
        }
        else {
            perror("Error: La ruta no es de un directorio\n");
            exit(EXIT_FAILURE);
        }

    }

    return 0;
}
