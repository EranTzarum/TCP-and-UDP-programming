#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
# include <stdio.h>
#include <netinet/in.h>
#include <netinet/tcp.h>  
#define P (u_short)0x3313


int main(int argc, char *argv[])
{
  int socket_fd;
  struct sockaddr_in  dest;
  struct hostent *hostptr;
  struct { char head; u_long body; char tail; } msgbuf;

  /*Creating socket file descriptor*/
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);
  

  /*The bzero() function erases the data in the n bytes of the memory
    starting at the location pointed to by *cli_name */
  bzero((char *) &dest, sizeof(dest)); /* They say you must do this */

  /*Assign IP from command-line*/
  hostptr = gethostbyname(argv[1]);
  dest.sin_family = (short)AF_INET;
  bcopy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length);

  /*Assign PORT P*/
  dest.sin_port = htons(P);

  msgbuf.head = '<';

  /*The htonl() function translates a long integer from host byte order to network byte order*/
  msgbuf.body = htonl(getpid()); /* IMPORTANT! */
  msgbuf.tail = '>';

  /*The sendto() function sends data on the socket with descriptor socket*/
  sendto(socket_fd,&msgbuf,sizeof(msgbuf),0,(struct sockaddr *)&dest,
                  sizeof(dest));
  return 0;
}
