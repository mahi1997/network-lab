//#include <stdio.h>
#include <unistd.h>
#include <bits/stdc++.h>

using namespace std;
int main()
{
     static int count=0;

     for(int i=0;i<5;i++){
        pid_t pid = fork();
        if(pid==0){
            
            count++;
        }
        if(pid>0){
            count++;
        }
     }
    
   cout<<"Total newly created proccess: "<<count<<endl;
    
    return 0;
}