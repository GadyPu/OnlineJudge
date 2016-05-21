#include<stdio.h>  
#include<string.h>  
#include<stdlib.h>  
#define N 1002  
#define Max(a,b) ((a)>(b)?(a):(b))  
int read[N][N] ,dp[N][N];  
void ReadData(int n)  
{  
    memset(read, 0, sizeof(read));  
    int i, j;  
    for (i = 0; i < n; i++)  
    {  
        for (j = 0; j <= i; j++)  
        {  
            scanf("%d", &read[i][j]);  
        }  
    }  
}  
void solve(int n)  
{  
    memset(dp, 0, sizeof(dp));  
    int i, j,T=0;  
    dp[0][1] = read[0][0];  
    for (i = 1; i < n; i++)  
    {  
        for (j = 1; j <= i + 1; j++)  
        {  
            dp[i][j] = Max(dp[i - 1][j - 1], dp[i - 1][j]) + read[i][j - 1];  
            T = Max(dp[i][j], T);  
        }  
    }  
    printf("%d\n", T);  
}  
int main()  
{  
    int n;  
    while (scanf("%d", &n) != EOF)  
    {  
        ReadData(n);  
        solve(n);  
    }  
    return 0;  
}  
