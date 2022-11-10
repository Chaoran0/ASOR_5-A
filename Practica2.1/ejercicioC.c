#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/utsname.h>
#include <stdlib.h>


int main() {
  //time_t time(time_t *tloc);   time - get time in seconds
  //The tloc argument is obsolescent and should always be NULL in new code.  When tloc is NULL, the call cannot fail.

  time_t t = time(NULL);
  Printf("La hora, en segundos desde el Epoch: %ld\n", t);
  
  return 0;
}
