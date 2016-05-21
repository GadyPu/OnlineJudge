#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<map>
using std::min;
using std::sort;
using std::pair;
using std::swap;
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
#define rep(i, n) for(int i = 1; i <= (int)n; i++)
#define tr(c, i) for(iter(c) i = (c).begin(); i != (c).end(); ++i)
const int Max_N = 1100;
const int INF = 0x3f3f3f3f;
struct Ford_Fulkerson {
    struct edge { int to, cap, next, rev; }G[Max_N << 2];
    int  N, F, D, tot, head[Max_N];
    bool vis[Max_N], Food[Max_N][Max_N], Drink[Max_N][Max_N];
    inline void init(int n, int f, int d) {
        tot = 0;
        this->N = n, this->F = f, this->D =d;
        cls(head, -1), cls(Food, false), cls(Drink, false);
    }
    inline void add_edge(int u, int v, int cap = 1) {
        G[tot] = (edge){ v, cap, head[u], tot + 1 }; head[u] = tot++;
        G[tot] = (edge){ u,   0, head[v], tot - 1 }; head[v] = tot++;
    }
    inline void built() {
        int x, y, v;
        rep(i, N) {
            scanf("%d %d", &x, &y);
            while(x--) {
                scanf("%d", &v);
                Food[i][v] = true;
            }
            while(y--) {
                scanf("%d", &v);
                Drink[i][v] = true;
            }
        }
    }
    inline int dfs(int u, int t, int f) {
        if(u == t) return f;
        vis[u] = true;
        for(int i = head[u]; ~i; i = G[i].next) {
            edge &e = G[i];
            if(e.cap > 0 && !vis[e.to]) {
                int d = dfs(e.to, t, min(e.cap, f));
                if(d > 0) {
                    e.cap -= d;
                    G[e.rev].cap +=d;
                    return d;
                }
            }
        }
        return 0;
    }
    inline void max_flow(int s, int t) {
        int flow = 0;
        while(true) {
            cls(vis, false);
            int f = dfs(s, t, INF);
            if(!f) break;
            flow += f;
        }
        printf("%d\n", flow);
    }
    inline void solve() {
        int s = 1, t = s + F + 2 * N + D + 1;
        rep(i, F) {
            add_edge(s, s + i);
        }
        rep(i, D) {
            add_edge(s + F + 2 * N + i, t);
        }
        rep(i, N) {
            add_edge(s + F + i, s + F + N + i, 1);
            rep(j, F) {
                if(Food[i][j]) add_edge(s + j, s + F + i);
            }
            rep(j, D) {
                if(Drink[i][j]) add_edge(s + F + N + i, s + F + 2 * N + j);
            }
        }
        max_flow(s, t);
    }
}go;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, f, d;
    while(~scanf("%d %d %d", &n, &f, &d)) {
        go.init(n ,f ,d);
        go.built();
        go.solve();
    }
    return 0;
}
