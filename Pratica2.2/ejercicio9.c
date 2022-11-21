#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sysmacros.h>
#include <time.h>
#include <stdlib.h>

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
  printf("MAJOR: %d\n", major(buffer.st_dev));//st_dev: ID of device containing file 
  printf("MINOR: %d\n", minor(buffer.st_dev));

  printf("I-Node: %ld\n",buffer.st_ino); //st_ino: Inode number 
	
  printf("MODE: %d\n",buffer.st_mode);//st_mode: File type and mode

  //S_ISLNK(m): Comprueba si es un enlace simbólico
  if(S_ISLNK(buffer.st_mode))
	  printf("%s es un enlace simbólico.\n", argv[1]);
  else if(S_ISREG(buffer.st_mode))//S_ISREG(m): Comprueba si es un fichero normal
	  printf("%s es un un fichero normal.\n", argv[1]);
  else if(S_ISDIR(buffer.st_mode))//S_ISDIR(m): Comprueba si es un directorio
	  printf("%s es un un directorio.\n", argv[1]);
  
  //time_t st_atime: Último acceso 
  //time_t st_mtime: time of last modification
  //time_t st_ctime: time of last status change

  time_t t = buffer.st_atime;
  struct tm *t1 = localtime(&t);
  /*int tm_sec;        
    int tm_min;       
    int tm_hour;    
    int tm_mday;        
    int tm_mon;         
    int tm_year;        
    int tm_wday;        
    int tm_yday;   
    
    IMPORTANTE!!!!!!!!!!!!!!!!!!
    tm_mon
    The number of months since January, in the range 0 to 11.

    tm_year
    The number of years since 1900.
    */
  printf("Último acceso: %d/%d/%d   %d:%d:%d\n",t1->tm_year+1900, t1->tm_mon+1, t1->tm_mday,t1->tm_hour, t1->tm_min, t1->tm_sec);


  close(fd);

  return 0;
}
