#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>


int main(){
	char* path = "../Descargas";
	if(pathconf(path, _PC_LINK_MAX) != -1)
		printf("El número máximo de enlaces: %ld\n", pathconf(path, _PC_LINK_MAX));
	else 
		printf("Error %d: %s\n", errno, strerror(errno));
	printf("El tamaño máximo de una ruta: %ld\n", pathconf(path, _PC_PATH_MAX));
	printf("El tamaño de un nombre de fichero: %ld\n\n", pathconf(path, _PC_NAME_MAX));

	printf("Devuelve un valor no nulo si el cambio del propietario del fichero está restringido: %ld\n", pathconf(path, _PC_CHOWN_RESTRICTED));
	printf("Número máximo de bytes que pueden escribirse atómicamente en la tubería: %ld\n", pathconf(path, _PC_PIPE_BUF));
	return 0;
}
