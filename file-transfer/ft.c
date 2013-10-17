/********************************************************
//ft version 1.0
//The program can directlly transfer the files from outside
//network to a LAN. The first step is to transfer file from
//outside to an intermediate machines, then transfer again
//to the machine at the LAN.
//
//Compile Syntax: using native GCC linked with ssh library
//gcc -o binary_file source_code -lssh
//Author:George Wang
//georgewhr@gmail.com
/*********************************************************/

#include <libssh/libssh.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libssh/sftp.h>
#include <sys/stat.h>
#include <fcntl.h>

char inBuf[256];    //a global read buffer
int SSHConnect(const char *ipAddr, ssh_session *sess, ssh_channel *chan);
int SSHDisconnect(ssh_session *sess);
int OpenChannel(ssh_session *sess, ssh_channel *chan);
int OpenRemoteShell(ssh_channel *chan);
int CaptureData(ssh_channel *chan, char *buf, int nBytes);
int SendData(ssh_channel *chan, char *buf, int nbytes);
int WaitForString(ssh_channel *chan, char *buf, int maxBytes, const char *str);
int WaitForPrompt(ssh_channel *chan, char *buf, int maxBytes);
void HandleErrorAndExit(ssh_session *sess);
void PrintData(char *buf, int numBytes);

int main(int argc, char *argv[])    //first argument is the input file path, second argument is the IP address of the intermediate machine
{
  ssh_session session;
  ssh_channel chan;
  int numBytes;


  if(strncmp(argv[1],"--help",6) == 0)
  {
      printf("\nft Version 1.0\n"
             "Usage: ft [Input File Path on local machine]... [Host Machine IP Address]...\n"
             "When the second prompt, type in the destination file path on DRU.\n"
             "For example:root@169.254.176.101:/root\n"
             "Transfer input files directly to DRU\n\n"

             "Report ft bugs to ERIC.CINA@te.com, george_wang@te.com\n"
            );

      return 0;
  }

  //two strings would be appended
  char *new_str;
  char *new_str2;
  char *new_str3;
  char inputFile[256];
  char dst_on_remote[256];
  char *s;
  char *a;

  new_str = malloc(strlen(argv[1]) + strlen(argv[2]) + 16);
  strcat(new_str,"scp ");
  strcat(new_str,argv[1]);
  strcat(new_str," ");
  strcat(new_str,"root@");
  strcat(new_str, argv[2]);
  strcat(new_str,":/root");

  system(new_str);      //execute the command at the local machine

  if (SSHConnect(argv[2], &session, &chan) < 0)
  {
    HandleErrorAndExit(&session);
  }

  printf("Connected to %s\n", argv[2]);

  if (OpenChannel(&session, &chan) < 0)
  {
    HandleErrorAndExit(&session);
  }

  if (OpenRemoteShell(&chan) < 0)
  {
    HandleErrorAndExit(&session);
  }

  inBuf[0] = 0;

  numBytes = WaitForPrompt(&chan, inBuf, 255);
  if (numBytes < 0)
  {
    HandleErrorAndExit(&session);
  }

  //PrintData(inBuf, numBytes);

  if (SendData(&chan, "scpremote ls\n",14 ) < 0)    //check how many remotes are out there connected to the host
  {
    HandleErrorAndExit(&session);
  }

  // *NOTE*: ** This sleep is needed to make it work for some reason!!!!!!!!!!!!!
  //usleep(50000L); // 0.05 second

  // Capture all data until the prompt

  memset(inBuf,0,256);      //initiliaze the input buffer

  numBytes = WaitForPrompt(&chan, inBuf, 255);

  PrintData(inBuf, numBytes);

  //usleep(50000L); // 0.05 second

  //printf("\nPlease type the destination of the file.(example:root@remote_ip_addr:/root)\n");
  //fgets(dst_on_remote,256,stdin);


  s = strrchr(argv[1],'/');
 /* a = s + 1;

  new_str2 = malloc(strlen(a) + strlen(dst_on_remote)+5);
  new_str2[0] = 0;

  strcat(new_str2,"scp ");

  strcat(new_str2,a);
  strcat(new_str2," ");
  strcat(new_str2,dst_on_remote);*/

  printf("Processing ......\n");

  //SendData(&chan, "root@169.254.13.120:/root\n", (strlen(new_str2)+1));
  SendData(&chan, "scp file root@169.254.13.120:/root\n",37);
  // Capture all data until the prompt
  numBytes = WaitForString(&chan, inBuf, 255, "password:");

  if (SendData(&chan, "ADCfwu\n", 7) < 0)
  {
    HandleErrorAndExit(&session);
  }
  // *NOTE*: ** This sleep is needed to make it work for some reason!!!!!!!!!!!!!
  //usleep(50000L); // 0.05 second

  // Capture all data until the prompt
  numBytes = WaitForPrompt(&chan, inBuf, 255);

  if (numBytes < 0)
  {
    HandleErrorAndExit(&session);
  }

  PrintData(inBuf, numBytes);



  strcat(new_str3,"rm ");
  strcat(new_str3,a);


  if (SendData(&chan, new_str3, strlen(new_str3)+1) < 0)  //this step removes the file in the intermediate machine
  {
    HandleErrorAndExit(&session);
  }

  // *NOTE*: ** This sleep is needed to make it work for some reason!!!!!!!!!!!!!
  //usleep(90000L); // 0.05 second

  // Capture all data until the prompt
  numBytes = WaitForPrompt(&chan, inBuf, 255);

  if (numBytes < 0)
  {
    HandleErrorAndExit(&session);
  }

  //usleep(50000L); // 0.05 second
  return 0;

}

