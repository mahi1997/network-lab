#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <strings.h>
#include <arpa/inet.h>
using namespace std;

int main() {
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server;
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(9999);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	char buf[512];

	connect(sockfd, (struct sockaddr *) &server, sizeof(server));

	send(sockfd, "Hello", 5, 0);
	recv(sockfd, buf, 512, 0);

	printf("%s\n", buf);
	close(sockfd);

	return 0;
}