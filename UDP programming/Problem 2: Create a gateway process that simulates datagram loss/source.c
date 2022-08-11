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


int main(int argc, char *argv[]){
    int socket_fd,i=0;
    struct sockaddr_in  dest;
    struct hostent *hostptr;
    struct { char head; size_t body; char tail; } msgbuf;

    /*Creating socket file descriptor*/
    socket_fd = socket (AF_INET, SOCK_DGRAM, 0);

    /*The bzero() function erases the data in the n bytes of the memory
    starting at the location pointed to by *cli_name */
    bzero((char *) &dest, sizeof(dest)); /* They say you must do this */

    /*Assign IP local host(127.0.0.1), PORT*/
    hostptr = gethostbyname("127.0.0.1");
    dest.sin_family = (short)AF_INET;
    
    /*The bcopy() function copies n bytes from src to dest*/
    bcopy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length);

    /*Assign PORT P+1*/
    dest.sin_port = htons(P+1);
    
    while (1)
    {
        msgbuf.head = '<';
        msgbuf.body = i;
        msgbuf.tail = '>'; 

        /*the body contins int and we send all the buff*/
        printf("the num is: %ld\n",msgbuf.body); 

        /*The sendto() function sends data on the socket with descriptor socket*/
        sendto(socket_fd,&msgbuf,sizeof(msgbuf),0,(struct sockaddr *)&dest,
                  sizeof(dest));
        i++;
        sleep(1);
    }
    return 0;
}