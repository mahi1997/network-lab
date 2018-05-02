#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <pthread.h>

void *func(void *x){
    int *id = (int *) x;

    printf("Thread Id: %d \n", *id);

    int sockfd = 0;
    int bytesReceived = 0;
    char recvBuff[256];
    memset(recvBuff, '0', sizeof(recvBuff));
    struct sockaddr_in serv_addr;

    /* Create a socket first */
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0))< 0)
    {
        printf("\n Error : Could not create socket \n");
        return NULL;
    }

    /* Initialize sockaddr_in data structure */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000); // port
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    /* Attempt a connection */
    // if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
    // {
    //     printf("\n Error : Connect Failed \n");
    //     return 1;
    // }

    char * msg = "test";
    sendto(sockfd, msg, sizeof(msg), 0 , (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    /* Create file where data will be stored */
    FILE *fp;
    fp = fopen("img.jpg", "ab"); 
    if(NULL == fp)
    {
        printf("Error opening file");
        return NULL;
    }

    /* Receive data in chunks of 256 bytes */
    int count =0;
    while((bytesReceived = read(sockfd, recvBuff, 256)) > 0)
    {
        //printf("Bytes received %d\n",bytesReceived);    
        count++;
        // recvBuff[n] = 0;
        fwrite(recvBuff, 1,bytesReceived,fp);
        //printf("%s \n", recvBuff);
    }

    printf("Number of packets %d\n",count);  

    if(bytesReceived < 0)
    {
        printf("\n Read Error \n");
    }

}

int main(void)
{
    int i;
    pthread_t tid;
    for(i=0;i<10;i++){
        pthread_create(&tid, NULL, func, &i);
    }

    pthread_exit(NULL);

    

    return 0;
}