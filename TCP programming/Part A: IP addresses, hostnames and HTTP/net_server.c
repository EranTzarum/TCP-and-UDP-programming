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
#define PORT 9999/* We mach the PORT in clint and the server*/

int main(void)
{ 
  int sock; 
  int connect_sock; 
  struct sockaddr_in serv_name; 
  size_t len; 
  int count;

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
  bzero(&serv_name, sizeof(serv_name));

  /*Assign PORT*/ 
  serv_name.sin_family = AF_INET;                                   
  serv_name.sin_port = htons(PORT); 

  /*Binding newly created socket to given IP and verify it*/
  if (bind(sock, (struct sockaddr *)&serv_name, sizeof(serv_name)) !=0 )
  {
    printf("socket bind failed...\n");
        exit(0);
  }

  /*Server is ready to listen (searching for a client) and verify it*/
  if (listen(sock, 1) != 0)
  {
    printf("Listen failed...\n");
        exit(0);
  }
      
  

  len = sizeof(serv_name);

  /*Accept the data packet from client*/
  connect_sock = accept(sock, (struct sockaddr *)&serv_name, &len);
  if (connect_sock < 0) {
        printf("accept failed...\n");
        exit(0);
    }

  for (count = 1; count <= SIM_LENGTH; count++)
    { 
      /*Writeing (INT 4 bytes)int num to socket*/
      write(connect_sock, &count, 4);
      printf("Server has written %d to socket.\n", count);
    }

  /*It is very important to close the socket at the end*/
  close(connect_sock); 
  close(sock);

}
