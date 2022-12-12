
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char **argv) {
	struct addrinfo hints:
	struct addrinfo *res, *ptr;
  
  if (argc != 2) {
        printf("Error: argumento insuficiente\n");
        exit(-1);
   }
	
	memset(&hints, 0, sizeof(struct addrinfo));
	/*Specifying hints as NULL is equivalent to setting ai_socktype and ai_protocol to 0; ai_family to AF_UNSPEC; and ai_flags to (AI_V4MAPPED | AI_ADDRCONFIG).*/
    hints.ai_flags = AI_PASSIVE; //NI_NUMERICHOST   /* For wildcard IP address */

	int rc = getaddrinfo(argv[1], NULL, &hints, &res);

	if(rc != 0) {
		printf("Error: getaddrinfo failed\n");
		exit (-1);
	}

	for(ptr = res; ptr != NULL; ptr = ptr->ai_next) {
		char host[NI_MAXHOST];
		getnameinfo(ptr->ai_addr, ptr->ai_addrlen, host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
		printf("Host: %s\nFamily: %d\nSocket: %d\n", host, ptr->ai_family, ptr->ai_socktype);
	}

	freeaddrinfo(res);

	return 0;
}
