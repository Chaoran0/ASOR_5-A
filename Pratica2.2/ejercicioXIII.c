/*Los operadores de redirección/tubería del shell se aplican en el orden en que aparecen en la línea de comandos. 
Una vez que sabes eso y lees los operadores de la manera correcta, la diferencia se vuelve clara, así que veamos los operadores con un poco más de detalle:

FD es la abreviatura de descriptor de archivo, un número que se asocia con un archivo (objeto similar) en una base por proceso. 
Los descriptores de archivo 0 a 2 tienen un significado especial: son los flujos estándar de entrada/salida/error. 
Si ejecuta un programa en su shell sin ningún operador de redirección, están esencialmente conectados a su terminal.
Redirigir a a b significa: hacer que el FD de a se refiera a lo mismo que b, es decir, después de la redirección, los dos descriptores de archivo pueden ser utilizados indistintamente (la antigua a se pierde). 
Internamente esto sucede usando la llamada al sistema dup2.
>foo reemplaza stdout con un handle que escribe en foo
2>&1 reemplaza FD 2 (stderr) con un manejador que escribe a lo que FD 1 (stdout) se refiere en ese momento.
Teniendo esto en cuenta, esto es lo que ocurre para las dos variantes:

>foo 2>&1: el shell abre un nuevo FD que escribe en foo, y redirige stdout a él, lo que significa que el FD 1 ahora escribe en foo. 
           Entonces, este FD 1 se duplica en el FD 2, cerrando implícitamente el antiguo FD 2 (que se refería a la stderr original). 
           Como resultado, ambos FDs escriben en foo.

2>&1 >foo: el shell primero duplica el FD 1 en el FD 2, de modo que los errores se escriben en stdout. Luego, crea un nuevo FD que escribe en foo y lo duplica en el FD 1. 
           Debido al orden de los operadores de redirección, esto sobreescribe el FD 1 pero el FD 2 todavía se refiere al "viejo" FD 1. 
           Como resultado, el FD 2 escribe en la antigua salida estándar (probablemente su terminal) y el FD 1 escribe en foo, que sustituye a la antigua salida estándar.
*/

#include <unistd.h>
#include <fcntl.h>           /* Definition of AT_* constants */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


int main(int argc, char *argv[]){
    int oldfd, newfd;

    if (argc != 2){
        printf("Poner la ruta del fichero para realizar el enlace\n");
        exit(1);
    }
    
    oldfd = open(argv[1], O_CREAT|O_WRONLY|O_WRONLY, 0777);

    //int dup(int oldfd);
    //int dup2(int oldfd, int newfd);

    if(dup(oldfd) == -1)
        printf("Error en la duplicacion.\n");

    newfd = dup2(oldfd, 1);
    if(newfd == -1)
        printf("Error en la duplicacion 2.\n");


    dup2(newfd, oldfd);

    return 0;
}
