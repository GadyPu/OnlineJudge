#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<map>
using std::min;
using std::find;
using std::sort;
using std::pair;
using std::queue;
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
const int N = 1100;
const int INF = 0x3f3f3f3f;
struct Dinic {
    struct edge { int to, cap, next, rev; }G[N << 2];
    int s, t, tot, level[N], ite[N], head[N];
    inline void init() {
        tot = 0, cls(head, -1);
    }
    inline void add_edge(int u, int v, int cap) {
        G[tot] = (edge){ v, cap, head[u], tot + 1 }; head[u] = tot++;
        G[tot] = (edge){ u,   0, head[v], tot - 1 }; head[v] = tot++;
    }
    inline void built(int n, int m) {
        int u, v, f;
        s = 1, t = n;
        while(m--) {
            scanf("%d %d %d", &u, &v, &f);
            add_edge(u, v, f);
        }
    }
    inline void bfs(int s) {
        cls(level, -1);
        queue<int> q;
        q.push(s);
        level[s] = 0;
        while(!q.empty()) {
            int u = q.front(); q.pop();
            for(int i = head[u]; ~i; i = G[i].next) {
                edge &e = G[i];
                if(e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
    }
    inline int dfs(int u, int t, int f) {
        if(u == t) return f;
        for(int &i = ite[u]; ~i; i = G[i].next) {
            edge &e = G[i];
            if(e.cap > 0 && level[u] < level[e.to]) {
                int d = dfs(e.to, t, min(e.cap, f));
                if(d > 0) {
                    e.cap -= d;
                    G[e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
    inline int max_flow() {
        int flow = 0;
        while(true) {
            bfs(s);
            if(level[t] < 0) break;
            int f;
            rep(i, t) ite[i] = head[i];
            while((f = dfs(s, t, INF)) > 0) {
                flow += f;
            }
        }
        return flow;
    }
    inline void solve(int n, int m) {
        static int k = 1;
        init(), built(n, m);
        printf("Case %d: %d\n", k++, max_flow());
    }
}go;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t, n, m;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        go.solve(n, m);
    }
    return 0;
}
