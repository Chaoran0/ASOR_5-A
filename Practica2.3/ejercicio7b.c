#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>


int main (int argc, char *argv[]){
    //int system(const char *command);
    if (argc < 2) {
        printf("ERROR: Introduce el comando.\n");
        exit(1);
    }

    if(system(argv[1]) == -1){
        perror("Error system: ");
        exit(1);
    }
    else printf("El comando terminó de ejecutarse\n");
    return 0;
}

/*
este caso sí que muestra el mensaje "El comando terminó de ejecutarse\n", 
porque La llamada retorna cuando termina la ejecución del comando (salvo si se ejecuta en segundo plano)
Devuelve el código de finalización del comando, obtenido con waitpid(2), o -1 en caso de error.
*/
