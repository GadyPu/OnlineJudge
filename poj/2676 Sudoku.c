#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#define N 9  
char buf[N+2];  
int map[N][N];  
struct tmp  
{  
    int x,y;  
}rec[N*N];  
int checkout(const int x,const int y,const int key)  
{  
    int i,j;  
    for(i=0;i<N;i++)  
    {  
        if(key == map[x][i] || key == map[i][y])  
            return 0;  
    }  
    for(i=x/3*3;i<=x/3*3+2;i++)  
    {  
        for(j=y/3*3;j<=y/3*3+2;j++)  
            if(key == map[i][j])  
                return 0;  
    }  
    return 1;  
}  
void PrintRes()  
{  
    int i,j;  
    for(i=0;i < N;i++)  
    {  
        for(j=0;j < N;j++)  
        {  
            printf("%d",map[i][j]);  
        }  
        printf("\n");  
    }  
}  
int dfs(int count)  
{  
    int i;  
    if(count < 0)  
    {  
        PrintRes();  
        return 0;  
    }  
    for(i=1;i<=N;i++)  
    {  
        int dx=rec[count].x,dy=rec[count].y;  
        if(checkout(dx,dy,i))  
        {  
            map[dx][dy]=i;  
            if(!dfs(count-1))  
                return ;  
            map[dx][dy]=0;  
        }  
    }  
    return 1;  
}  
void solve()  
{  
    int i,j,count=0;  
    memset(rec,0,sizeof(rec));  
    memset(map,0,sizeof(map));  
    for(i=0;i<N;i++)  
    {  
        scanf("%s",buf);  
        for(j=0;j<N;j++)  
        {  
            if(0 == buf[j]-'0')  
            {  
                rec[count].x=i;  
                rec[count++].y=j;  
            }  
            else  
                map[i][j]=buf[j]-'0';  
        }  
    }  
    dfs(--count);  
}  
int main()  
{  
    int t;  
    scanf("%d",&t);  
    while(t--)  
        solve();  
    return 0;  
}  
