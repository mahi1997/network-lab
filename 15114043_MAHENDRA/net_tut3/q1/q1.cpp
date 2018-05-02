#include<iostream>
#include<fstream>
#include<signal.h>
#include<unistd.h>
using namespace std;
int d=2;char * argvv[5];int k=0;
void displayfile();
void sig_int_handler(int sig)
{
	if(sig==SIGINT)
	{
			d++;
			displayfile();
	}
}
void displayfile()
{
	while(d<5)
	{
	cout<<endl<<"begining of file "<<argvv[d]<<endl;
	fstream file;
	file.open(argvv[d]);
	string str="";
	while(!file.eof())
	{
		getline(file,str);
		cout<<str;
		
	}
	file.close();

	signal(SIGINT,sig_int_handler);
	sleep(k);
	d++;
	}

}


int main(int argc,char *argv[])
{	
	//cout<<argv[1];
	for(int i=1;i<5;i++)
	{argvv[i]=argv[i];
	}
	char c=argvv[1][0];
	k=c-48;
	//cout<<c;
	//cout<<k;
	displayfile();
	return 0;
}
