#include<stdio.h>  
#include<string.h>  
#include<stdlib.h>  
#define Max_N 3000  
#define INF 0x3f3f3f3f  
#define _min(a,b) ((a)>(b)?(b):(a))  
int V,E,map[Max_N][Max_N], dist[Max_N],vis[Max_N];  
void dijkstra(){  
    int u;  
    for (u = 0; u < V; u++) dist[u] = (u == V - 1 ? 0 : INF);  
    memset(vis, 0, sizeof(vis));  
    for (;;){  
        int v = -1;  
        for (u = 0; u < V;u++)  
        if (!vis[u] && (-1 == v || dist[v]>dist[u])) v = u;  
        if (-1 == v) break;  
        vis[v] = 1;  
        for (u = 0; u < V; u++)  
            dist[u] = _min(dist[u], dist[v] + map[v][u]);  
    }  
    printf("%d\n", dist[0]);  
}  
int main(){  
#ifdef LOCAL  
    freopen("in.txt", "r", stdin);  
    freopen("out.txt", "w+", stdout);  
#endif  
    while (~scanf("%d %d", &E, &V)){  
        int  a, b, c, k = 0, t = E;  
        for (a = 0; a < V; a++){  
            for (b = 0; b < V; b++) map[a][b] = INF;  
        }  
        while (t--){  
            scanf("%d %d %d", &a, &b, &c);  
            --a, --b;  
            map[a][b] = map[b][a] = _min(c, map[a][b]);  
        }  
        dijkstra();  
    }  
    return 0;  
}  
