
#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;


int main(int argc,char *argv[])
{
	string data,poly;
	int arg = atoi(argv[1]);
	cin>>data>>poly;
	data[arg]='1'?'0':'1';
	cout<<data<<endl;
	cout<<poly<<endl;
	return 0;
}
