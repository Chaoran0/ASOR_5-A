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

/*
Comando: gcc -o ejer1 ejer1.c
         ./ejer1

Resultado
Error: : Operation not permitted
porque no existe el usuario 2, y setuid(2) = -1

*/
