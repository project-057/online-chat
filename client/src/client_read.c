#include "header.h"
void client_read(const char* node, const char* service) {
    int status, sockfd;
    struct addrinfo hints = {
		.ai_family = AF_INET,   // use AF_INET and AF_INET6 for iPv4 and iPv6 respectively
		.ai_socktype = SOCK_STREAM, // use TCP type
		.ai_flags = AI_PASSIVE, 
	};
    struct addrinfo *servinfo;
    time_t rawtime = time(NULL);
    struct tm * timeinfo;
    memset(&hints, 0, sizeof(hints)); // очистка структуры
    //лутаем инфу о нашем айпишнике
    if ((status = getaddrinfo(node, service, &hints, &servinfo)) != 0) { 
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(-1);
    }
    // лутаем дескриптор файла
    sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
	// выгружает сокет из ядра(если порт юзаный)
    int yes = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        perror("setsockopt\n");
        exit(-1);
    }
    // коннектимся?
    if ((status = connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) < 0)) {
		fprintf(stderr, "connect: error\n");
        exit(-1);
	}
    freeaddrinfo(servinfo);

    char buffer[BUFFER_SIZE] = {'\0'};
    char username[20] = {'\0'};
    while (1) {
        if (read(sockfd, buffer, BUFFER_SIZE) == -1) {
            perror("null");
        } else if(strcmp("Enter room number: ", buffer) == 0) {
            puts(buffer);
            bzero(buffer, sizeof buffer);
            scanf("%s", username);
            send(sockfd, username, BUFFER_SIZE, 0);
            bzero(username, sizeof username);
        } else if (strcmp("Enter your username: ", buffer) == 0) {
            puts(buffer);
            bzero(buffer, sizeof buffer);
            scanf("%s", username);
            printf("haha\n");
            send(sockfd, username, BUFFER_SIZE, 0);
        } else if (strcmp("/exit", buffer) == 0) {
            printf("Connection closed, your interlocutor left.");
            break;
        } else {
            timeinfo = localtime(&rawtime);
            printf("|%d:%d| ", timeinfo->tm_hour, timeinfo->tm_min);
            puts(buffer);
            bzero(buffer, sizeof buffer);
        }
    }
    close(sockfd);
	
}
