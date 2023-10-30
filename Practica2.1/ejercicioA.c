#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>


int main(){
	struct passwd *pwd;
	pwd = getpwuid(getuid());
	printf("Nombre de usuario: %s\n", pwd->pw_name);
	printf("Contraseña: %s\n", pwd->pw_passwd);
	printf("Identificador de usuario: %d\n", pwd->pw_uid);
	printf("Identificador de grupo: %d\n", pwd->pw_gid);
	printf("Directorio 'home': %s\n", pwd->pw_dir);
	printf("Shell: %s\n", pwd->pw_shell);

	if(pwd->pw_uid != geteuid())
		printf("Bit setuid activo\n");
	else 
		printf("Bit setuid no activo\n");

	if(pwd->pw_gid != getegid())
		printf("Bit setgid activo\n");
	else 
		printf("Bit setgid no activo\n");
		
	return 0;
}

