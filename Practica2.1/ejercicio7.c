#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/utsname.h>
#include <stdlib.h>

int main() {
   //long fpathconf(int fd, int name);
   //long pathconf(char *path, int name);
  char *path = "/D";
  printf("The maximum number of links to the file: %ld\n", pathconf(path, _PC_LINK_MAX));
  printf("The maximum length of a relative pathname when path or fd is the current working directory: %ld\n", pathconf(path, _PC_PATH_MAX));
  printf("The maximum length of a filename in the directory path or fd that the process is allowed to create: %ld\n", pathconf(path, _PC_NAME_MAX));
  
  return 0;
}

