#include<iostream>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
using namespace std;


int main()
{
  int welcomeSocket,newSocket,nBytes,n;
  struct sockaddr_in serverAddr;
  struct sockaddr_in remaddr;
  char buffer[1024];
  socklen_t addrlen;



  welcomeSocket=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);

  int optval = 1;
  setsockopt(welcomeSocket, SOL_SOCKET, SO_REUSEADDR, 
       (const void *)&optval , sizeof(int));

  int tv = 10000; //Time-out interval: 10000ms
  setsockopt(welcomeSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)(&tv), sizeof(int));

  if(welcomeSocket<0)
  {
    cout<<"Errr"<<endl;
  }

  else
  {
    cout<<"succes"<<endl;
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(8080);
    serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    
    
   //---
        addrlen=sizeof(remaddr);
        while(1)
        {   /* get a message from the user */
    bzero(buffer, 1024);
    printf("Please enter msg: ");
    fgets(buffer, 1024, stdin);
    printf(buffer);

    /* send the message to the server */
    socklen_t serverlen = sizeof(serverAddr);
    n = sendto(welcomeSocket, buffer, strlen(buffer), 0, (struct sockaddr*)&serverAddr, serverlen);
    if (n < 0) 
      printf("ERROR in sendto");
    else
      printf("data sent\n");
            //cout<<"Waiting on port 7891"<<endl;
       int k=     recvfrom(welcomeSocket,buffer,1024,0,(struct sockaddr*)&remaddr,(socklen_t*)&addrlen);
if(k<0) printf("error in receiving");
       printf(buffer);
        }
    
//-------
        close(welcomeSocket);
}
return 0;
}