#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>

#include "Client.h"

int init_client() {
    int status, sockfd;
	struct addrinfo *servinfo;
	struct addrinfo hints = {
		.ai_family = AF_INET,   // use AF_INET and AF_INET6 for iPv4 and iPv6 respectively
		.ai_socktype = SOCK_STREAM, // use TCP type
		.ai_flags = AI_PASSIVE, 
	};

	if ((status = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return status;
	}

	if ((sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol))) {
        perror("socket");
    }

	if (connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) < 0) {
		perror("connect");
	}

	freeaddrinfo(servinfo);

    return sockfd;
}

void send_message(int sockfd, char *message) {
	if (send(sockfd, message, strlen(message), 0) == 0) {
			perror("send");
	} 
}

void *recv_message(void *vargp) {
	ThreadData* tdata = (ThreadData *)vargp;
	while (1) {
		if (recv(tdata->sockfd, tdata->buffer, BUFFER_SIZE, 0) == 0) {
			perror("recv");
			break;
		} else {
			tdata->read = 1;
		}
		sleep(1);
	}
	pthread_exit(NULL);	
}

ThreadData *create_tdata(int sockfd) {
	ThreadData *tdata = malloc(sizeof *tdata);
	tdata->buffer = calloc(BUFFER_SIZE, sizeof(char));
	tdata->sockfd = sockfd;
	tdata->read = 0;
	return tdata;
}