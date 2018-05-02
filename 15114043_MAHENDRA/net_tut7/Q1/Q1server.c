#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <mqueue.h>



#define QUEUE_NAME  "/test_queue"
#define MAX_SIZE    1024
#define MSG_STOP    "exit"
/*

struct mq_attr {
    long mq_flags;       // Flags: 0 or O_NONBLOCK 
    long mq_maxmsg;      // Max. # of messages on queue 
    long mq_msgsize;     // Max. message size (bytes) 
    long mq_curmsgs;   };  // # of messages currently in queue 
    */
 

int main(int argc, char **argv)
{
    mqd_t mq;
    struct mq_attr attr;
    char buffer[MAX_SIZE + 1];
    int must_stop = 0;

    /* initialize the queue attributes */
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;

    /* create the message queue */
    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, 0644, &attr);
    //CHECK((mqd_t)-1 != mq);

    mq_getattr( mq, &attr);

    printf("msg flags: %d\n" ,attr.mq_flags);
    printf("msg maximum number of size: %d\n" ,attr.mq_maxmsg);
    printf("msg size: %d\n" ,attr.mq_msgsize);
    printf("msg in queue: %d\n" ,attr.mq_curmsgs);

    do {
        ssize_t bytes_read;
        printf("Received: %s\n", buffer);

        /* receive the message */
        bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);
        //CHECK(bytes_read >= 0);

        buffer[bytes_read] = '\0';
        if (! strncmp(buffer, MSG_STOP, strlen(MSG_STOP)))
        {
            must_stop = 1;
        }
        else
        {
            printf("Received: %s\n", buffer);
        }
    } while (1);

    /* cleanup */
    mq_close(mq);
    mq_unlink(QUEUE_NAME);

    return 0;
}
