#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>


int main(){
	printf("Longitud máxima de los argumentos: %ld\n", sysconf(_SC_ARG_MAX));
	printf("El número máximo de hijos y : %ld\n", sysconf(_SC_CHILD_MAX));
	printf("El número máximo de ficheros abiertos: %ld\n\n", sysconf(_SC_OPEN_MAX));

	printf("Número de ticks de reloj por segundo (Hz): %ld\n", sysconf(_SC_CLK_TCK));
	printf("Tamaño de página en bytes: %ld\n", sysconf(_SC_PAGESIZE));
	return 0;
}

