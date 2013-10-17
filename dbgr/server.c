
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>



int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;

     char buffer[256];

     struct sockaddr_in serv_addr, cli_addr;
     int n = 0;



     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
        error("ERROR opening socket");

     bzero((char *) &serv_addr, sizeof(serv_addr));

     //portno = atoi(argv[1]);

     serv_addr.sin_family = AF_INET;

     serv_addr.sin_addr.s_addr = INADDR_ANY;

     serv_addr.sin_port = htons(22221);

     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
              error("ERROR on binding");

     listen(sockfd,5);

     clilen = sizeof(cli_addr);
     int i;
    // char *ptr;
   int j = 0;
  char *ptr[6];
//  ptr = (malloc(3));
  char *loc;
     while (1)
     {

        newsockfd = accept(sockfd,
                    (struct sockaddr *) &cli_addr,
                    &clilen);

        if (newsockfd < 0)
             error("ERROR on accept");

        bzero(buffer,256);


          j = 0;


          n = read(newsockfd,buffer,255);

         loc = buffer;

        for(i = 0;i<n;i++)
        {

             if(buffer[i] == ';')
             {


                   buffer[i] = '\0';


                   ptr[j] = loc;
                   loc = loc + strlen(loc) + 1;
                   j++;

             }


         }



          //  ptr = buffer + 7;
            printf("I received %d bytes\n", n);
            printf("I received %d parameters\n", j);


            for(i = 0;i<j;i++)
              printf("Here is the message %s\n",ptr[i]);




        if (n < 0) error("ERROR reading from socket");



        n = write(newsockfd,"I got your message",18);

        if (n < 0) error("ERROR writing to socket");


        close(newsockfd);
     }

     close(sockfd);

     return 0;
}
