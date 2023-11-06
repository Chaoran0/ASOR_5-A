#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]){
 
  /* Variables */
  int fd;
 
  mode_t mask = umask(0027);

  if (argc != 2){
    printf("Error: pon el nombre del fichero a abrir.\n");
    exit(1);
  }
 
  fd = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, mask);

 	if(fd == -1)
		printf("Error %d: %s", errno, strerror(errno));

  close(fd);

  return 0;
}
