//#include  <unp.h>
#include  <stdio.h>
#include <bits/stdc++.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <string.h>
#include <time.h>
#include <unistd.h>


#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h> 
//---------------
#define BUFSIZE 1024

//------------
using namespace std;
int main(){
//-----------------------------------------------------------
int     listenfd, connfd ,n;
    struct sockaddr_in servaddr;
//--
    struct sockaddr_in clientaddr;
     struct hostent *hostp; /* client host info */
    char *hostaddrp; /* dotted decimal host addr string */
     int optval; /* flag value for setsockopt */
    int portno; /* port to listen on */
    time_t ticks;
    //-------
socklen_t addr_size;

struct sockaddr_storage   serverStorage;
      char    buff[1024];
      

    listenfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (listenfd < 0) 
    printf("ERROR opening socket");

optval = 1;
  setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, 
       (const void *)&optval , sizeof(int));

bzero((char *) &servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  //servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_addr.s_addr =inet_addr("127.0.0.1");
  servaddr.sin_port = htons(8080);

   if(bind(listenfd, (struct sockaddr*) &servaddr, sizeof(servaddr))<0)
   	printf("error in binding..");

    //listen(listenfd, 5);
/*if(listen(listenfd, 5)==0)
		cout<<"listening...."<<endl;
	else
		 cout<<"error1"<<endl;
		 */
//------------------------------------------------

		 /* 
   * main loop: wait for a datagram, then echo it
   */
  socklen_t clientlen = sizeof(clientaddr);
  while (1) {

    /*
     * recvfrom: receive a UDP datagram from a client
     */
  	printf("ready to listen\n");
    bzero(buff, BUFSIZE);
    printf("I'm here \n");
    //recvfrom(welcomeSocket,buffer,1024,0,(struct sockaddr*)&remaddr,(socklen_t*)&addrlen);
   n = recvfrom(listenfd, buff, BUFSIZE, 0,
     (struct sockaddr *) &clientaddr, (socklen_t*)&clientlen);
    printf("%d \n" ,n);
    if (n < 0)
      printf("ERROR in recvfrom");
    else
    	//printf(n);
    	printf("%d",n);

    //printf("I'm here");

    /* 
     * gethostbyaddr: determine who sent the datagram
     */
   ticks = time(NULL);
   //buff=ctime(&ticks);
    n = sendto(listenfd,ctime(&ticks), 30, 0, 
         (struct sockaddr *) &clientaddr, clientlen);
    if (n < 0) 
      printf("ERROR in sendto");
  }
  close(listenfd);
		//-------------------------------
/*
    for( ; ; ) {
//----------

//----------

addr_size=sizeof serverStorage;
        connfd = accept(listenfd, (struct sockaddr*) &serverStorage,&addr_size);
        //connfd = accept(listenfd, NULL,NULL);

        time_t ticks= time(NULL);
struct tm *tm=localtime(&ticks);
char s[64];

strftime(s,sizeof(s),"%c",tm);
//cout<<s<<endl;
strcpy(buff,s);

       //snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
       send(connfd, buff, 64+1,0);


       close(connfd);
  }
  */
//----------------------------------------------------------
	/* int wSocket,newSocket;
	char buffer[1024];

	char bufferW[1024]; //to read from client


	struct sockaddr_in  serverAddr;
	struct sockaddr_storage   serverStorage;
	socklen_t addr_size;

	wSocket=socket(PF_INET,SOCK_STREAM,0);

	serverAddr.sin_family= AF_INET;
	serverAddr.sin_port=htons(7891);
	serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");


	memset(serverAddr.sin_zero,'\0',sizeof(serverAddr.sin_zero));
//bind to socket
	bind(wSocket,(struct sockaddr*) &serverAddr,sizeof(serverAddr));

	//listen from socket
	if(listen(wSocket,5)==0)
		cout<<"listening...."<<endl;
	else
		 cout<<"error"<<endl;

		//accept call creates new socket for incoming connection
		addr_size=sizeof serverStorage;
		newSocket=accept(wSocket,(struct sockaddr*) &serverStorage,&addr_size);


        //receive from client
        //recv(wSocket,buffer2,1024,0);
        //string msg=tolower(buffer2);

        //________________

        //read from server
        while(1){
	recv(newSocket,bufferW,1024,0);
    
	//cout<<bufferW<<endl;

	string str=bufferW;
	int n=str.length();
	for(int i=0;i<str.length();i++)
		str[i]=tolower(str[i]);
	cout<<str<<endl;

	char msg[n];
	for(int i=0;i<n;i++)
		msg[i]=str[i];
        //____________________________





		//send msg to client


		//char msg[]="hii how are you";
		strcpy(buffer,msg);
		send(newSocket,buffer,n+1,0);
	}

*/
		return 0;




}

