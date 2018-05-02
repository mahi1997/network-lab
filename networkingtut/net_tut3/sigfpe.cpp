
#include <signal.h>
#include <unistd.h>
#include <bits/stdc++.h>

using namespace std;

void sig_handler(int signo){
	if(signo== SIGFPE)
	{  cout<<"undefined"<<endl;
		//sleep(5);
	}
}

int main(int argc, char **argv)
{
	//register sigfpe
   signal(SIGFPE,sig_handler);
   
  while(1){
 double x;
cin>>x;
double num=(x-3.0)*(x+0.5);
double den=(x-0.5)*(x+0.4);
if(den==0.0){
	cout<<x<<" ";
	raise(SIGFPE);
}
else
cout<<x<<" "<<num/den<<endl;
}



    return 0;

    }
