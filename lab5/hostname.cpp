// THIS IS A DEPRECATED METHOD OF GETTING HOST NAMES
// use getaddrinfo() instead!
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

int main(int argc, char *argv[])
{
   	

   	struct hostent *he;
	struct in_addr ipv4addr;
	struct in6_addr ipv6addr;

    if (argc != 2) {
        fprintf(stderr,"usage: IP\n");
        return 1;
    }



	inet_pton(AF_INET, argv[1], &ipv4addr);
	he = gethostbyaddr(&ipv4addr, sizeof ipv4addr, AF_INET);
	printf("Host name: %s\n", he->h_name);

	//



  return 0;
}
// 