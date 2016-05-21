#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<cmath>
#include<set>
using std::set;
using std::pair;
using std::swap;
using std::multiset;
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
typedef unsigned long long ull;
struct P {
    float x, y;
    P(float i = 0.0, float j = 0.0) :x(i), y(j) {}
    inline float calc(const P &k) const {
        return sqrt((x - k.x) * (x - k.x) + (y - k.y) * (y - k.y));
    }
}A[N];
struct PDI {
    int v;
    float s;
    PDI(int i = 0, float j = 0.0) :v(i), s(j) {}
    inline bool operator<(const PDI &k) const {
        return s > k.s;
    }
};
struct Prim {
    bool vis[N];
    int tot, head[N];
    float mincost[N];
    struct edge { int to; float w; int next; }G[(N * N) << 1];
    inline void init(int n) {
        tot = 0;
        rep(i, n + 1) {
            head[i] = -1;
            vis[i] = false;
            mincost[i] = INF;
        }
    }
    inline void add_edge(int u, int v, float w) {
        G[tot] = (edge){ v, w, head[u] }; head[u] = tot++;
    }
    inline void built(int n) {
        rep(i, n) scanf("%f %f", &A[i].x, &A[i].y);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                add_edge(i + 1, j + 1, A[i].calc(A[j]));
            }
        }
    }
    inline void prim(int s = 1) {
        float ans = 0.0;
        priority_queue<PDI> q;
        q.push(PDI(s));
        for (int i = head[s]; ~i; i = G[i].next) {
            edge &e = G[i];
            q.push(PDI(e.to, mincost[e.to] = e.w));
        }
        vis[s] = true;
        while (!q.empty()) {
            PDI t = q.top(); q.pop();
            int u = t.v;
            if (vis[u]) continue;
            vis[u] = true;
            ans += mincost[u];
            for (int i = head[u]; ~i; i = G[i].next) {
                edge &e = G[i];
                if (mincost[e.to] > e.w && !vis[e.to]) {
                    q.push(PDI(e.to, mincost[e.to] = e.w));
                }
            }
        }
        printf("%.2f\n", ans);
    }
    inline void solve(int n) {
        init(n), built(n), prim();
    }
}go;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n;
    while (~scanf("%d", &n)) {
        go.solve(n);
    }
    return 0;
}
