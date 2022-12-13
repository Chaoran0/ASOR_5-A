#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <arpa/inet.h>


int main (int argc, char **argv) {
    struct addrinfo hints;
    if(argc != 4){
        printf("Error: argumento insuficiente\n");
        exit(-1);
    }

    memset(&hints, 0, sizeof(struct addrinfo));

    /*Specifying hints as NULL is equivalent to setting ai_socktype and ai_protocol to 0; ai_family to AF_UNSPEC; and ai_flags to (AI_V4MAPPED | AI_ADDRCONFIG).*/
    hints.ai_flags    = AI_PASSIVE;
    hints.ai_family   = AF_UNSPEC;   // IPv4 o IzPv6
    hints.ai_socktype = SOCK_DGRAM;
    struct addrinfo *result;
	int rc = getaddrinfo(argv[1], argv[2], &hints, &result);
    if(rc != 0){
        printf("[getaddrinfo]: %s\n", gai_strerror(rc));
        exit(-1);
    }
    
    int sd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (sd == -1) {
		perror("Error: socket failed\n");
		exit(-1);
	}

	bind(sd, (struct sockaddr *)result->ai_addr, result->ai_addrlen);
    

    struct sockaddr_storage input_addr;
	socklen_t input_len = sizeof(input_addr);
	//argv[3] == command
    sendto(sd, argv[3], strlen(argv[3]), 0, result->ai_addr, result->ai_addrlen);
    
    
    char buf[257] = "";
	ssize_t readsize = recvfrom(sd, buf, 256, 0, result->ai_addr, &(result->ai_addrlen));
	if (readsize == -1) {
		perror("Error: recevfrom");
		return -1;
	}

	buf[readsize] = '\0';
	printf("%s\n", buf);

	printf("Command %s sent to %s : %s\n", argv[3], argv[1], argv[2]);
	
	freeaddrinfo(result);
	close(sd);


    return 0;
}

/*
usuario_local@portatil:~/Descargas$ ./servidor :: 3000
1 bytes de ip6-localhost:40201
1 bytes de ip6-localhost:52936

usuario_local@portatil:~/Descargas$ ./cliente :: 3000 t
12:37:49 PM
Command t sent to :: : 3000
usuario_local@portatil:~/Descargas$ ./cliente :: 3000 d
2022-12-13
Command d sent to :: : 3000

*/
