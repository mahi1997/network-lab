
#include <signal.h>
#include <unistd.h>
#include <bits/stdc++.h>

using namespace std;


int main(int argc, char **argv)
{
   
    cout<<"Helloworld"<<endl;
    pid_t gid;
//setpgrp(getpid(),getegid());
     //cout<<"parent's gid:"<<getpid()<<endl;
    if((gid=getgid())<0)
        cout<<"eroor in group id printing"<<endl;
    else
        cout<<"Group id :"<< gid<<endl;
	 cout<<getgid()<<" "<<getegid()<<" "<<getpgrp()<<" "<<getpgid(getpid())<<endl;
     cout <<argv[1]<<endl;
     cout <<argv[2]<<endl;
   return 0;

    }
