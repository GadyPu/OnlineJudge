#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
using std::map;
using std::min;
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
const int N = 110;
const int INF = 0x3f3f3f3f;
int V, E;
struct edge {
    int u, v, w;
    inline bool operator<(const edge &x) const {
        return w < x.w;
    }
}G[(N * N) << 1], X[N * N];
struct Kruskal {
    int par[N], rank[N];
    inline void init() {
        rep(i, V + 1) {
            par[i] = i;
            rank[i] = 0;
        }
    }
    inline int find(int x) {
        while(x != par[x]) {
            x = par[x] = par[par[x]];
        }
        return x;
    }
    inline bool unite(int x, int y) {
        x = find(x), y = find(y);
        if(x == y) return false;
        if(rank[x] < rank[y]) {
            par[x] = y;
        } else {
            par[y] = x;
            rank[x] += rank[x] == rank[y];
        }
        return true;
    }
    inline void built() {
        int u, v, w;
        rep(i, E) {
            scanf("%d %d %d", &u, &v, &w);
            G[i] = (edge){ u, v, w };
        }
    }
    inline int kruskal_1(int &p) {
        init();
        int ans = 0;
        rep(i, E) {
            int u = G[i].u, v = G[i].v;
            if(unite(u, v)) {
                ans += G[i].w;
                X[p++] = (edge){ u, v, G[i].w };
            }
        }
        return ans;
    }
    inline int kruskal_2(int x, int y) {
        init();
        int ans = 0;
        rep(i, E) {
            int u = G[i].u, v = G[i].v;
            if(u == x && y == v) continue;
            if(unite(u, v)) {
                ans += G[i].w;
            }
        }
        return ans;
    }
    inline void solve() {
        built();
        sort(G, G + E);
        int p = 0, ans = kruskal_1(p);
        rep(i, p) {
            int ret = kruskal_2(X[i].u, X[i].v);
            int t = -1;
            for(int j = 1; j <= V; j++) {
                if(par[j] == j) t++;
            }
            if(t) continue;
            if(ret == ans) { ans = -1; break; }
        }
        if(-1 == ans) puts("Not Unique!");
        else printf("%d\n", ans);
    }
}go;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &V, &E);
        go.solve();
    }
    return 0;
}
