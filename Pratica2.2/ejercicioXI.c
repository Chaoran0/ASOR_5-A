#include <unistd.h>
#include <fcntl.h>           /* Definition of AT_* constants */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
//#include <sys/sysmacros.h>


int main(int argc, char *argv[]){
    int fd;

    if (argc != 2){
        printf("Poner la ruta del fichero para realizar el enlace\n");
        exit(1);
    }
    
    fd = open(argv[1], O_CREAT|O_WRONLY|O_WRONLY, 0777);//crear si no existe

    struct stat buffer;
    int statint = stat(argv[1], &buffer);
    if (statint == -1) {
		printf("ERROR: Argumento incorrecto.\n");
		exit(1);
	}

    char* regular = malloc(sizeof(char)*(5 + strlen(argv[1])));//reservar memoria
    char* symbolic = malloc(sizeof(char)*(5 + strlen(argv[1])));
    strcpy(regular, argv[1]);//copiar el contenido de argv[1]
    strcpy(symbolic, argv[1]);
	
    regular = strcat(regular, ".hard");//ponerle la extensión 
    symbolic = strcat(symbolic, ".sym");

    if(S_ISREG(buffer.st_mode)){
        printf("%s es un un fichero normal.\n", argv[1]);
        if(symlink(argv[1], symbolic) == -1)
            printf("Error: no se ha creado el enlace simbolico\n");
        else 
            printf("Enlace simbolico creado: %s\n", symbolic);
        
        if(link(argv[1], regular) == -1)
            printf("Error: no se ha creado el enlace rígido\n");
        else 
            printf("Enlace rígido creado: %s\n", regular);
    }
    else 
        printf("%s no es un fichero normal.\n", argv[1]);

    return 0;
}
