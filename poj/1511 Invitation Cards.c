#include<stdio.h>  
#include<string.h>  
#include<stdlib.h>  
#define Max_N 1000020  
#define INF 0x3f3f3f3f  
typedef long long ll;  
typedef struct _node{  
    int to, cost;  
}edge;  
edge G1[Max_N], G2[Max_N];  
int V, E, sz1, sz2, Queue[Max_N << 2], vis[Max_N], dist[Max_N], node1[Max_N], node2[Max_N], next1[Max_N], next2[Max_N];  
void built(int s, int to, int cost){  
    G1[sz1] = (edge){ to, cost };  
    next1[sz1] = node1[s];  
    node1[s] = sz1++;  
    G2[sz2] = (edge){ s, cost };  
    next2[sz2] = node2[to];  
    node2[to] = sz2++;  
}  
void spfa(int s, edge *G, int *node, int *next){  
    int u, front = 0, rear = 0;  
    for (u = 1; u <= V; u++) dist[u] = (u == s ? 0 : INF);  
    Queue[rear++] = s;  
    memset(vis, 0, sizeof(vis));  
    while (front < rear){  
        int v = Queue[front++];  
        vis[v] = 0;  
        for (u = node[v]; u != -1; u = next[u]){  
            if (dist[G[u].to] > dist[v] + G[u].cost){  
                dist[G[u].to] = dist[v] + G[u].cost;  
                if (!vis[G[u].to]){  
                    vis[G[u].to] = 1;  
                    Queue[rear++] = G[u].to;  
                }  
            }  
        }  
    }  
}  
int main(){  
#ifdef LOCAL  
    freopen("in.txt", "r", stdin);  
    freopen("out.txt", "w+", stdout);  
#endif  
    int i, k, t;  
    scanf("%d", &t);  
    while (t--){  
        sz1 = 0, sz2 = 0;  
        scanf("%d %d", &V, &E);  
        memset(node1, -1, sizeof(node1));  
        memset(node2, -1, sizeof(node2));  
        k = E;  
        while (k--){  
            int a, b, c;  
            scanf("%d %d %d", &a, &b, &c);  
            built(a, b, c);  
        }  
        ll res = 0;  
        spfa(1, G1, node1, next1);  
        for (i = 1; i <= V; i++) res += dist[i];  
        spfa(1, G2, node2, next2);  
        for (i = V; i > 0; i--) res += dist[i];  
        printf("%lld\n", res);  
    }  
    return 0;  
}  
