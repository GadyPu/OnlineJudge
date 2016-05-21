/****************************************   Prim   ****************************************/
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#define Max_N 100 + 2  
#define INF 0x3f3f3f3f  
#define min(a,b) ((a)>(b)?(b):(a))  
int V,mincost[Max_N],vis[Max_N],cost[Max_N][Max_N];  
int Prim(int s)  
{  
    int u,res=0;  
    for(u=0;u<V;u++)  
        mincost[u] = (u == s ? 0 : INF);  
    memset(vis,0,sizeof(vis));  
    for(;;)  
    {  
        int v=-1;  
        for(u=0;u<V;u++)  
            if(!vis[u] && (-1 == v || mincost[u] < mincost[v])) v=u;  
        if(-1 == v) break;  
        vis[v]=1;  
        res+=mincost[v];  
        for(u=0;u<V;u++)  
            mincost[u] = min(mincost[u],cost[v][u]);  
    }  
    return res;  
}  
int main()  
{  
    #ifdef LOCAL  
    freopen("input.txt","r",stdin);  
    #endif  
    int i,j;  
    while(EOF !=scanf("%d",&V))  
    {  
        memset(cost,0,sizeof(cost));  
        for(i=0;i<V;i++)  
        {  
            for(j=0;j<V;j++)  
                scanf("%d",&cost[i][j]);  
        }  
        printf("%d\n",Prim(0));  
    }  
    return 0;  
}  
/****************************************  kruskal   ****************************************/
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#define Max_N 11000  
typedef struct eg{int from,to,cost;}edge;  
edge es[Max_N];  
int V=0,E=0,par[Max_N],rank[Max_N];  
void init(int n)  
{  
    int i;  
    for(i=0;i<n;i++)  
    {  
        par[i]=i;  
        rank[i]=0;  
    }  
}  
int find(int x)  
{  
    if(x == par[x])  
        return x;  
    else  
        return par[x] = find(par[x]);  
}  
void unite(int x,int y)  
{  
    x=find(x),y=find(y);  
    if(x == y) return ;  
    if(rank[x] < rank[y]) {  
        par[x]=y;  
    } else {  
        par[y]=x;  
        if(rank[x] == rank[y]) rank[x]++;  
    }  
}  
int same(int x,int y)  
{  
    return find(x) == find(y);  
}  
int cmp(const void *a,const void *b)  
{  
    edge *aa=(edge *)a,*bb=(edge *)b;  
    return aa->cost - bb->cost;  
}  
int kruskal()  
{  
    init(V);  
    qsort(es,E,sizeof(es[0]),cmp);  
    int i,res=0;  
    for(i=0;i<E;i++)  
    {  
        edge e=es[i];  
        if(!same(e.from,e.to))  
        {  
            unite(e.from,e.to);  
            res+=e.cost;  
        }  
    }  
    return res;  
}  
int main()  
{  
    #ifdef LOCAL  
    freopen("input.txt","r",stdin);  
    #endif  
    while(EOF!=scanf("%d",&V))  
    {  
        int i,j;  
        E=0;  
        for(i=0;i<V;i++)  
        {  
            for(j=0;j<V;j++)  
            {  
                es[E].from=i,es[E].to=j;  
                scanf("%d",&es[E++].cost);  
            }  
        }  
        printf("%d\n",kruskal());  
    }  
    return 0;  
}  
