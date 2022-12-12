#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char **argv) {
	struct addrinfo hints;
	struct addrinfo *res, *tmp;
  
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

	for(tmp = res; tmp != NULL; tmp = tmp->ai_next) {
		char host[NI_MAXHOST];
		getnameinfo(tmp->ai_addr, tmp->ai_addrlen, host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
		printf("Host: %s\nFamily: %d\nSocket: %d\n", host, tmp->ai_family, tmp->ai_socktype);
	}

	freeaddrinfo(res);

	return 0;
}


/*
usuario_local@pto0519:~/Descargas$ ./ejer localhost
Host: 127.0.0.1
Family: 2
Socket: 1
Host: 127.0.0.1
Family: 2
Socket: 2
Host: 127.0.0.1
Family: 2
Socket: 3

usuario_local@pto0519:~/Descargas$ ./ejer ::1
Host: ::1
Family: 10
Socket: 1
Host: ::1
Family: 10
Socket: 2
Host: ::1
Family: 10
Socket: 3
usuario_local@pto0519:~/Descargas$ ./ejer 1::3::4
Error: getaddrinfo failed
usuario_local@pto0519:~/Descargas$ ./ejer www.google.com
Host: 142.250.200.132
Family: 2
Socket: 1
Host: 142.250.200.132
Family: 2
Socket: 2
Host: 142.250.200.132
Family: 2
Socket: 3
Host: 2a00:1450:4003:801::2004
Family: 10
Socket: 1
Host: 2a00:1450:4003:801::2004
Family: 10
Socket: 2
Host: 2a00:1450:4003:801::2004
Family: 10
Socket: 3

*/
