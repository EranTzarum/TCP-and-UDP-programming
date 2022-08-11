
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
  struct addrinfo* res;
  char* hostname;
  char* hostaddr;
  struct sockaddr_in* saddr;
  
  /*Checks if given value in the command-line*/
  if (argc != 2) {
    perror("Usage: hostnamelookup <hostname>\n");
    exit(1);
  }

  /*Takes the hostname from the command-line*/
  hostname = argv[1];
  
  /*Geting the localhost hostname into the addrinfo struct*/
  if (0 != getaddrinfo(hostname, NULL, NULL, &res)) {
    fprintf(stderr, "Error in resolving hostname %s\n", hostname);
    exit(1);
  }

  /*Enters the values of the current host into the sockaddr_in struct and into the hostname*/
  saddr = (struct sockaddr_in*)res->ai_addr;
  hostaddr = inet_ntoa(saddr->sin_addr);

  /*Printing the values that we got from the getaddrinfo() func*/
  printf("Address for %s is %s\n", hostname, hostaddr);
  exit(0);
}
