#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#define N 30  
int buf[N][N] = { 0 };  
int ans[N + N];  
void Init()  
{  
    int i, j, k;  
    for (i = 0; i < N; i++)  
        buf[i][0] = 1;  
    for (i = 0; i < N; i++)  
    {  
        for (j = 1; j <= i + 1; j++)  
        {  
            int c = 0;  
            for (k = 0; k < N; k++)  
            {  
                int temp = buf[i][k] * j + c;  
                buf[i][k] = temp % 10;  
                c = temp / 10;  
            }  
        }  
    }  
}  
void solve(int m, int n)  
{  
    memset(ans, 0, sizeof(ans));  
    int i, j;  
    for (i = m - 1; i < n; i++)  
    {  
        int c = 0;  
        for (j = 0; j < N; j++)  
        {  
            ans[j] += buf[i][j] + c;  
            c = ans[j] / 10;  
            ans[j] %= 10;  
        }  
    }  
    j = N - 1;  
    while (!ans[j])  
        j--;  
    for (; j >= 0; j--)  
        printf("%d", ans[j]);  
    printf("\n");  
}  
  
int main()  
{  
    Init();  
    int m, n;  
    while (EOF != scanf("%d %d", &m, &n) && 0 != m && 0 != n)  
        solve(m, n);  
    return 0;  
}  
