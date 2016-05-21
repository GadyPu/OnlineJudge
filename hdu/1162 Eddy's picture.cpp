#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<cmath>
#include<map>
using std::map;
using std::min;
using std::find;
using std::sqrt;
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
    double x, y;
    P(double i = 0.0, double j = 0.0) :x(i), y(j) {}
    double calc(const P &t) const {
        return sqrt((x - t.x) * (x - t.x) + (y - t.y) * (y - t.y));
    }
}A[N];
struct edge { int to; double w; int next; }G[(N * N) << 1];
struct PII {
    int v;
    double w;
    PII(int i = 0, double j = 0.0) :v(i), w(j) {}
    inline bool operator<(const PII &x) const {
        return w > x.w;
    }
};
struct Prim {
    bool vis[N];
    int tot, head[N];
    double mincost[N];
    inline void init() {
        tot = 0, cls(head, -1), cls(vis, false), cls(mincost, 0x3f);
    }
    inline void add_edge(int u, int v, double w) {
        G[tot] = (edge){ v, w, head[u] }; head[u] = tot++;
    }
    inline void built(int m) {
        rep(i, m) {
            scanf("%lf %lf", &A[i].x, &A[i].y);
        }
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < m; j++) {
                if(i == j) continue;
                add_edge(i + 1, j + 1, A[i].calc(A[j]));
            }
        }
    }
    inline void prim(int s) {
        double ans = 0.0;
        priority_queue<PII> q;
        q.push(PII(s, 0.0));
        for(int i = head[s]; ~i; i = G[i].next) {
            mincost[G[i].to] = G[i].w;
            q.push(PII(G[i].to, G[i].w));
        }
        mincost[s] = 0, vis[s] = true;
        while(!q.empty()) {
            PII t = q.top(); q.pop();
            int u = t.v;
            if(vis[u]) continue;
            vis[u] = true;
            ans += t.w;
            for(int i = head[u]; ~i; i = G[i].next) {
                double &d = mincost[G[i].to];
                if(d > G[i].w && !vis[G[i].to]) {
                    d = G[i].w;
                    q.push(PII(G[i].to, d));
                }
            }
        }
        printf("%.2lf\n", ans);
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
    while(~scanf("%d", &n)) {
        go.solve(n);
    }
    return 0;
}
