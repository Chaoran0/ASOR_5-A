#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
 
  /* Variables */
  int fd;
  struct stat buffer;

  if (argc != 2){
    printf("Poner el nombre del archivo a crear/leer/escribir\n");
    exit(1);
  }
  
  int statint = stat(argv[1], &buffer);
  if (statint == -1) {
		printf("ERROR: Argumento incorrecto.\n");
		exit(1);
	}


 
  fd = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0777);



  close(fd);

  return 0;
}
