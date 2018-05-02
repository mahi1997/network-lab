
#include <signal.h>
#include <unistd.h>
#include <bits/stdc++.h>

using namespace std;


int main(int argc, char **argv)
{
   
    cout<<"Helloworld"<<endl;
    gid_t gid;
    if(gid=getgid()<0)
        cout<<"eroor in group id printing"<<endl;
    else
        cout<<"Group id"<< gid<<endl;
    return 0;

    }