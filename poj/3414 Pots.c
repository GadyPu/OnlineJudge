#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#define Size 100 + 10  
typedef struct node  
{  
    int ix,iy;  
}Node;  
Node Queue[100000],cur,now;  
int rear,front,flag,dir[100000],dist[100000],vis[Size][Size],fa[100000],last_dir[100000];  
const char *buf[8]={"FILL(1)","FILL(2)","DROP(1)","DROP(2)","POUR(1,2)","POUR(2,1)","impossible"};  
void bfs(int ai,int bi,int ci)  
{  
    rear=0,front=0;  
    now.ix=0,now.iy=0;  
    Queue[rear++]=now;  
    dist[0]=0;  
    while(front<rear)  
    {  
        now=Queue[front];  
        if(now.ix == ci || now.iy == ci)  
            break;  
        const int dx=now.ix,dy=now.iy;  
        if(dx<ai && !vis[ai][dy])  
        {  
            vis[ai][dy]=1;  
            cur.ix=ai,cur.iy=dy;  
            dist[rear]=dist[front]+1;  
            fa[rear]=front;  
            last_dir[rear]=0;  
            Queue[rear++]=cur;  
        }  
        if(dy<bi && !vis[dx][bi])  
        {  
            vis[dx][bi]=1;  
            cur.ix=dx,cur.iy=bi;  
            dist[rear]=dist[front]+1;  
            fa[rear]=front;  
            last_dir[rear]=1;  
            Queue[rear++]=cur;  
        }  
        if(dx>0 && !vis[0][dy])  
        {  
            vis[0][dy]=1;  
            cur.ix=0,cur.iy=dy;  
            dist[rear]=dist[front]+1;  
            fa[rear]=front;  
            last_dir[rear]=2;  
            Queue[rear++]=cur;  
        }  
        if(dy>0 && !vis[dx][0])  
        {  
            vis[dx][0]=1;  
            cur.ix=dx,cur.iy=0;  
            dist[rear]=dist[front]+1;  
            fa[rear]=front;  
            last_dir[rear]=3;  
            Queue[rear++]=cur;  
        }  
        if(dx>0 && dx<=ai && dy<bi)  
        {  
            int rest=bi-dy;  
            if(rest <= dx && !vis[dx-rest][bi])  
            {  
                vis[dx-rest][bi]=1;  
                cur.ix=dx-rest,cur.iy=bi;  
                dist[rear]=dist[front]+1;  
                fa[rear]=front;  
                last_dir[rear]=4;  
                Queue[rear++]=cur;  
            }  
            else if(rest > dx && !vis[0][dx+dy])  
            {  
                vis[0][dx+dy]=1;  
                cur.ix=0,cur.iy=dx+dy;  
                dist[rear]=dist[front]+1;  
                fa[rear]=front;  
                last_dir[rear]=4;  
                Queue[rear++]=cur;  
            }  
        }  
        if(dy>0 && dy<=bi && dx<ai)  
        {  
            int rest=ai-dx;  
            if(rest<=dy && !vis[ai][dy-rest])  
            {  
                vis[ai][dy-rest]=1;  
                cur.ix=ai,cur.iy=dy-rest;  
                dist[rear]=dist[front]+1;  
                fa[rear]=front;  
                last_dir[rear]=5;  
                Queue[rear++]=cur;  
            }  
            else if(rest>dy && !vis[dx+dy][0])  
            {  
                vis[dx+dy][0]=1;  
                cur.ix=dx+dy,cur.iy=0;  
                dist[rear]=dist[front]+1;  
                fa[rear]=front;  
                last_dir[rear]=5;  
                Queue[rear++]=cur;  
            }  
        }  
        front++;  
    }  
    if(!dist[front])  
    {  
        flag=0;  
        printf("%s\n",buf[6]);  
    }  
    else  
        printf("%d\n",dist[front]);  
}  
void print_path(int ic)  
{  
    int i,num,c=0;  
    for(i=0;i<=rear;i++)  
    {  
        if(Queue[i].ix==ic || Queue[i].iy==ic)  
        {  
            num=i;  
            break;  
        }  
    }  
    while(num)  
    {  
        dir[c++]=last_dir[num];  
        if(num == 0)  
            break;  
        num=fa[num];  
  
    }  
    while(c-- )  
        printf("%s\n",buf[dir[c]]);  
}  
void solve(int ia,int ib,int ic)  
{  
    if((0 == ia && 0 != ib && 0 == ic)||(0!=ia && 0==ib && 0==ic) || (0==ia && 0==ib && 0==ic))  
    {  
        printf("0\n");  
        return;  
    }  
    flag=1;  
    memset(Queue,0,sizeof(Queue));  
    memset(vis,0,sizeof(vis));  
    memset(fa,-1,sizeof(fa));  
    memset(dist,0,sizeof(dist));  
    memset(last_dir,0,sizeof(last_dir));  
    memset(dir,0,sizeof(dir));  
    bfs(ia,ib,ic);  
    if(flag)  
        print_path(ic);  
}  
int main()  
{  
    int ia,ib,ic;  
    while(EOF!=scanf("%d %d %d",&ia,&ib,&ic))  
        solve(ia,ib,ic);  
    return 0;  
} 
