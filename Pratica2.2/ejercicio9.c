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
//unsigned int minor(dev_t dev);
//unsigned int major(dev_t dev);
  printf("MAJOR: %d\n", minor(buffer.st_dev));//st_dev: ID of device containing file 
  printf("MINOR: %d\n", major(buffer.st_dev));

  printf("I-Node: %d\n",buffer.st_ino); //st_ino: Inode number 
	
  printf("MODE: %d\n",buff.st_mode);//st_mode: File type and mode

  close(fd);

  return 0;
}
