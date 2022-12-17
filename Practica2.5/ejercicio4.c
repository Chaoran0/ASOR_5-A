#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

int main(int argc, char **argv) {

	if (argc < 3) {
		printf("Use: ./ej1 host port\n");
		return -1;
	}
  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = 0;
	hints.ai_flags = AI_PASSIVE;


	struct addrinfo *result;
	int rc = getaddrinfo(argv[1], argv[2], &hints, &result);

	if (rc != 0) {
		printf("Error while gettinf info: %s\n", gai_strerror(rc));
		return -1;
	}

	int sd = socket(result->ai_family, SOCK_DGRAM, result->ai_protocol);
	if (sd == -1) {
		perror("Unable to open the socket");
		return -1;
	}

	if (bind(sd, result->ai_addr, result->ai_addrlen)) {
		perror("Unable to bind");
		return -1;
	}

	freeaddrinfo(result);

	char buf[2] = "";
	struct sockaddr_storage input_addr;
	socklen_t input_len = sizeof(input_addr);
	fd_set set;
	int readsize;

	while (buf[0] != 'q') {
		FD_ZERO(&set);
		FD_SET(0, &set);
		FD_SET(sd, &set);

		if (-1 == select(sd + 1, &set, NULL, NULL, NULL)) {
			perror("Error while waiting for data");
			return -1;
		}

		if (FD_ISSET(sd, &set))
			readsize = recvfrom(sd, &buf, 2*sizeof(char), 0, (struct sockaddr*) &input_addr, &input_len);
		else if (FD_ISSET(0, &set))
			readsize = read(0, &buf, 2*sizeof(char));
		
		if (readsize == -1) {
			perror("Error ocurred while reciving");
			close(sd);
			return -1;
		}
		else if (readsize == 0) {
			printf("Client has performed a shutdown\n");
			buf[0] = 'q';
		}
		else {
			if (FD_ISSET(sd, &set)) {
				char hostname[NI_MAXHOST] = "";
				char port[NI_MAXSERV] = "";

				if (getnameinfo((struct sockaddr*) &input_addr, input_len, hostname, NI_MAXHOST, port, NI_MAXSERV, 0)) {
					perror("Error getting info from name");
					return -1;
				}

				printf("Recibí %i bytes de %s:%s\n", readsize, hostname, port);
			}

			if (buf[0] == 'd') {
				time_t t;
				struct tm *loctime;
				char buffer[256];
				t =  time(NULL);
				loctime = localtime(&t);
				strftime(buffer,256,"%Y-%m-%d", loctime);

				if (FD_ISSET(0, &set))
					printf("%s\n", buffer);
				else if (FD_ISSET(sd, &set)) {
					int writesize = sendto(sd, buffer, strlen(buffer), 0, (struct sockaddr *)&input_addr, input_len);
					if (writesize == -1) {
						perror("Error while sending back to client");
						return -1;
					}
				}
			} else if (buf[0] == 't') {
				time_t t;
				struct tm *loctime;
				char buffer[256];
				t =  time(NULL);
				loctime = localtime(&t);
				strftime(buffer,256,"%r", loctime);

				if (FD_ISSET(0, &set))
					printf("%s\n", buffer);
				else if (FD_ISSET(sd, &set)) {
					int writesize = sendto(sd, buffer, strlen(buffer), 0, (struct sockaddr *)&input_addr, input_len);
					if (writesize == -1) {
						perror("Error while sending back to client");
						return -1;
					}
				}
			}
			else if (buf[0] == 'q')
				printf("Comando de finalización recibido, saliendo…\n");
			else
				printf("Comando no soportado %s", buf);
		}
	}

	close(sd);
	return 0;
}
