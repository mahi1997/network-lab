#include  <stdio.h>
#include <bits/stdc++.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <string.h>

using namespace std;
int main(){
	int clientSocket,newSocket;
	char buffer[1024];
	char bufferW[1024];
	struct sockaddr_in  serverAddr;
	struct sockaddr_storage   serverStorage;
	socklen_t addr_size;

	clientSocket=socket(AF_INET,SOCK_STREAM,0);

	serverAddr.sin_family= AF_INET;
	serverAddr.sin_port=htons(7891);
	serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");

//bind to socket
	memset(serverAddr.sin_zero,'\0',sizeof(serverAddr.sin_zero));

	addr_size=sizeof serverAddr;
	connect(clientSocket,(struct sockaddr*) &serverAddr,addr_size);
	//__________--____________________________________________________--------------

	//accept call creates new socket for incoming connection
		//addr_size=sizeof serverStorage;
		//newSocket=accept(clientSocket,(struct sockaddr*) &serverStorage,&addr_size);
while(1){
	    string str;
	    cout<<"Enter your string.."<<endl;
	    cin>>str;
        //getline(str);

	    int n=str.length();
	    char msg[n];
	for(int i=0;i<n;i++)
		msg[i]=str[i];

 
		strcpy(bufferW,msg);
		send(clientSocket,bufferW,n+1,0);

		//________________________________________________________________

	//read from server
	recv(clientSocket,buffer,1024,0);

	cout<<buffer<<endl;

	}
		return 0;




}

