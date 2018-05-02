#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <string.h>

int main(void)
{
 FILE* fp;
 char* command;
 char* line;

 line = malloc(200 * sizeof(char));
 command = malloc(200 * sizeof(char));
 strcpy(command,"kill -l");

 fp = popen(command,"r");
 
 int num=0;
 while((fgets(line,  INT_MAX, fp)))
 { 
  printf("%s \n",line);
  num++;
 }
  printf("Total number of signals %d \n",num-1);
 return 0;
}
