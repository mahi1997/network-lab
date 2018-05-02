#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>


#define QUEUE_NAME  "/test_queue"
#define MAX_SIZE    1024
#define MSG_STOP    "exit"


int main(int argc, char **argv)
{
    mqd_t mq;
    char buffer[MAX_SIZE];

    /* open the mail queue */
    mq = mq_open(QUEUE_NAME, O_WRONLY);
    //CHECK((mqd_t)-1 != mq);


    printf("Send to server (enter \"exit\" to stop it):\n");

    do {
        printf("enter your message..\n");
        fflush(stdout);

        memset(buffer, 0, MAX_SIZE);
        fgets(buffer, MAX_SIZE, stdin);

        /* send the message */
        if(0 <= mq_send(mq, buffer, MAX_SIZE, 0))
            printf("msg sent..\n");

    } while (strncmp(buffer, MSG_STOP, strlen(MSG_STOP)));

    /* cleanup */
    mq_close(mq);

    return 0;

}