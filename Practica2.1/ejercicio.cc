#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>


int main() {
   setuid(0);
   setuid(2);
    perror();
   return 1;
}
