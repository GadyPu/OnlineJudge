#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#define N 20 + 2  
char buf[N][N];  
int ans;  
void InputData(int m,int n,int *x,int *y)  
{  
    int i, j;  
    memset(buf, 0, sizeof(buf));  
    for (i = 0; i < n; i++)  
    {  
        getchar();  
        for (j = 0; j < m; j++)  
        {  
            scanf("%c", &buf[i][j]);  
            if (buf[i][j] == '@')  
                *x = i, *y = j;  
        }  
    }  
}  
void dfs(int x, int y)  
{  
    buf[x][y] = '#';  
    int i, dx[4] = { -1, 1, 0, 0 }, dy[4] = { 0, 0, 1, -1 };  
    for (i = 0; i < 4; i++)  
    {  
        int nx = x + dx[i], ny = y + dy[i];  
        if (x >= 0 && x < N && y >= 0 && y < N && buf[nx][ny] == '.')  
        {  
            ans++;  
            dfs(nx, ny);  
        }  
    }  
}  
void solve(int m, int n)  
{  
    int x = 0, y = 0;  
    InputData(m, n,&x,&y);  
    ans = 1;  
    dfs(x, y);  
    printf("%d\n",ans);  
}  
int main()  
{  
    int m, n;  
    while (EOF != scanf("%d %d", &m, &n) && 0!=m && 0!=n)  
        solve(m, n);  
    return 0;  
}  
