#include<stdio.h>   
#include<time.h>   

int main()   
{   
    clock_t t1, t2;  
    t1 = clock();   
    int i;
    for(i = 0; i < 1000000; i++)   
    {   
        int x = 90;  
    }   

    t2 = clock();   

    float diff = t2-t1;   
    printf("%f",diff);   

    return 0;   
}