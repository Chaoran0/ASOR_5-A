#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
 
  /* Variables */
  int fd;
  char buffer[1024];
  int numbytes;
 
  mode_t prev = umask(750);

  if (argc != 2){
    printf("Fallo en comando\n");
    exit(1);
  }
 
  fd = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0777);
  
  printf("Resultado: %d\n", fd);
  close(fd);
  

  /*const char PATH[]="/workspaces/ASOR_5-A/Pratica2.2/ejer5.txt";

  int df = open(PATH, O_CREAT, 0645);

  printf("Resultado = %i\n", df);
 
  close(df);*/

  return 0;
}
