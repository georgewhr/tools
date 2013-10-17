/**************************************************************************
*   Module:
*   Filename:       userifThread.c
*   Author:
*   Created:
*   Description:    To allow users to run a function or set a variable in the running application
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

#include "userIfDefs.h"

int numFuncs = 0;
int numVars = 0;
int userIfDbg = 0;
char *ptr[6];
int passVar[5];
int sockfd, newsockfd;
UserifMsg_t user;

void *userInterfaceThread(void *arg);

func_t userFuncTable[MAXNUM_USER_FUNC] =
{
    { {0}, NULL },
};

var_t userVarTable[MAXNUM_USER_VAR] =
{
    { {0}, NULL },
};

pthread_mutex_t userifMutex;

void main()
{
    pthread_t tid;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_create(&tid, &attr,&userInterfaceThread, NULL );

    while(1){}
    pthread_join(tid, NULL);
}

/*void userifRegInit()
{
   userIfRegisterFunc and userIfRegisterVar can also be directly called from user code
    userifRegisterFunc("almShow",       &lcFmShowAlarm,     "Display current alarm state, usage: almShow");
    userifRegisterFunc("brdShow",       &brdShowBoard,      "Display board data, usage: brdShow");

    userifRegisterVar("ipcDebug",       &gIpcDebug,         "IPC debug flag");
    userifRegisterVar("cfgDebug",       &lcCfgDebug,        "CFG debug flag");
}*/

/*******************************************************************
*  Function: userifRegisterFunc
*  Description: Register the user input Function and save the
*               registered function in function table:
*               userFuncTable[]
*
*  Inputs: user_input function name, function pointer points to
*          the address of the function
*
*  Returns:If function is ALREADY registered, outputs 1
*******************************************************************/

int userifRegisterFunc(char *name, int (*pFunc)(), char *help)
{
    if ( strlen(name) > USERIF_NAME_SIZE ) return 1;
    if ( numFuncs >=  MAXNUM_USER_FUNC ) return 1;
    int i;

    /*Check if function is registered
      or not
    */
    for(i = 0;i < numFuncs; i++)
    {
        if(strcmp(userFuncTable[i].name,name) == 0)
        {
            return 1;   //return 1 if function is already registered
        }
    }

    pthread_mutex_lock(&userifMutex);

    strcpy( userFuncTable[numFuncs].name, name);

    userFuncTable[numFuncs].pFunc = pFunc;

    numFuncs++;

    pthread_mutex_unlock(&userifMutex);

    return 0;
}

/*******************************************************************
*  Function: userifRegisterVar
*  Description: Store the user input variables in each associated
*               function tables.
*
*  Inputs: user_input function name, a pointer points to
*          the passed variables
*
*  Outputs: Return 0 if stored successfully
*******************************************************************/

int userifRegisterVar(char *name, int *pVar, char *help)
{
    if ( strlen(name) > USERIF_NAME_SIZE ) return 1;
    if ( numFuncs >=  MAXNUM_USER_FUNC ) return 1;

    pthread_mutex_lock(&userifMutex);
    strcpy( userVarTable[numVars].name, name);
   // strcpy( userVarTable[numVars].help, help);
    userVarTable[numVars].pVar = pVar;
    numVars++;
    pthread_mutex_unlock(&userifMutex);
    return 0;
}

int userifHelp()
{
    int i;

    printf("Registered functions (%d):\n", numFuncs);
    for(i = 0; i < numFuncs; i++)
    {
        printf("    %-30s  %s\n", userFuncTable[i].name, userFuncTable[i].help);
    }

    printf("\nRegistered variables (%d):\n", numVars);
    for(i = 0; i < numVars; i++)
    {
        printf("    %-30s  %s\n", userVarTable[i].name, userVarTable[i].help);
    }
    return 0;
}

/*******************************************************************
*  Function: userifRunFunc
*  Description: Function to call the local stacks and get the
*               Output of each stacks
*
*  Inputs: User input variables type of UserifMsg_t
*
*  Outputs: Return 0 if function is located
*           Return 1 if no such function in function table
*******************************************************************/

