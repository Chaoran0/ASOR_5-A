#include <sys/utsname.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>


int main(){
	struct utsname syst;
	if (uname(&syst) == 0){
		printf("Operating system name (e.g., 'Linux'): %s\n", syst.sysname);
		printf("Name within 'some implementation-definednetwork': %s\n", syst.nodename);
		printf("Operating system release (e.g., '2.6.28'): %s\n", syst.release);
		printf("Operating system version: %s\n", syst.version);
		printf("Hardware identifier: %s\n", syst.machine);
		#ifdef _GNU_SOURCE
			printf("NIS or YP domain name: %s\n", syst.domainname);
		#endif
	}
	else 
		printf("Error %d : %s", errno, strerror(errno));
	
}

/*
RETURN:
Operating system name (e.g., 'Linux'): Linux
Name within 'some implementation-definednetwork': pto0515
Operating system release (e.g., '2.6.28'): 5.15.0-39-generic
Operating system version: #42-Ubuntu SMP Thu Jun 9 23:42:32 UTC 2022
Hardware identifier: x86_64
*/

/*
DESCRIPTION
       uname()  returns system information in the structure pointed to by buf.
       The utsname struct is defined in <sys/utsname.h>:

           struct utsname {
               char sysname[];    /* Operating system name (e.g., "Linux") */
               char nodename[];   /* Name within "some implementation-defined
                                     network" */
               char release[];    /* Operating system release
                                     (e.g., "2.6.28") */
               char version[];    /* Operating system version */
               char machine[];    /* Hardware identifier */
           #ifdef _GNU_SOURCE
               char domainname[]; /* NIS or YP domain name */
           #endif
           };

       The length of the arrays  in  a  struct  utsname  is  unspecified  (see
       NOTES); the fields are terminated by a null byte ('\0').
RETURN VALUE
       On  success,  zero is returned.  On error, -1 is returned, and errno is
       set appropriately.

ERRORS
       EFAULT buf is not valid.
*/
