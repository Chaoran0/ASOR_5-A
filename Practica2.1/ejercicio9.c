/*
EL bit setuid es asignable a ficheros ejecutables, y permite que cuando un usuario ejecute dicho fichero, 
el proceso adquiera los permisos del propietario del fichero ejecutado.

¿Cuándo podríamos asegurar que el fichero del programa tiene activado el bit setuid?
Podríamos asegurarlo en el momento que sea ejecutado por otro usuario que no sea su dueño. Si el bit está activo indica que el usuario efectivo es el dueño.
*/

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>


int main(){
	if(getuid() != -1)
		printf("UID real: %d\n", getuid());
	else 
		printf("Error %d: %s\n", errno, strerror(errno));
	
	if(getuid() != -1)
		printf("UID efectivo: %d\n", geteuid());
	else 
		printf("Error %d: %s\n", errno, strerror(errno));
		

	if(getuid() != -1)
		printf("GID real: %d\n", getgid());
	else 
		printf("Error %d: %s\n", errno, strerror(errno));

	if(getuid() != -1)
		printf("GID efectivo: %d\n", getegid());
	else 
		printf("Error %d: %s\n", errno, strerror(errno));

	if(getuid() != geteuid())
		printf("Bit setuid activo\n");
	else 
		printf("Bit setuid no activo\n");
	if(getgid() != getegid())
		printf("Bit setgid activo\n");
	else 
		printf("Bit setgid no activo\n");
	return 0;
}

