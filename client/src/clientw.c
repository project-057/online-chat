/*
** client.c -- a stream socket client-write
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "clientw.h"

#define PORT "8765" // the port client will be connecting to 

#define MAXDATASIZE 100 // max number of bytes we can get at once 

// get sockaddr, IPv4 or IPv6:


void* get_in_addr(struct sockaddr* sa)
{
  if (sa->sa_family == AF_INET) {
    return &(((struct sockaddr_in*)sa)->sin_addr);
  }

  return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void)
{
  int sockfd, numbytes;
 
  char msg[MAXDATASIZE];
  struct addrinfo hints, * servinfo, * p;
  int rv;
  char s[INET6_ADDRSTRLEN];

  memset(&msg, 0, sizeof msg);
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    return 1;
  }

  // loop through all the results and connect to the first we can
  for (p = servinfo; p != NULL; p = p->ai_next) {
    if ((sockfd = socket(p->ai_family, p->ai_socktype,
      p->ai_protocol)) == -1) {
      perror("client: socket");
      continue;
    }

    if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
      perror("client: connect");
      close(sockfd);
      continue;
    }

    break;
  }

  if (p == NULL) {
    fprintf(stderr, "client: failed to connect\n");
    return 2;
  }

  inet_ntop(p->ai_family, get_in_addr((struct sockaddr*)p->ai_addr),
    s, sizeof s);
  printf("client: connecting to %s\n", s);

  freeaddrinfo(servinfo); // all done with this structure
  //int numberOfTheRoom()
  //{
    //send the number of the room to the server after recieving the request
    // try to connect to the room
    //if an attempt to connect to the room ends with an error it will mean that the room has not been created yet --> the server needs to create it
    //if the room does not exist client sends the request to the server to create the room, after which the server asks the limit of clients in a room
    //connect to the room
  //}

  while (1)
  {
    printf("Enter your message: ");
    scanf("%s", msg);
    int size = strlen(msg);
    msg[size++] = '\n';
    msg[size++] = '\0';

    if ((numbytes = send(sockfd, msg, MAXDATASIZE - 1, 0)) == -1) {
      perror("send");
      exit(1);
    }

    printf("client: sent '%s'\n", msg);
    memset(&msg, 0, sizeof msg);
  }

  close(sockfd);

  return 0;
}