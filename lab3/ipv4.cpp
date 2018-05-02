#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

char decimaltogethex(int a)
{
	if(a>=0&&a<=9) return char((int)('0')+(int)(a)); //if number is inbetween 1 0 and 9
	return char((int)('a')+(int)(a-10));               //for A-- to F
}

string ipv4toipv6(string ipv4)

{
	// let ip4 addr is 172.64.1.4
	string ans;    
	ipv4+='.';  //now ip4=172.64.1.4.


	int a,i=0,p,q;
	char c;

	for(int x=0;x<4;x++)
	{
		a=0;
		while(ipv4[i]!='.')
		{
			c=ipv4[i];
			a = a*10 + int((int)(c)-(int)('0'));
			i++;
		}
			p=a/16; q=a%16; i++;

			ans=ans+decimaltogethex(p)+decimaltogethex(q);
			if(x==1) ans+=':';
	}
	return ans;

}

int main()
{
	string ipv4,ipv6,str;
	cin>>ipv4;
	str= ipv4toipv6(ipv4);
	ipv6="0:0:0:0:0:ffff:"+str;

	cout<<ipv6<<endl;
	return 0;
}
