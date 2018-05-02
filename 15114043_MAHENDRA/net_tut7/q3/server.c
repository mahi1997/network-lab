
/*
     add_server.c: A server to add numbers received in message.

 */
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define SERVER_FIFO "/tmp/addition_fifo_server"
#define MAX_NUMBERS 500

int main (int argc, char **argv)
{
    int fd, fd_client, bytes_read, i;
    char buf [4096];
    char *return_fifo;
    char *mstring;


    if ((mkfifo (SERVER_FIFO, 0664) == -1) && (errno != EEXIST)) {
        perror ("mkfifo");
        exit (1);
    }
    if ((fd = open (SERVER_FIFO, O_RDONLY)) == -1)
        perror ("open");


     while (1) {
         // get a message
         memset (buf, '\0', sizeof (buf));
         if ((bytes_read = read (fd, buf, sizeof (buf))) == -1)
             perror ("read");
         if (bytes_read == 0)
             continue;

         if (bytes_read > 0) {
             return_fifo = strtok (buf, ", \n");
             printf("%s\n", return_fifo);
             i = 0;
             mstring = strtok (NULL, ", \n");

             unsigned int error = 0;
             

        
             for(int j=0; mstring[j] != NULL; j++){
                  mstring[j]  = toupper(mstring[j]);
            }

             /* Send the result */
             if ((fd_client = open (return_fifo, O_WRONLY)) == -1) {
                 perror ("open: client fifo");
                 continue;
             }

             if (error)
                 sprintf (buf, "Error in input.\n");
             else
                 sprintf (buf, "Upper = %s\n", mstring);

             if (write (fd_client, buf, strlen (buf)) != strlen (buf))
                 perror ("write");

             if (close (fd_client) == -1)
                 perror ("close");
         }

     }
}