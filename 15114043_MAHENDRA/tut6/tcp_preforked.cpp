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

#define CHNO 10 // Number of children

pid_t pids[CHNO];

void handle(int signo) {
	for(int i = 0; i < CHNO; i++) {
		kill(pids[i], SIGTERM);
	}
	while(wait(NULL) > 0);

	cout << "All children killed, now exiting..." << endl;

	exit(0);
}

void child_main(int listenfd) {
	struct sockaddr_in client;
	unsigned int clilen;
	char buf[512];

	for(;;) {
		bzero(&client, sizeof(client));
		clilen = sizeof(client);
		cout << "Client " << getpid() << " serving ... Receieved = ";
		int connfd = accept(listenfd, (struct sockaddr *) &client, &clilen);
		int n = recv(connfd, buf, 512, 0);
		cout << buf << " ";
		send(connfd, buf, n, 0);
		cout << "... now echoed";
		close(connfd);
		cout << " ... connection closed" << endl;
	}
}

pid_t child_make(int listenfd) {
	pid_t pid = fork();
	if(pid > 0) {
		printf("Child with pid %d\n", pid);
		return pid;
	}

	child_main(listenfd);
}

int main() {
	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server;
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(9999);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	int on = 1;
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (void *) &on, sizeof(on));

	bind(listenfd, (struct sockaddr *) &server, sizeof(server));

	listen(listenfd, 5);

	for(int i = 0; i < CHNO; i++) {
		pids[i] = child_make(listenfd);
	}

	cout << "Server setup" << endl;

	signal(SIGINT, handle);

	while(1) pause();
}