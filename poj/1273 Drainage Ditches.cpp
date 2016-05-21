#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
using std::min;
using std::find;
using std::sort;
using std::pair;
using std::vector;
using std::multimap;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cls(arr, val) memset(arr, val, sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for(int i = 0; i < (int)n; i++)
#define tr(c, i) for(iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 210;
const int INF = 0x3f3f3f3f;
struct Ford_Flukerson {
    struct edge { int to, cap, next, rev; }G[N << 1];
    bool vis[N];
    int tot, head[N];
    inline void init() {
        tot = 0, cls(head, -1);
    }
    inline void add_edge(int u, int v, int cap) {
        G[tot] = (edge){ v, cap, head[u], tot + 1 }; head[u] = tot++;
        G[tot] = (edge){ u,   0, head[v], tot - 1 }; head[v] = tot++;
    }
    inline void built(int m) {
        int u, v, f;
        while(m--) {
            scanf("%d %d %d", &u, &v, &f);
            add_edge(u, v, f);
        }
    }
    inline int dfs(int u, int t, int f) {
        if(u == t) return f;
        vis[u] = true;
        for(int i = head[u]; ~i; i = G[i].next) {
            edge &e = G[i];
            if(!vis[e.to] && e.cap > 0) {
                int d = dfs(e.to, t, min(e.cap, f));
                if(d > 0 ) {
                    e.cap -= d;
                    G[e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
    inline void max_flow(int n) {
        int flow = 0;
        while(true) {
            cls(vis, false);
            int f = dfs(1, n, INF);
            if(!f) break;
            flow += f;
        }
        printf("%d\n", flow);
    }
}go;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, m;
    while(~scanf("%d %d", &m, &n)) {
        go.init();
        go.built(m);
        go.max_flow(n);
    }
    return 0;
}
