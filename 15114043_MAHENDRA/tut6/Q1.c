/*
** echos.c -- the echo server for echoc.c; demonstrates unix sockets
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCK_PATH "echo_socket\0"

int main(void)
{
	int listenfd, connfd, addrlen,n;
	struct sockaddr_un servaddr, cliaddr,myaddr;
	char str[100];
        
        pid_t pid;
	listenfd = socket(AF_UNIX, SOCK_STREAM, 0);
        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int));
	servaddr.sun_family = AF_UNIX;
	strcpy(servaddr.sun_path, SOCK_PATH);
	unlink(servaddr.sun_path);
	addrlen = sizeof(servaddr.sun_family)+sizeof(servaddr.sun_path);

	bind(listenfd, (struct sockaddr *)&servaddr, addrlen);
        int len=sizeof(myaddr);
        getsockname(listenfd,(struct sockaddr*)&myaddr,&len);
        printf("bound name = %s, returned len = %d\n", myaddr.sun_path, len);
        
       

	listen(listenfd, 5);

	for(;;) 
     {
		printf("Waiting for a connection...\n");
		addrlen = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &addrlen);
                
		printf("Connected.\n");
                
                int lens=sizeof(myaddr);
                    getsockname(listenfd,(struct sockaddr*)&myaddr,&lens);
                    printf("Parent bound name = %s, returned len = %d\n", myaddr.sun_path, lens);

                if(pid=fork()==0)
               {      
                     struct sockaddr_un myaddr2;
                    int len2=sizeof(myaddr2);
                    getsockname(listenfd,(struct sockaddr*)&myaddr2,&len2);
                    printf("Child bound name = %s, returned len = %d\n", myaddr2.sun_path, len2);

                    close(listenfd);

		 while(1)
                      { 
                        bzero(str,100);
			n = read(connfd, str, 100);
                        printf("%s\n",str);
                        write(connfd,str,n);
		      } 

	       }

         close(connfd);

      }

	return 0;
}



