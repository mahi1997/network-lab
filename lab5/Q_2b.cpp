//#include  "unp.h"

#include <iostream>
#include <stdio.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>   //ifreq
#include <unistd.h> 
#include <fstream> 
#include <stdlib.h> 

#include <bits/stdc++.h> 
#include <strings.h>


using namespace std;
int main(int argc, char **argv){
  int sockfd;

   sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  struct hostent *host;
  //------------------------------------
  //string url=argv[1];
  string url="https://www.iitr.ac.in/";
  //string url="https://www.google.co.in/";
  size_t found = url.find_first_of(":");
  string protocol=url.substr(0,found); 

 string url_new=url.substr(found+3); //url_new is the url excluding the http part
 size_t found1 =url_new.find_first_of("/");
 string host1 =url_new.substr(0,found1);

 string path =url_new.substr(found1);
  //-------------------------------------
  host = gethostbyname(host1.c_str());
  sockaddr_in servaddr;
  servaddr.sin_port = htons(80);
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);
  cout << "Connecting...\n";
  if (connect(sockfd, (struct sockaddr*)(&servaddr), sizeof(servaddr)) != 0){
    cout << "Could not connect";
    return 0;
  }
  cout << "Connected.\n";
  //const char* link = host;
   //string httpreq="GET /index.html HTTP/1.0\r\n";
   string httpreq="GET /index.html HTTP/1.0\r\n Host: "+host1+" \r\nConnection: close\r\n\r\n ";

   cout<<"\n\n "<<httpreq<<endl;
   //const char* httpreq =httpre.c_str();

  //send(sockfd, "GET / HTTP/1.1\r\nHost: "+host1+" \r\nConnection: close\r\n\r\n", strlen("GET / HTTP/1.1\r\nHost: www.wikipedia.org \r\nConnection: close\r\n\r\n"), 0);
  
  send(sockfd, httpreq.c_str(), strlen(httpreq.c_str()), 0);

  char buffer[10000];
  int nDataLength;
  FILE *fp;
  fp=fopen("abcd.html","w");
  while ((nDataLength = recv(sockfd, buffer, 10000, 0)) > 0){
    int i = 0;
    while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r') {
      cout << buffer[i];
      fputc(buffer[i],fp);
      i += 1;
    }
  }
  close(sockfd);
  //execv("abcd.html");
  fclose(fp);

  system("xdg-open abcd.html");
  
  return 0 ;




}

