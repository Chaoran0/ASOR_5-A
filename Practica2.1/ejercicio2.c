#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


int main() {
    int x;
   if(setuid(2) == -1){
       printf("Error: %d, %s\n", errno, strerror(errno));
      //perror("Error: ");

   }
   else
      printf("Correct.");
   return 0;
}
