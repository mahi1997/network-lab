
#include <signal.h>
#include <unistd.h>
#include <bits/stdc++.h>

using namespace std;

void sig_handler(int signo){
	if(signo== SIGINT)
	{  cout<<"Singal received"<<endl;
		sleep(5);
	}
}

int main(int argc, char **argv)
{
   
    if(signal(SIGINT,sig_handler)==SIG_ERR)
    cout<<"can not handle signal"<<endl;
    
  while(1);

    return 0;

    }