//********************************************************************//
//                 USE of code                                       //
// run by  sudo ./compiledcodename  destinationIP   
//here     sudo ./helloping 8.8.8.8      for google
//sudo is compulsory elese you will get error sudo will give permissions to ping

// include icmph.h   here i.e. structure for our header


//*************************************************************



#define _BSD_SOURCE
#include <sys/time.h>

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

#include <linux/ip.h>
//#include <linux/icmp.h>
#include "icmph.h"

#define ICMP_ECHO        8
#define ICMP_ECHOREPLY   0

using namespace std;
struct sockaddr_in sasend; 
struct sockaddr_in sarecv; 
//register all functions
void sig_alrm(int );
void readloop(char *);
void send_v4();
void proc_v4(char *, ssize_t , struct timeval *, char *);
unsigned short in_cksum(unsigned short *, int );


//-----------

int sockfd ;
int nsent=0;
pid_t pid ;
int datalen = 56; /* data that goes with ICMP echo request */
int main(int argc, char **argv)
{
char *host = argv[1];  //Host address 
pid = getpid();
signal(SIGALRM, sig_alrm);
printf("PING %s : %d data bytes\n", argv[1], datalen);
bzero(&sasend, sizeof(sasend));
sasend.sin_family = AF_INET;
sasend.sin_addr.s_addr = inet_addr(argv[1]);

readloop(argv[1]);

exit(0);
}



void sig_alrm(int signo)
{
send_v4();
alarm(5);
return;
}
void readloop(char *host)
{
  

 sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
setuid(getuid()); /* don&#39;t need special permissions any more */
sig_alrm(SIGALRM); /* send first packet */
for ( ; ; ) {
socklen_t size = sizeof(sarecv);
//---------
int n;
char recvbuf[1024];

struct timeval tval;
//----------
n = recvfrom(sockfd, recvbuf, sizeof(recvbuf), 0,
(struct sockaddr*) &sarecv, &size);

cout<<n<<endl;

if (n < 0) {
if (errno == EINTR) continue;
else
 {printf("recvfrom error"); break;}
}
else{
gettimeofday(&tval, NULL);
proc_v4(recvbuf, n, &tval, host);}
}
}

void send_v4(void)
{   

  struct icmphdr* icmp;
  char sendbuf[1024];
  int len;

icmp = (struct icmphdr *) sendbuf;
icmp->type = ICMP_ECHO;
icmp->code = 0;
icmp->un.echo.id= pid;
icmp->un.echo.sequence = nsent++;

gettimeofday( &icmp->data, NULL);

icmp->msg ="Hello";



len = 8 + datalen; /* checksum ICMP header and data */
icmp->checksum  = 0;
icmp->checksum    = in_cksum((u_short *) icmp, len);   //write  in_chsum code
sendto(sockfd, sendbuf, len, 0, (struct sockaddr *) &sasend,
sizeof(sasend));
}
void proc_v4(char *ptr, ssize_t len, struct timeval *tvrecv, char *host)
{
  //----------
  ssize_t hlen1,icmplen;
  struct icmphdr* icmp;
  struct iphdr* ip;
  //------
ip = (struct iphdr *) ptr; /* start of IP header */
hlen1 = ip->ihl << 2; /* length of IP header */
icmp = (struct icmphdr *) (ptr + hlen1); /* start of ICMP header */
if ( (icmplen = len - hlen1) < 8)
printf("icmplen (%d) < 8", icmplen);
if (icmp->type == ICMP_ECHOREPLY) {
if (icmp->un.echo.id  != pid)
return; /* not a response to our ECHO_REQUEST */
if (icmplen < 16)
printf("icmplen (%d) < 16", icmplen);
struct timeval *tvsend = &icmp->data;

//cout<<icmp->data->tv_sec <<"sec  "<<icmp->data->tv_usec<<" usec\n";
//cout<<tvrecv->tv_sec <<"sec  "<<tvrecv->tv_usec<<" usec\n";

//tv_sub(tvrecv, tvsend);       


char* datarec=icmp->msg;
double rtt = (double)(tvrecv->tv_sec - tvsend->tv_sec) / 1000000.0 + (double)(tvrecv->tv_usec - tvsend->tv_usec)  / 1000.0;  //datatype for rtt??
printf("%d bytes from %s: seq=%u, ttl=%d, rtt=%.3f ms  Data received=%s\n",
icmplen, host,icmp->un.echo.sequence, ip->ttl, rtt,datarec);

}
}


unsigned short in_cksum(unsigned short *addr, int len)
{
    register int sum = 0;
    u_short answer = 0;
    register u_short *w = addr;
    register int nleft = len;
    /*
     * Our algorithm is simple, using a 32 bit accumulator (sum), we add
     * sequential 16 bit words to it, and at the end, fold back all the
     * carry bits from the top 16 bits into the lower 16 bits.
     */
    while (nleft > 1)
    {
      sum += *w++;
      nleft -= 2;
    }
    /* mop up an odd byte, if necessary */
    if (nleft == 1)
    {
      *(u_char *) (&answer) = *(u_char *) w;
      sum += answer;
    }
    /* add back carry outs from top 16 bits to low 16 bits */
    sum = (sum >> 16) + (sum & 0xffff);       /* add hi 16 to low 16 */
    sum += (sum >> 16);               /* add carry */
    answer = ~sum;              /* truncate to 16 bits */
    return (answer);
}