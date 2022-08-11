#include <sys/types.h>
#include <unistd.h>          
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>    
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#define SIM_LENGTH 10 /*Fixd length*/
#define IP_ADDRESS "127.0.0.1" /*Define localhost name*/
#define PORT 9999 /*We mach the PORT in clint and the server*/

int main(void)
{ 
  int sock; 
  struct sockaddr_in cli_name; 
  int count;
  int value; 

  printf("Client is alive and establishing socket connection.\n");

  /*Create the socket and verify it*/
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
    { 
      perror ("Error opening channel");
      close(sock);
      exit(1);
    }
      
  /*The bzero() function erases the data in the n bytes of the memory
    starting at the location pointed to by *cli_name */
  bzero(&cli_name, sizeof(cli_name)); 

  /*Assign IP, PORT*/
  cli_name.sin_family = AF_INET; 
  cli_name.sin_addr.s_addr = inet_addr(IP_ADDRESS); 
  cli_name.sin_port = htons(PORT);
  
  
  
  /*Connect the client socket to server socket*/
  if (connect(sock, (struct sockaddr *)&cli_name, sizeof(cli_name)) != 0)
    { perror ("Error establishing communications");
      close(sock);
      exit(1);
    }
    /*If we run client whan server is not runing,
     The client will try to connect with the func connect() above but will not succeed
     becouse the server accept socket is not open and no server is listening to accept a client from this port.
     So we will get a Error establishing communications: Connection refused. */


  for (count = 1; count <= SIM_LENGTH; count++)
    { 
      /*Reading (INT 4 bytes)int num from connection socket*/
      read(sock, &value, 4);
      printf("Client has received %d from socket.\n", value);
    }

  printf("Exiting now.\n");

  /*It is very important to close the socket at the end*/
  close(sock); 
  exit(0); 

} 

