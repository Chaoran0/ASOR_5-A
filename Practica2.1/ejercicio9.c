/*
EL bit setuid es asignable a ficheros ejecutables, y permite que cuando un usuario ejecute dicho fichero, 
el proceso adquiera los permisos del propietario del fichero ejecutado.

¿Cuándo podríamos asegurar que el fichero del programa tiene activado el bit setuid?
Podríamos asegurarlo en el momento que sea ejecutado por otro usuario que no sea su dueño. Si el bit está activo indica que el usuario efectivo es el dueño.
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/utsname.h>
#include <stdlib.h>

int main() {
   // getuid devuelve el identificador de usuario real del proceso actual.
   // geteuid devuelve el identificador de usuario efectivo del proceso actual.
  printf("UID: %d\n", getuid());
	printf("EUID: %d\n", geteuid());
	if (geteuid() != getuid())
		printf("bit setuid: Activado \n");
  
  return 0;
}
