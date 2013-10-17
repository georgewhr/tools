/*********************************************************************
*
* userIfSend.c
*
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <stddef.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <pthread.h>
#include <asm/ioctls.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <netinet/in.h>
#include "userIfDefs.h"


#define MAXBUFFERSIZE 80
#deine PORT           12468
#define IP_ADDRESS    localhost

int gSeqNum = 0;


/***************************************************************************
*
*
****************************************************************************/
int userMsgSend (unsigned short msg_type,
                     unsigned short mbox,
                     char           *pData,
                     short          size,
                     char           *nodeName)
{
     int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    int n;
    char buffer[256];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);



    if (sockfd < 0)
        error("ERROR opening socket");

    server = gethostbyname(IP_ADDRESS);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;

    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);

    serv_addr.sin_port = htons(PORT);


   int num_bytes;
   int msg_size;
   int rack,shelf,slot;
   unsigned short reg;
   int lcFd;
   int userSocket;
   int rc;
  // struct sockaddr_tipc dest_addr;
   ipc_msg_t *pMsg;
   lcHwAccess_t ioStruct;
   msg_size = size;
   pMsg = (ipc_msg_t *)pData;

   lcFd = open("/dev/lc_common", O_RDWR);
   if (lcFd < 0)
   {
      printf("Can't open /dev/lc_common for hardware access\n");
      return;
   }

   ioStruct.devType = LC_IOCTL_CPLD;
   ioStruct.action = LC_ACTION_READ;
   ioStruct.offset = 0x100;
   ioStruct.width = 2;
   ioStruct.length = 2; /* generic driver needs length in bytes */
   ioStruct.data = (void *)&reg;
   rc = ioctl(lcFd, LC_IOCTL_CPLD,(unsigned)&ioStruct);

   if (rc)
      printf("Error return from ioctl %d\n",rc);

   rack = (reg & 0x1e00) >> 9;
   shelf = (reg & 0xe000) >> 13;
   slot = (reg & 0x1f0) >> 4;

   pMsg->hdr.card_id = ((rack << 16) | (shelf << 8) | slot);
   pMsg->hdr.msg_type = msg_type;
   pMsg->hdr.mbox = mbox;
   pMsg->hdr.seq_num = gSeqNum++;

   pMsg->hdr.size = size;
   pMsg->hdr.version = IPC_MSG_VERSION;
   pMsg->hdr.ccode = 0;

    // cl_socket = socket (AF_TIPC, SOCK_RDM, 0);
   /*dest_addr.family = AF_TIPC;
   dest_addr.scope = TIPC_ZONE_SCOPE;

   dest_addr.addrtype = TIPC_ADDR_NAME;
   dest_addr.addr.name.name.type = IPC_TIPC_TYPE + mbox;
   dest_addr.addr.name.domain = 0;
   dest_addr.addr.name.name.instance = IPC_TIPC_LC_NAME_INST(rack, shelf, slot);

   userSocket = socket(AF_TIPC, SOCK_RDM, 0);
   */

   if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    printf("enter the message: ");
    bzero(buffer,256);

    fgets(buffer,255,stdin);

    n = write(sockfd,buffer,strlen(buffer));

    if (n < 0)
         error("ERROR writing to socket");

     bzero(buffer,256);


     num_bytes = read(sockfd, buffer, strlen(buffer));


   //num_bytes = sendto(userSocket, (char *)pMsg, msg_size , 0,
     //                (struct sockaddr*)&dest_addr, sizeof(dest_addr));

   close (lcFd);
   close(userSocket);

   return num_bytes;
}

/***************************************************************************
*
*
****************************************************************************/
int main(int argc, char* argv[])
{

   int i;
   UserifMsg_t msg;
   int nchars;


   memset(&msg,0,sizeof(msg));

   strcpy(msg.name,argv[1]);
   msg.numParams = argc - 2;

   if (msg.numParams > USERIF_NUM_PARAMS)
   {
      printf("Error: There is a maximum of 5 parameters\n");
      return -1;
   }

   /*for (i = 0; i < msg.numParams; i++)
   {
         if (argv[i+2][0] == '0' && argv[i+2][1] == 'x')
            sscanf(argv[i+2],"%x",&msg.param[i]);
         else
            sscanf(argv[i+2],"%d",&msg.param[i]);
   }*/

/* tell application which file in /dev to set as stdout */


   int return_bytes;

   return_bytes = userMsgSend(IPC_USERIF_RUN_FUNC, TASK_USERIF_MBOX, (char *)&msg,
                         sizeof(msg), NULL);





    close(sockfd);

   return 0;
}


