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
    if(argc != 3){
        printf("Error: argumento insuficiente\n");
        exit(-1);
    }

    memset(&hints, 0, sizeof(struct addrinfo));

    /*Specifying hints as NULL is equivalent to setting ai_socktype and ai_protocol to 0; ai_family to AF_UNSPEC; and ai_flags to (AI_V4MAPPED | AI_ADDRCONFIG).*/
    hints.ai_flags    = 0;
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
    freeaddrinfo(result);

    char buf[2] = "";//t, d, q
    struct sockaddr_storage input_addr;
	socklen_t input_len = sizeof(input_addr);
    
    while (buf[0] != 'q') {
        int c = recvfrom(sd, &buf, 2*sizeof(char), 0, (struct sockaddr *) &input_addr, &input_len);
        if (c == -1) {
            perror("Error: recvfrom\n");
            close(sd);
            exit(-1);
        }
        else if (c == 0) {
            printf("Termina el proceso servidor\n");
            buf[0] = 'q';
        }
        else {
            char host[NI_MAXHOST];
            char serv[NI_MAXSERV];
		
            if (getnameinfo((struct sockaddr *)&input_addr, input_len, host, NI_MAXHOST, serv, NI_MAXSERV, 0)) {
                perror("Error: getnameinfo failed\n");
                exit(-1);
            }

            printf("%i bytes de %s:%s\n", c, host, serv);

            if (buf[0] == 'd') {
                time_t t;
                struct tm *loctime;
                char buffer[256];
                t =  time(NULL);
                loctime = localtime(&t);
                strftime(buffer,256,"%Y-%m-%d", loctime);
    
                int writesize = sendto(sd, buffer, strlen(buffer), 0, (struct sockaddr *)&input_addr, input_len);
                if (writesize == -1) {
                    perror("Error: sendto failed\n");
                    exit(-1);
                }
            } else if(buf[0] == 't') {
                time_t t;
                struct tm *loctime;
                char buffer[256];
                t =  time(NULL);
                loctime = localtime(&t);
                strftime(buffer,256,"%r", loctime);
    
                int writesize = sendto(sd, buffer, strlen(buffer), 0, (struct sockaddr *)&input_addr, input_len);
                if (writesize == -1) {
                    perror("Error: sendto failed\n");
                    exit(-1);
                }
            } else if (buf[0] == 'q')
                printf("Saliendo...\n");
            else
                printf("Command not exist: %s\n", buf);
            
        }
	}

	close(sd);


    return 0;
}
