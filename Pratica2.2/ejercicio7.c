#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
 
  /* Variables */
  int fd;
 
  mode_t mask = umask(0027);

  if (argc != 2){
    printf("Error: pon el nombre del fichero a abrir.\n");
    exit(1);
  }
 
  fd = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0777);
  

  printf("Umask: %o\n", mask2);


  close(fd);

  return 0;
}
