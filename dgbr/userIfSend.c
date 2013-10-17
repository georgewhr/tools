/**************************************************************************
*   Module:
*   Filename:       userifSend.c
*   Author:
*   Created:
*   Description:    Send user input via socket to the pthread
*
*
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stddef.h>
#include <ctype.h>
#include <time.h>
#include <stddef.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <pthread.h>
#include <asm/ioctls.h>
#include <sys/ioctl.h>
#include <netdb.h>

char buffer[256];
int bb[128];

int main(int argc, char *argv[])
{
    char cbuffer[256];
    if(argc <=1 )
    {
        printf("Please type Arguments.\n");
        return 0;
    }

    int sockfd, n, i, port_number ,length;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
        error("ERROR opening socket");

    server = gethostbyname("localhost");

    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }


    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;

    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);

    serv_addr.sin_port = htons(23232);

    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    bzero(buffer,256);
    bzero(cbuffer,256);

    /*append ';' to the end of each typing string */

    for(i = 1;i<argc;i++)
    {
        length = strlen(argv[i]);
        strcpy(buffer,argv[i]);
        strcat(buffer,";");
        strcat(cbuffer,buffer);
    }

    printf("the buffer here is %s\n",cbuffer);


    n = write(sockfd,cbuffer,strlen(cbuffer));

    printf("send %d bytes\n",n);
    if (n < 0)
         error("ERROR reading from socket");

    read(sockfd,bb,1);

    printf("return value from userIfThread is %d\n",bb[0]);
    close(sockfd);

    return 0;
}


