#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char **argv){

    if(argc != 2){
        perror("Error: Incorrect argument.\n");
        exit(-1);
    }

    //int mkfifo(const char *filename, mode_t mode);
    int fifo = mkfifo(argv[1], 0777);
    int fd = open(argv[1], O_WRONLY);
    char buf[256];
    scanf("%s", buf);
	write(fd, buf, strlen(argv[1]));

	close(fd);



    return 0;
}

