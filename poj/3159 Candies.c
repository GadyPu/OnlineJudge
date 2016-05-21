#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#define Max_N 200000  
#define INF 0x3f3f3f3f  
typedef struct info{int dist,vertex;}pair;  
typedef struct pri_heap  
{  
    pair tp[Max_N];  
    int nSize;  
}Heap;  
Heap que;  
int N,M,vis[Max_N],dist[Max_N],first[Max_N],u[Max_N],v[Max_N],w[Max_N],next[Max_N];  
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
void dijkstra()  
{  
    int i;  
    Init();  
    memset(vis,0,sizeof(vis));  
    for(i=0;i<N;i++) dist[i]=(i==0?0:INF);  
    push(0,0);  
    while(!empty())  
    {  
        pair pii=pop();  
        int x=pii.vertex;  
        if(vis[x]) continue;  
        vis[x]=1;  
        for(i=first[x];-1!=i;i=next[i])  
        {  
            if(dist[v[i]] > dist[x] + w[i])  
            {  
                dist[v[i]] = dist[x] + w[i];  
                push(dist[v[i]],v[i]);  
            }  
        }  
    }  
    printf("%d\n",dist[N-1]);  
}  
int main()  
{  
    #ifdef LOCAL  
    freopen("input.txt","r",stdin);  
    #endif  
    int e;  
    while(EOF!=scanf("%d %d",&N,&M))  
    {  
        memset(first,-1,sizeof(first));  
        for(e=0;e<M;e++)  
        {  
            scanf("%d %d %d",&u[e],&v[e],&w[e]);  
            --u[e],--v[e];  
            next[e]=first[u[e]];  
            first[u[e]]=e;  
        }  
        dijkstra();  
    }  
    return 0;  
}  
