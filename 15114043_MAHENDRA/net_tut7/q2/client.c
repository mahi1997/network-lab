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

int main(int argc, char* argv[]){
  key_t key;
  int msqid;
  key = ftok(argv[1], 'b');
  msqid = msgget(key, 0666 | IPC_CREAT);

  struct msgbuf msg;
  msg.mtype = 6;
  scanf("%s", msg.msg);
  msgsnd(msqid, &msg, 256, 0);

  struct msgbuf msg2;
  msgrcv(msqid, &msg2, 256, 6, 0);
  printf("%s\n", msg2.msg);
  return 0;
}