int userifRunFunc(UserifMsg_t *user_input)
{
    int i;
    int rc;
    func_t *pFuncTable = userFuncTable;
    var_t *pVarTable = userVarTable;

    printf("\nnumber of function is %d\n",numFuncs);

    for(i = 0; i < numFuncs; i++)
    {
        if ( strcmp(user_input->name, pFuncTable->name) == 0 )
        {
            /* call the function */
            rc =  (pFuncTable->pFunc)(user_input->param[0],
                                      user_input->param[1],
                                      user_input->param[2],
                                      user_input->param[3],
                                      user_input->param[4]);

            printf("%s():  ret code = %d \n\n\n",user_input->name, rc);
            write(newsockfd,&rc,1);
            return 0;
        }
        pFuncTable++;
    }

    for(i = 0; i < numVars; i++)
    {
        if ( strcmp(user_input->name, pVarTable->name) == 0 )
        {
            if ( user_input->numParams > 0 ) *(pVarTable->pVar) = user_input->param[0];
            printf("%s = %d\n", user_input->name, *(pVarTable->pVar));
            return 0;
        }
        pVarTable++;
    }

    printf("Error command not found\n");
    return 1;
}

/**************
testing function
***************/

int myFunction(int a, int b, int c)
{
    printf("Hello George, here is the print out in the dummy function, the number is %d\n",a+b+c);
    return (a + b + c );
}

/*int lcUserifMsgHandler(void *pRxBuf, void *pTxBuf, int *pTxSize)
{
    ipc_msg_t *pMsg = (ipc_msg_t *)pRxBuf;

    UserifMsg_t *pUserifMsg = (UserifMsg_t *)(pRxBuf);

    freopen(pUserifMsg->stdoutDev,"w",stdout);

    *pTxSize = 0;

    if ( userIfDbg )
    {
        printf("%s (%d): msg_type: 0x%x\n", __FUNCTION__, __LINE__, pMsg->hdr.msg_type);
    }

    switch(pMsg->hdr.msg_type)
    {
    case IPC_USERIF_RUN_FUNC:
    case IPC_USERIF_SET_VAR:    return userifRunFunc(pRxBuf);

    default:
        printf("%s:  Unsupported msg_type(%d)\n", __FUNCTION__, pMsg->hdr.msg_type);
        return 1;
   }

   return 0;
}*/

/*******************************************************************
*  Function:    userInterfaceThread
*  Description: The user thread stack will keep listening via the
*               socked and process each incomed parameters.
*******************************************************************/

void *userInterfaceThread(void *arg)
{
     char *loc;     //loc is a pointer points to each string after '0\'
     int n, i, m, rc, j;
     char buffer[256];
     j = 0;
     //UserifMsg_t user;
     socklen_t clilen;
     struct sockaddr_in serv_addr, cli_addr;

     if ( pthread_mutex_init(&userifMutex, 0) != 0 )
     {
         printf("ERROR: failed to create userif mutex\n");
     }

     /*mem zero out of all buffer*/
     memset(ptr,0,6);
     memset(passVar,0,5);
     memset(buffer,0,256);

     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
        error("ERROR opening socket");

     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;

     serv_addr.sin_addr.s_addr = INADDR_ANY;

     serv_addr.sin_port = htons(23232);

     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
              error("ERROR on binding");

     listen(sockfd,5);

     clilen = sizeof(cli_addr);

     while (1)
     {
         newsockfd = accept(sockfd,
                    (struct sockaddr *) &cli_addr,
                    &clilen);

         if (newsockfd < 0)
              error("ERROR on accept");

         bzero(buffer,256);
         m = j = 0;

         n = read(newsockfd,buffer,255);
         printf("I received %d bytes\n", n);
         loc = buffer;  //store the base address in loc

         /*Parse the passed buffer to
           different strings. Count numbers of
           flag sign ';', which means number of
           how many passed parameter
         */
         for(i = 0;i < n;i++)
         {
              if(buffer[i] == ';')
              {
                    buffer[i] = '\0';
                    ptr[j] = loc;
                    loc = loc + strlen(loc) + 1;
                    j++;
              }
         }

         user.name = ptr[0];

         /*store each varibales in each function*/

         for(i = 1;i < j;i++)
         {
              *(passVar+m) = atoi(ptr[i]);
              user.param[m] = *(passVar+m);
              userifRegisterVar(ptr[0], passVar + m, NULL);
              //printf("number is %d\n",*(passVar+m));
              m++;
         }

         if(userifRegisterFunc(ptr[0],&myFunction,NULL) == 1)
              printf("Function is already registed\n");

         userifRunFunc(&user);

         if (n < 0) error("ERROR writing to socket");

         close(newsockfd);
     }
}
