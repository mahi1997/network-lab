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
        
        
    cout<< "child group process id: "<<getgid()<<endl;
        execv("helloworld",argv);
        exit(0);

        
    }
    if (pid > 0)
    {
        // parent process
         cout<< "parent group id: "<<getgid()<<endl;
        
    }
    

    return 0;
}
