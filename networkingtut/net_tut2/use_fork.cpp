//#include <stdio.h>
#include <unistd.h>
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char **argv)
{
   
    pid_t pid = fork();

    if (pid == 0)
    {
        // child process
        
        cout<< "child process id: "<<getpid()<<endl;
        execv("/helloworld",NULL);
        exit(123);

        
    }
    if (pid > 0)
    {
        // parent process
         cout<< "parent process id: "<<getpid()<<endl;
        
    }
    

    return 0;
}