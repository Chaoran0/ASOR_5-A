#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/utsname.h>
#include <stdlib.h>
#include <pwd.h>

int main() {
   // getuid devuelve el identificador de usuario real del proceso actual.
   // geteuid devuelve el identificador de usuario efectivo del proceso actual.
  printf("UID: %d\n", getuid());
  printf("EUID: %d\n", geteuid());
  
  //struct passwd *getpwuid(uid_t uid);
  struct passwd *pwd;
  pwd = getpwuid(getuid());
  printf("Username: %s\n", pwd->pw_name);
  printf("Home directory: %s\n", pwd->pw_dir);
  printf("User info: %s\n", pwd->pw_gecos);
  
  if (geteuid() != getuid())
	  printf("bit setuid: Activado \n");
  
  return 0;
}
