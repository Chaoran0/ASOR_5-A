#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/utsname.h>
#include <stdlib.h>


int main() {
   //long sysconf(int name);

  printf("The maximum length of the arguments: %ld\n", sysconf(_SC_ARG_MAX));
  printf("The maximum number of simultaneous processes per user ID: %ld\n", sysconf(_SC_CHILD_MAX));
  printf("The maximum number of files that a process can have open at any time: %ld\n", sysconf(_SC_OPEN_MAX));
 
  return 0; 
}
