#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#define N 303  
#define Size 10000  
#define INF 0x3f3f3f3f  
#define min(a,b) ((a)>(b)?(b):(a))  
typedef struct node{int x,y,t;}Node;  
Node Queue[Size],now,cur;  
int map[N][N],vis[N][N];  
const int dx[]={-1,1,0,0},dy[]={0,0,-1,1};  
int bfs()  
{  
    int i,front=0,rear=0;  
    memset(vis,0,sizeof(vis));  
    now=(Node){0,0,0};  
    vis[0][0]=1;  
    Queue[rear++]=now;  
    while(front<rear)  
    {  
        now=Queue[front++];  
        if(INF == map[now.x][now.y]) return now.t;  
        for(i=0;i<4;i++)  
        {  
            int nx=dx[i]+now.x,ny=dy[i]+now.y;  
            if(nx>=0 && nx<N && ny>=0 && ny<N && now.t + 1 < map[nx][ny] && !vis[nx][ny])  
            {  
                vis[nx][ny]=1;  
                cur=(Node){nx,ny,now.t + 1};  
                Queue[rear++]=cur;  
            }  
        }  
    }  
    return -1;  
}  
int main()  
{  
    #ifdef LOCAL  
    freopen("input.txt","r",stdin);  
    #endif  
    int i,t,xi,yi,ti;  
    memset(map,INF,sizeof(map));  
    scanf("%d",&t);  
    while(t--)  
    {  
        scanf("%d %d %d",&xi,&yi,&ti);  
        for(i=0;i<4;i++)  
        {  
            int nx=dx[i]+xi,ny=dy[i]+yi;  
            if(nx>=0 && nx<N && ny>=0 && ny<N)  
                map[nx][ny]=min(map[nx][ny],ti);  
        }  
        map[xi][yi]=min(map[xi][yi],ti);  
    }  
    printf("%d\n",bfs());  
    return 0;  
}  
