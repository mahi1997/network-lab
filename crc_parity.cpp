#include<stdio.h>
#include<string.h>
#include<bits/stdc++.h>
#include<fstream>
//#include<file.h>

using namespace std;

 
//string t="";
//string cs="";
//g[]="1101";

int a,e,c;
 
string xor_func(string g,string cs){
	int N=g.length();
    for(c = 1;c < N; c++)
    cs[c] = (( cs[c] == g[c])?'0':'1');
return cs;
}
 
string crc(string g,string t){
	int N=g.length();
	string cs="";
    for(e=0;e<N;e++)
        cs+=t[e];
    do{
        if(cs[0]=='1')
           cs= xor_func(g,cs);
        for(c=0;c<N-1;c++)
            cs[c]=cs[c+1];
        cs[c]=t[e++];
    }while(e<=a+N-1);
    return cs;
}
 
int main(int argc,char* argv[])
{
	if(argc==3){
		int N=strlen(argv[2]);
		fstream myFile;
		myFile.open(argv[1]);
		string generator="";
		string fline;
		while(!myFile.eof()){
			getline(myFile,fline);
			generator+=fline;
		}
        myFile.close();
		cout<<"\nGeneratng polynomial : "<<argv[2]<<endl;
    string t=generator;
    cout<<t<<endl;
    a=t.length();
    for(e=a;e<a+N-1;e++)
        t+="0";
    cout<<"\nModified data is : "<<t<<endl;
    string cs=crc(argv[2],t);
    cout<<"\nChecksum is : "<<cs<<endl;

    for(e=a;e<a+N-1;e++)
        t[e]=cs[e-a];
    cout<<"\nFinal codeword is : "<<t<<endl;

	}
	//--------------------------
	
	if(argc==4){
		int e=atoi(argv[2]);
		//string t=argv[1];

		fstream myFile;
		myFile.open(argv[1]);
		string generator="";
		string fline;
		while(!myFile.eof()){
			getline(myFile,fline);
			generator+=fline;
		}
        myFile.close();

        string t=generator;
		t[e-1]=(t[e-1]=='0')?'1':'0';
        cout<<"\nencryipted  data : \n"<<t<<endl;
        int N=strlen(argv[3]);

string cs=crc(argv[3],t);
        for(e=0;(e<N-1) && (cs[e]=='0');e++);
        if(e<N-1)
            cout<<"Error detected"<<endl;
        else
            cout<<"\nNo error detected"<<endl;


	}

	
        return 0;
}
