#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <stddef.h>

struct msgbuf{
  long mtype;
  char msg[256];
};

void func(char * temp) {
  char * name;
  name = strtok(temp,":");

  char *s = name;
  while (*s) {
    *s = toupper((unsigned char) *s);
    s++;
  }

}

int main(int argc, char* argv[]){
  key_t key;
  int msqid;
  key = ftok(argv[1], 'b');
  msqid = msgget(key, 0666 | IPC_CREAT);

  struct msgbuf msg;
  while(1){

    msgrcv(msqid, &msg, 256, 6, 0);
    printf("%s\n", msg.msg);

    for(int i=0; msg.msg[i] != NULL; i++){
      msg.msg[i] = toupper(msg.msg[i]);
    }

    msgsnd(msqid, &msg, 256, 0);

  }
  return 0;
}
