#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include<math.h>  
#define N 6000  
int num[N];  
int IsPrime(int n)  
{  
    int i;  
    for (i = 2; i <= sqrt(n); i++)  
    {  
        if (n % i == 0)  
            return 0;  
    }  
    return 1;  
}  
int CreatePalindromes(int num)  
{  
    int i,j;  
    char A[20] = { 0 };  
    if (num < 10)  
        return num;  
    else  
    {  
        sprintf(A, "%d", num);  
        j = strlen(A);  
        for (i = strlen(A) -2; i >= 0; i--)  
        {  
            A[j++] = A[i];  
        }  
        A[j] = '\0';  
    }  
    return atoi(A);  
}  
void CreateTable()  
{  
    memset(num, 0, sizeof(num));  
    int  i, j = 0;  
    for (i = 5; i <= 99999; i++)  
    {  
        int A = CreatePalindromes(i);  
        if (IsPrime(A) && A<1000000000)  
        {  
            num[j++] = A;  
        }  
        if (A == 7)  
        {  
            num[j++] = 11;  
        }  
    }  
}  
void PrintResult(int m,int n)  
{  
    int i;  
    for (i = 0; i < N; i++)  
    {  
        if (num[i] >= m && num[i] <= n)  
            printf("%d\n", num[i]);  
    }  
}  
int main()  
{  
    int m, n;  
    CreateTable();  
    scanf("%d%d", &m, &n);  
    PrintResult(m, n);  
    return 0;  
}  
