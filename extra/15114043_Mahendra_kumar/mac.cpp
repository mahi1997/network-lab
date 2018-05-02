//********************************************************************//
//                 USE of code                                       //
// run by  compiledcodename  internetface  
// eg -    ./mac eno1 
//internet face can be found from ifconfig command on top           //


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
   		int fd;
    struct ifreq ifr;
    //char *iface = "eno1";
    char *iface = argv[1];
    unsigned char *mac;
     
    fd = socket(AF_INET, SOCK_STREAM, 0);
 
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name , iface , IFNAMSIZ-1);
 
    ioctl(fd, SIOCGIFHWADDR, &ifr);
 
    close(fd);
     
    mac = (unsigned char *)ifr.ifr_hwaddr.sa_data;

    // cout<<mac[0]<<mac[1]<<mac[2]<<mac[3]<<mac[4]<<mac[5]<<endl;
    //display mac address
   printf("Mac : %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n" , mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

   	

	//



  return 0;
}
// 