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
#include <bits/stdc++.h> 
#include <strings.h>


using namespace std;
int main(int argc, char **argv)
{
	
   string url=argv[1];
  size_t found = url.find_first_of(":");
  string protocol=url.substr(0,found); 

 string url_new=url.substr(found+3); //url_new is the url excluding the http part
 size_t found1 =url_new.find_first_of("/");
 string host =url_new.substr(0,found1);

 string path =url_new.substr(found1);


  cout<<protocol<<endl;
 cout<<host<<endl;
 //cout<<port<<endl;
 cout<<path;
 return 0;
 }