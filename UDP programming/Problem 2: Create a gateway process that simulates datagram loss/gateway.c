#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define P (u_short)0x3313

int main(int argc, char *argv[])
{
    float rando;
    int socket_fd, cc, fsize;
    struct sockaddr_in  s_in, from;
    struct { char head; size_t body; char tail;} msg;
    
    /*Creating socket file descriptor*/
    socket_fd = socket (AF_INET, SOCK_DGRAM, 0);

    /*The bzero() function erases the data in the n bytes of the memory
    starting at the location pointed to by *cli_name */
    bzero((char *) &s_in, sizeof(s_in));  /* They say you must do this    */

    /*Assign IP, PORT*/
    s_in.sin_family = (short)AF_INET;
    s_in.sin_addr.s_addr = htonl(INADDR_ANY);    /* WILDCARD */
    s_in.sin_port = htons(P+1);

    //printsin(&s_in, "RECV_UDP", "Local socket is:"); 
    fflush(stdout);

    /*Binding newly created socket to given IP and verify it*/
    bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in));

    for(;;) {
        fsize = sizeof(from);
        /*The recvfrom() func are used to receive messages from a socket,
         and may be used to receive data on a socket*/
        cc = recvfrom(socket_fd,&msg,sizeof(msg),0,(struct sockaddr *)&from,&fsize);

        /*samples a random number*/
        rando = ((float)random())/((float)RAND_MAX);
        if (rando > 0.5)
        {
            printf("random num is: %f\n",rando);
            printf("sending.. : \n");
            printf("\n");
            /*Assign PORT*/
            s_in.sin_port = htons(P);

            /*The sendto() function sends data on the socket with descriptor socket*/
            sendto(socket_fd,&msg,sizeof(msg),0,(struct sockaddr *)&s_in,
                  sizeof(s_in));
        }
        else
        {
            printf("random num : %f\n",rando);
            printf("Lose packet..\n");
            printf("\n");
        }
        fflush(stdout);
    }
    
    return 0;
}