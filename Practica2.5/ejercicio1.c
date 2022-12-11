
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char **argv) {
	struct addrinfo hints;
	struct addrinfo *res, *ptr;
  
  if (argc != 2) {
        printf("Error: argumento insuficiente\n");
        exit(-1);
   }
	
	memset(&hints, 0, sizeof(struct addrinfo));
	
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
  hints.ai_socktype = 0;
  hints.ai_flags = AI_PASSIVE; //NI_NUMERICHOST   /* For wildcard IP address */
  hints.ai_protocol = 0;          /* Any protocol */
  hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;

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