int SSHConnect(const char *ipAddr, ssh_session *sess, ssh_channel *chan)
{
  int status;
  *sess = ssh_new();
  int port = 22;

  if (*sess == NULL) return -1;

  ssh_options_set(*sess, SSH_OPTIONS_HOST, ipAddr);
  //ssh_options_set(sess, SSH_OPTIONS_LOG_VERBOSITY, &verbosity);
  ssh_options_set(*sess, SSH_OPTIONS_PORT, &port);
  ssh_options_set(*sess, SSH_OPTIONS_USER, "root");

  status = ssh_connect(*sess);
  if (status != SSH_OK)
  {
    fprintf(stderr, "Error connecting to localhost: %s\n",
    ssh_get_error(*sess));
    return status;
  }

  status = ssh_userauth_password(*sess, NULL, "ADCfwu");
  if (status != SSH_AUTH_SUCCESS)
  {
    fprintf(stderr, "Error authenticating with password: %s\n",
    ssh_get_error(*sess));
    return -2;
  }
  return 0;
}

int SSHDisconnect(ssh_session *sess)
{
  ssh_disconnect(*sess);
  ssh_free(*sess);
}

int OpenChannel(ssh_session *sess, ssh_channel *chan)
{
  int status;

  *chan = ssh_channel_new(*sess);
  if (*chan == NULL)
    return -1;
  status = ssh_channel_open_session(*chan);
  if (status != SSH_OK)
  {
    ssh_channel_free(*chan);
    return status;
  }
}

int OpenRemoteShell(ssh_channel *chan)
{
  int status;

  status = ssh_channel_request_pty(*chan);
  if (status != SSH_OK) return status;
  status = ssh_channel_change_pty_size(*chan, 80, 24);
  if (status != SSH_OK) return status;

  status = ssh_channel_request_shell(*chan);
  if (status != SSH_OK) return status;
}

int kbhit()
{
struct timeval tv = { 0L, 0L };
fd_set fds;
FD_ZERO(&fds);
FD_SET(0, &fds);
return select(1, &fds, NULL, NULL, &tv);
}

int CaptureData(ssh_channel *chan, char *buf, int maxBytes)
{
  int nBytes;

 // while (ssh_channel_is_open(*chan) && !ssh_channel_is_eof(*chan))
 // {
   nBytes = ssh_channel_read(*chan, buf, maxBytes, 0);
   if (nBytes < 0)
     return -1;


  return nBytes;
}

int SendData(ssh_channel *chan, char *buf, int nbytes)
{
  int nWrite;

  nWrite = ssh_channel_write(*chan, buf, nbytes);
  return nWrite;
}

// Capture all data up until and including str
int WaitForString(ssh_channel *chan, char *buf, int maxBytes, const char *str)
{
  int nBytes=1, total=0;

  while (nBytes > 0)
  {
    nBytes = CaptureData(chan, &buf[total], maxBytes);
    if (nBytes < 0) break;
    total += nBytes;
    if (strstr(buf, str) > 0) return total;
  }
  return -1;
}

// Capture all data up until and including the prompt
int WaitForPrompt(ssh_channel *chan, char *buf, int maxBytes)
{
  return WaitForString(chan, buf, maxBytes, "root>");

}

void PrintData(char *buf, int numBytes)
{
  buf[numBytes] = 0;  // place null at end of string
  printf("%s", buf);
}

void HandleErrorAndExit(ssh_session *sess)
{
  printf("Error!!!\n");
  SSHDisconnect(sess);
  exit(-1);
}

