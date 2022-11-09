#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


int main() {
  int i;
  for (i = 0; i < 255; i++)
    if(setuid(2) == -1){
       printf("Error: %d, %s\n", i, strerror(i));
   return 1;
}
