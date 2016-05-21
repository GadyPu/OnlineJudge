#include<stdio.h>  
#include<string.h>  
#include<stdlib.h>  
#define N 8  
int tot;  
char chess[N][N];  
void read(int n)  
{  
    int i, j;  
    for (i = 0; i < n; i++)  
    {  
        getchar();  
        for (j = 0; j < n; j++)  
            scanf("%c", &chess[i][j]);  
    }  
}  
int checkout(int x, int y)  
{  
    int i;  
    for (i = 0; i < x; i++){  
        if ('Q' == chess[i][y])  
            return 1;  
    }  
    return 0;  
}  
void dfs(int cur, int num, int n, int k)  
{  
    int i, j;  
    if (num == k)  
    {  
        tot++;  
    }  
    else  
    {  
        for (i = cur; i < n; i++)  
        {  
            for (j = 0; j < n; j++)  
            {  
                if ('#' == chess[i][j] && !checkout(i, j))  
                {     
                    chess[i][j] = 'Q';  
                    dfs(i + 1, num + 1, n, k);  
                    chess[i][j] = '#';  
                }  
            }  
        }  
    }  
}  
void solve(int n, int k)  
{  
    tot = 0;  
    read(n);  
    dfs(0, 0, n, k);  
    printf("%d\n", tot);  
}  
int main()  
{  
    int n, k;  
    while (EOF != scanf("%d %d", &n, &k) && -1 != n && -1 != k)  
        solve(n, k);  
    return 0;  
}  
