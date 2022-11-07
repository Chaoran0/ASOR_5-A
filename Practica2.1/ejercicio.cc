#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>


int main() {
   if(setuid(2) == -1){
      perror("Error: ");
   }
   else
      printf("Correct.");
   return 1;
}
