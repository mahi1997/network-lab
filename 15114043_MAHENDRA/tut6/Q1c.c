#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netdb.h>
#include<sys/un.h>
#define SOCK_PATH "echo_socket"
int main()
{
  int sockfd,n,addrlen;
  struct sockaddr_un servaddr;
  char recvline[100];
  char sendline[100];
  
  bzero(&servaddr,sizeof(servaddr));
  
  sockfd=socket(AF_UNIX,SOCK_STREAM,0);
  printf("Trying to connect...\n");
  servaddr.sun_family=AF_UNIX;
  strcpy(servaddr.sun_path,SOCK_PATH);
  //unlink(servaddr.sun_path);
  addrlen=sizeof(servaddr.sun_family)+sizeof(servaddr.sun_path);
  bind(sockfd,(struct sockaddr*)& servaddr,addrlen);
  connect(sockfd,(struct sockaddr*)&servaddr,addrlen);
  
  printf("Connected.\n");
  
  struct sockaddr_un myaddr;
  int len=sizeof(myaddr);
  getsockname(sockfd,(struct sockaddr*)&myaddr,&len);
  printf("bound name = %s, returned len = %d\n", myaddr.sun_path, len);
  while(1)
  {
    bzero(sendline,100);
    bzero(recvline,100);
    fgets(sendline,100,stdin);
    write(sockfd,sendline,strlen(sendline)+1);
    n=read(sockfd,recvline,100);
    printf("%s\n",recvline);
  }

  close(sockfd);
  return 0;
}
