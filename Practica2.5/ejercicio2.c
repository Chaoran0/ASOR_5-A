#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main (int argc, char **argv) {
    struct addrinfo hints;
    if(argc != 3){
        printf("Error: argumento insuficiente\n");
        exit(-1);
    }

    memset(&hints, 0, sizeof(struct addrinfo));

    /*Specifying hints as NULL is equivalent to setting ai_socktype and ai_protocol to 0; ai_family to AF_UNSPEC; and ai_flags to (AI_V4MAPPED | AI_ADDRCONFIG).*/
    hints.ai_flags    = 0;
    hints.ai_family   = AF_UNSPEC;   // IPv4 o IPv6
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

    setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, "1", sizeof(int));
	setsockopt(sd, IPPROTO_IPV6, IPV6_V6ONLY, "0", sizeof(int));

	if (bind(sd, (struct sockaddr *)result->ai_addr, result->ai_addrlen)) {
		perror("Error: bind failed\n");
		exit(-1);
	}
    freeaddrinfo(result);

    char buf[2] = {"", "", ""};//t, d, q
    struct sockaddr_storage input_addr;
	socklen_t input_len = sizeof(input_addr);
    
    while (buf[0] != 'q') {
        int c = recvfrom(sd, &buf, 2*sizeof(char), 0, (struct sockaddr *) &input_addr, &input_len);
        printf("Recibidos %d bytes de %s:%s\n", c, host, serv);
        sendto(sd, buf, c, 0, (struct sockaddr *) &addr, addrlen);
        if (c == -1) {
            perror("Error ocurred while reciving");
            close(sd);
            return -1;
        }
        else if (c == 0) {
            printf("Client has performed a shutdown\n");
            buf[0] = 'q';
        }
        else {
            char hostname[NI_MAXHOST];
            char port[NI_MAXSERV];

            if (getnameinfo((struct sockaddr *)&input_addr, input_len, hostname, NI_MAXHOST, port, NI_MAXSERV, 0)) {
                perror("Error getting info from name");
                return -1;
            }

            printf("Recibí %i bytes de %s:%s\n", c, hostname, port);

            if (buf[0] == 'd') {
                time_t t;
                struct tm *loctime;
                char buffer[256];
                t =  time(NULL);
                loctime = localtime(&t);
                strftime(buffer,256,"%Y-%m-%d", loctime);
    
                int writesize = sendto(sd, buffer, strlen(buffer), 0, (struct sockaddr *)&input_addr, input_len);
                if (writesize == -1) {
                    perror("Error while sending back to client");
                    return -1;
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
                    perror("Error while sending back to client");
                    return -1;
                }
            } else if (buf[0] == 'q')
                printf("Comando de finalización recibido, saliendo…\n");
            else
                printf("Comando no soportado %s", buf);
            
        }
	}

	close(sd);


    return 0;
}

