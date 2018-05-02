#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int main(void)
{
    int listenfd = 0;
    int sizeB = 25600;
    int connfd = 0;
    struct sockaddr_in serv_addr;
    char sendBuff[1025];
    int numrv;

    listenfd = socket(AF_INET, SOCK_DGRAM, 0);

    printf("Socket retrieve success\n");

    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);

    if(bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr) )  == -1){
        printf("Bind Error\n");
        exit(0);
    }

    // if(listen(listenfd, 10) == -1)
    // {
    //     printf("Failed to listen\n");
    //     return -1;
    // }


    struct sockaddr cli_addr;
    int m = sizeof(cli_addr);

    for(;;){
        char msg[100];
        int bytes_rec = recvfrom(listenfd, msg, 100, 0,(struct sockaddr *)  &cli_addr, &m);

        FILE *fp = fopen("img.jpg","rb");
        if(fp==NULL)
        {
            printf("File opern error");
            return 1;   
        }   

        /* Read data from file and send it */
        while(1)
        {
            /* First read file in chunks of 256 bytes */
            unsigned char buff[25600]={0};
            int nread = fread(buff,1,sizeB,fp);
            printf("Bytes read %d \n", nread);        

            /* If read was success, send data. */
            if(nread > 0)
            {
                printf("Sending \n");
                //write(connfd, buff, nread);
                sendto(listenfd, buff, nread, 0,  (struct sockaddr *) &cli_addr, m);
            }

            if (nread < sizeB)
            {
                sendto(listenfd, NULL, 0, 0,  (struct sockaddr *) &cli_addr, m);
                if (feof(fp))
                    printf("End of file\n");
                if (ferror(fp))
                    printf("Error reading\n");
                break;
            }
        }

        fclose(fp);
    }
    

    //sleep(1);


    return 0;
}