#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#define N 100 + 10  
#define INF 0x3f3f3f3f  
#define max(a,b) ((a)>(b)?(a):(b))  
#define min(a,b) ((a)>(b)?(b):(a))  
typedef struct Edge{int to,cost;}edge;  
typedef struct info{int dist,vertex;}pair;  
typedef struct pri_heap  
{  
    pair tp[N];  
    int nSize;  
}Heap;  
Heap que;  
edge G[N][N];  
int n,E,vis[N],dist[N],adjcount[N],ans[N];  
void Init()  
{  
    que.nSize=0;  
}  
int empty()  
{  
    return 0==que.nSize;  
}  
void push(int dist,int v)  
{  
    int i=que.nSize++;  
    pair tmp;  
    tmp.dist=dist,tmp.vertex=v;  
    while(i>0)  
    {  
        int p=(i-1)>>1;  
        if(que.tp[p].dist<=tmp.dist) break;  
        que.tp[i]=que.tp[p];  
        i=p;  
    }  
    que.tp[i]=tmp;  
}  
pair pop()  
{  
    pair ret=que.tp[0];  
    pair tmp=que.tp[--que.nSize];  
    int i=0;  
    while(i*2+1 < que.nSize)  
    {  
        int a=i*2+1,b=i*2+2;  
        if(i*2+2 < que.nSize && que.tp[a].dist > que.tp[b].dist) a=b;  
        if(que.tp[a].dist >= tmp.dist) break;  
        que.tp[i]=que.tp[a];  
        i=a;  
    }  
    que.tp[i]=tmp;  
    return ret;  
}  
void dijkstra(int s)  
{  
    int i;  
    Init();  
    memset(vis,0,sizeof(vis));  
    for(i=0;i<n;i++) dist[i]=(i==s?0:INF);  
    push(0,s);  
    while(!empty())  
    {  
        pair pii=pop();  
        int v=pii.vertex;  
        if(vis[v]) continue;  
        vis[v]=1;  
        for(i=0;i<adjcount[v];i++)  
        {  
            edge e=G[v][i];  
            if(dist[e.to] > dist[v] + e.cost)  
            {  
                dist[e.to] = dist[v] + e.cost;  
                push(dist[e.to],e.to);  
            }  
        }  
    }  
}  
void solve()  
{  
    int i,j,res=INF,index=0;  
    memset(adjcount,0,sizeof(adjcount));  
    for(i=0;i<n;i++)  
    {  
        scanf("%d",&E);  
        adjcount[i]=E;  
        for(j=0;j<E;j++)  
        {  
            scanf("%d %d",&G[i][j].to,&G[i][j].cost);  
            G[i][j].to--;  
        }  
        ans[i]=-INF;  
    }  
    for(i=0;i<n;i++)  
    {  
        dijkstra(i);  
        for(j=0;j<n;j++)  
            ans[i]=max(ans[i],dist[j]);  
    }  
    for(i=0;i<n;i++)  
    {  
        if(res > ans[i])  
        {  
            res=ans[i];  
            index=i;  
        }  
    }  
    if(INF == res)  
        printf("disjoint\n");  
    else  
        printf("%d %d\n",index + 1,res);  
}  
int main()  
{  
    #ifdef LOCAL  
    freopen("input.txt","r",stdin);  
    #endif  
    while(EOF!=scanf("%d",&n) && 0!=n)  
        solve();  
    return 0;  
}  
