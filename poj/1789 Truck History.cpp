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
const int N = 2100;
const int INF = 0x3f3f3f3f;
struct P {
    int w, v;
    P(int i = 0, int j = 0) :w(i), v(j) {}
    inline bool operator<(const P &x) const {
        return w > x.w;
    }
};
struct Prim {
    typedef char State[8];
    struct edge { int to, w, next; }G[N * N];
    State st[N];
    bool vis[N];
    int tot, head[N], mincost[N];
    inline void init() {
        tot = 0, cls(vis, false), cls(head, -1), cls(mincost, 0x3f);
    }
    inline void add_edge(int u, int v, int w) {
        G[tot] = (edge){ v, w, head[u] }; head[u] = tot++;
    }
    inline int calc(int i, int j) {
        int res = 0;
        rep(k, 7) {
            if(st[i][k] != st[j][k]) res++;
        }
        return res;
    }
    inline void built(int n) {
        rep(i, n) scanf("%s", st[i]);
        rep(i, n) {
            rep(j, n) {
                int ret = calc(i, j);
                if(i == j) continue;
                add_edge(i + 1, j + 1, ret);
            }
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
        mincost[s] = 0, vis[s] = true;
        while(!q.empty()) {
            P t = q.top(); q.pop();
            int u = t.v;
            if(vis[u]) continue;
            vis[u] = true;
            ans += t.w;
            for(int i = head[u]; ~i; i = G[i].next) {
                int &d = mincost[G[i].to];
                if(d > G[i].w && !vis[G[i].to]) {
                    d = G[i].w;
                    q.push(P(G[i].w, G[i].to));
                }
            }
        }
        printf("The highest possible quality is 1/%d.\n", ans);
    }
    inline void solve(int n) {
        init(), built(n), prim(1);
    }
}go;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n;
    while(~scanf("%d", &n), n) {
        go.solve(n);
    }
    return 0;
}
