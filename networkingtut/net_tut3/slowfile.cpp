#include <signal.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <fstream>

using namespace std;
int c=2; int k=0;
fstream myFile;

void sig_handler(int signo){
	if(signo== SIGINT)
	{   myFile.close();
		sleep(k);
	}
}


int main(int argc, char *argv[])
{
	
	if(argc==5){
		//register sigfpe
		 signal(SIGINT,sig_handler);

         k=atoi(argv[1]);
         while(c<=4){


         	//fstream myFile;
		myFile.open(argv[c]);
		//string generator="";
		string fline;
		while(!myFile.eof()){

			getline(myFile,fline);
			cout<<fline<<endl;
			 raise(SIGINT);
		}
        
        myFile.close();
       
        sleep(k);
        c++;

         }

	}
  
    return 0;

    }
