#pragma once

#define PORT "8765"
#define BUFFER_SIZE 65536

typedef struct {
    char *buffer;
    int sockfd;
    int read;
} ThreadData;
int init_client();

void send_message(int sockfd, char *message);
void *recv_message(void *vargp);

ThreadData *create_tdata(int sockfd);
