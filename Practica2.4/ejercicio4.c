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
    if(fifo == -1){
        perror("Error: mkfifo failed.\n");
        exit(-1);
    }
    else printf("mkfifo saccessed\n");
    int fd = open(argv[1], O_WRONLY);
    if(fd == -1){
        perror("Error: open failed.\n");
        exit(-1);
    }
    else printf("Open saccessed\n");
    char buf[3];
    scanf("Write commands here: %s", buf);
	write(fd, buf, 3);
	close(fd);



    return 0;
}
