#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define Max_N 40
#define INF 0x3f3f3f3f
#define _min(a,b) ((a)>(b)?(b):(a))
int V,vis[Max_N], mincost[Max_N], cost[Max_N][Max_N];
void Prim()
{
    int u, res = 0;
    for (u = 0; u<V; u++)
        mincost[u] = (u == 0 ? 0 : INF);
    memset(vis, 0, sizeof(vis));
    for (;;)
    {
        int v = -1;
        for (u = 0; u < V; u++){
            if (!vis[u] && (-1 == v || mincost[u] < mincost[v])) v = u;
        }
        if (-1 == v) break;
        vis[v] = 1;
        res += mincost[v];
        for (u = 0; u<V; u++)
            mincost[u] = _min(mincost[u], cost[v][u]);
    }
    printf("%d\n", res);
}
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int i, t, k;
    char s1[2],s2[2];
    while (~scanf("%d", &V) && V){
        for (i = 0; i < V; i++){
            for (k = 0; k < V; k++)cost[i][k] = INF;
        }
        for (i = 1; i<V; i++){
            scanf("%s%d", s1, &t);
            while (t--){
                scanf("%s%d", s2, &k);
                int x = s1[0] - 'A', y = s2[0] - 'A';
                cost[x][y] = cost[y][x] = k;
            }
        }
        Prim();
    }
    return 0;
}
