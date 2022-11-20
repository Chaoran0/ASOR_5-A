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
 
  mode_t mask = umask(0027);

  if (argc != 2){
    printf("Uso: %s origen destino\n", argv[0]);
    exit(1);
  }
 
  fd = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0777);
  
  mode_t mask2 = umask(mask);

    printf("Umask: %i\n", mask2);


  close(fd);

  return 0;
}
