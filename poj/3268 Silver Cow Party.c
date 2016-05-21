#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#define Max_N 100010  
#define INF 0x3f3f3f3f  
#define _max(a,b) ((a)>(b)?(a):(b))  
typedef struct node_t{ int v,e; }edge;  
edge G[Max_N];  
int sz,V,E,D,ret[Max_N],Queue[Max_N<<2],dist[Max_N],vis[Max_N],node[Max_N],next[Max_N];  
void add(int s,int v,int e){  
    G[sz].e=e;  
    G[sz].v=v;  
    next[sz]=node[s];  
    node[s]=sz++;  
}  
void spfa(int s){  
    int i,p,front=0,rear=0;  
    for(i=1;i<=V;i++) dist[i]=(i==s?0:INF);  
    memset(vis,0,sizeof(vis));  
    Queue[rear++]=s;  
    while(front<rear){  
        int v=Queue[front++];  
        vis[v]=0;  
        for(p=node[v];p!=-1;p=next[p]){  
            if(dist[G[p].v] > dist[v] + G[p].e){  
                dist[G[p].v]=dist[v] + G[p].e;  
                if(!vis[G[p].v]){  
                    vis[G[p].v]=1;  
                    Queue[rear++]=G[p].v;  
                }  
            }  
        }  
    }  
}  
int main(){  
    int i,a,b,c,t,ans;  
    while(~scanf("%d %d %d",&V,&E,&D)){  
        ans=0,sz=0,t=E;  
        memset(node,-1,sizeof(node));  
        memset(next,0,sizeof(next));  
        while(t--){  
            scanf("%d %d %d",&a,&b,&c);  
            add(a,b,c);  
        }  
        for(i=1;i<=V;i++){  
            spfa(i);  
            ret[i]=dist[D];  
        }  
        spfa(D);  
        for(i=1;i<=V;i++) ret[i]+=dist[i];  
        for(i=1;i<=V;i++) ans=_max(ans,ret[i]);  
        printf("%d\n",ans);  
    }  
    return 0;  
}  
