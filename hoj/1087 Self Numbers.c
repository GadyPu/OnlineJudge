#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include<math.h>  
#define N 1000000  
int *Num;  
void CreateTable()  
{  
    int i, j;  
    Num = (int *)malloc(sizeof(int)*(N+5));  
    memset(Num, 0, sizeof(int)*(N+5));  
    for (i = 1; i <=N; i++)  
    {  
        int p = i;  
        int sum = 0;  
        int len = (int)log10((double)i) + 1;  
        for (j = 0; j < len; j++)  
        {  
            sum += p % 10;  
            p /= 10;  
        }  
        int n = sum + i;  
        if (!Num[n] && n<=N)  
        {  
            Num[n] = 1;  
        }  
    }  
}  
int main()  
{  
    CreateTable();  
    int i;  
    for (i = 1; i <=N ; i++)  
    {  
        if (!Num[i])  
            printf("%d\n", i);  
    }  
    return 0;  
}  
