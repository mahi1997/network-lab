// Server side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h> 
#include <arpa/inet.h>

#include <bits/stdc++.h>


#include <arpa/inet.h>

#include <string.h>
#include <time.h>
#include <unistd.h>

#include <ctime>


#include <netdb.h>
#include <sys/types.h> 
#define PORT 8080
#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
    int server_fd, valread,ret, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";

    char clientAddr[1024];
     pid_t childpid;
    //int new_socket[3];
   
     int clilen;
     //--------------
    
     //-------------
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == 0)
    {printf("socket failed");
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
     
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {   printf("setsockopt");
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr =inet_addr("127.0.0.1");
    address.sin_port = htons( 8080 );
     
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {   printf("bind failed");
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
   
    


for( ; ;) { //infinite loop

  int new_socket = accept(server_fd, (struct sockaddr *)&address, 
                       (socklen_t*)&addrlen);
   if(new_socket>0){
  printf("Connection accepted...\n");

  inet_ntop(AF_INET, &(address.sin_addr), clientAddr, 1024);
 
  if ((childpid = fork()) == 0) { //creating a child process

   close(server_fd); 
//stop listening for new connections by the main process. 
//the child will continue to listen. 
//the main process now handles the connected client.
   int count=0;
    long double started ;
   for (;;) {

    memset(buffer, 0, 1024);
    ret = recvfrom(new_socket, buffer, 1024, 0, (struct sockaddr *) &address, (socklen_t*)&addrlen);
    if(ret < 0) {
     printf("Error receiving data!\n");  
     exit(1);
    }
    if(count==0)
      started = time(0) *1000;

    printf("Received data from %s: %s\n", clientAddr, buffer); 
    count+=ret;
     cout<<"Total pkts :"<<count<<endl;
      long double done = time(0) *1000;

    cout << "Time (miillisec):"<< done-started<<endl;

    



   }

  }
}
  close(new_socket);
 

 }
 close(server_fd);

    return 0;
}

//ret = recvfrom(newsockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &cl_addr, &l