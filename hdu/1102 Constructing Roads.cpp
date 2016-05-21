#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<map>
using std::map;
using std::min;
using std::find;
using std::pair;
using std::vector;
using std::multimap;
using std::priority_queue;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cls(arr, val) memset(arr, val, sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for(int i = 0; i < (int)n; i++)
#define tr(c, i) for(iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 110;
const int INF = 0x3f3f3f3f;
struct P {
    int w, v;
    P(int i = 0, int j = 0) :w(i), v(j) {}
    inline bool operator<(const P &x) const {
        return w > x.w;
    }
};
struct Prim {
    struct edge { int to, w, next; }G[(N * N) << 1];
    bool vis[N];
    int tot, head[N], mincost[N];
    inline void init() {
        tot = 0, cls(vis, false), cls(head, -1), cls(mincost, 0x3f);
    }
    inline void add_edge(int u, int v, int w) {
        G[tot] = (edge){ v, w, head[u] }; head[u] = tot++;
    }
    inline void fix_up(int u, int v) {
        for(int i = head[u]; ~i; i = G[i].next) {
            if(G[i].to == v) {
                G[i].w = 0;
                return;
            }
        }
    }
    inline void built(int V) {
        int u, v, q;
        rep(i, V) {
            rep(j, V) {
                scanf("%d", &v);
                if(i == j) continue;
                add_edge(i + 1, j + 1, v);
            }
        }
        scanf("%d", &q);
        while(q--) {
            scanf("%d %d", &u, &v);
            fix_up(u, v), fix_up(v, u);
        }
    }
    inline void prim(int s) {
        int ans = 0;
        priority_queue<P> q;
        q.push(P(0, s));
        for(int i = head[s]; ~i; i = G[i].next) {
            mincost[G[i].to] = G[i].w;
            q.push(P(G[i].w, G[i].to));
        }
        vis[s] = true;
        while(!q.empty()) {
            P t = q.top(); q.pop();
            int u = t.v;
            if(vis[u]) continue;
            vis[u] = true;
            ans += mincost[u];
            for(int i = head[u]; ~i; i = G[i].next) {
                int &d = mincost[G[i].to];
                if(d > G[i].w && !vis[G[i].to]) {
                    d = G[i].w;
                    q.push(P(d, G[i].to));
                }
            }
        }
        printf("%d\n", ans);
    }
    inline void solve(int V) {
        init(), built(V), prim(1);
    }
}go;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int V;
    while(~scanf("%d", &V)) {
        go.solve(V);
    }
    return 0;
}
