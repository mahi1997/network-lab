#include  <stdio.h>
#include <bits/stdc++.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

//#include <string.h>

using namespace std;
int main(){
	int wSocket,newSocket;
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
		//newSocket=accept(wSocket,(struct sockaddr*) &serverStorage,&addr_size);


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
		return 0;




}

