	

#include <sys/socket.h>
#include <stdio.h>

int main(int argc, char **argv)
{
 int sockfd, recvbuff;
 socklen_t optlen;

 sockfd = socket(AF_INET, SOCK_DGRAM, 0);
 if(sockfd == -1)
     printf("Error");

 int res = 0;

 // Get buffer size
 optlen = sizeof(recvbuff);
 res = getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &recvbuff, &optlen);

 if(res == -1)
     printf("Error getsockopt one");
 else
     printf("recv buffer size = %d\n", recvbuff);

 // Set buffer size
 recvbuff = 98304;

 printf("sets the send buffer to %d\n", recvbuff);
 res = setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &recvbuff, sizeof(recvbuff));

 if(res == -1)
     printf("Error setsockopt");


 // Get buffer size
 optlen = sizeof(recvbuff);
 res = getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &recvbuff, &optlen);

 if(res == -1)
     printf("Error getsockopt two");
 else
     printf("send buffer size = %d\n", recvbuff);

 return 0;
}