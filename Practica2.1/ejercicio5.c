#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/utsname.h>
#include <stdlib.h>


int main() {
   //int uname(struct utsname *buf);
  struct utsname buf;
  if(uname(&buf) == 0){
    printf("Operating system name (e.g., Linux): %s\n", buf.sysname);
    printf("Name within 'some implementation-defined network': %s\n", buf.nodename);
    printf("Operating system release (e.g., '2.6.28'): %s\n", buf.release);
    printf("Operating system version: %s\n", buf.version);
    printf("Hardware identifier: %s\n", buf.machine);
  }
  else 
    printf("Error: %d, %s\n", errno, strerror(errno));
}
