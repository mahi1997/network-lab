

#include <bits/stdc++.h>
#include <iostream>
//#include <stdlib>
using namespace std;
 

int main(int argc ,char* argv[]){
	if(argc!=4){
         //wrong input
         cout<<"commad is calc number1 operator number2"<<endl;
	}
        else{
        int a= atoi(argv[1]);
        int b= atoi(argv[3]);
        char op=argv[2][0];
        switch(op){
        case '+':
        cout<<a+b<<endl;
        break;
        case '-':
        cout<<a-b<<endl;
        break;
        case '*':
        // your command should like  calc 5 \* 4 to get 20 ..bcoz *  
        // * is derefrencing pointer ... 
        cout<<a*b<<endl;
        break;
        case '/':
        cout<<a/b<<endl;
        break;
        }
        }
	
	return 0;
} 
