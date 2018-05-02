#include <iostream>
#include  <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <fstream>
#include <sys/socket.h>
#include <string.h>
using namespace std;


int main(int argc ,char **argv)
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
    socklen_t serverlen = sizeof(serverAddr);
    //connect is called in case of connect UDP sockets
    connect(welcomeSocket,(struct sockaddr*)&serverAddr, serverlen);
    /* send the message to the server */
    

    fstream file;
    file.open(argv[1]);
    string str="";
    while(!file.eof()){
      getline(file,str);
      int k=str.length();
      char bug[k];
      for(int i=0;i<k;i++)
        bug[i]=str[i];
      cout<<str<<endl;
      // n = sendto(welcomeSocket, bug, strlen(bug), 0, (struct sockaddr*)&serverAddr, serverlen);
      n=write(welcomeSocket, bug, strlen(bug));
    if (n < 0) 
      printf("ERROR in sendto");
    else
      printf("data sent");

    }
/*
    n = sendto(welcomeSocket, buffer, strlen(buffer), 0, (struct sockaddr*)&serverAddr, serverlen);
    if (n < 0) 
      printf("ERROR in sendto");
    else
      printf("data sent");
            //cout<<"Waiting on port 7891"<<endl;
       int k=     recvfrom(welcomeSocket,buffer,1024,0,(struct sockaddr*)&remaddr,(socklen_t*)&addrlen);
if(k<0) printf("error in receiving");
*/
        }
    
//-------
        close(welcomeSocket);
}
return 0;
}