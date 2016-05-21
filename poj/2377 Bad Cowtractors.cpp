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
const int N = 1100;
const int INF = 0x3f3f3f3f;
struct Kruskal {
    struct edge {
        int u, v, w;
        inline bool operator<(const edge &x) const {
            return w > x.w;
        }
    }G[N * 20];
    int E, par[N], rank[N];
    inline void init(int n) {
        E = 0;
        rep(i, n + 1) {
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
    inline void built(int m) {
        int u, v, w;
        while(m--) {
            scanf("%d %d %d", &u, &v, &w);
            G[E++] = (edge){ u, v, w };
        }
        sort(G, G + E);
    }
    inline void kruskal(int n) {
        bool f = false;
        int ans = 0, cnt = 0;;
        rep(i, E) {
            int u = G[i].u, v = G[i].v;
            if(unite(u, v)) {
                ans += G[i].w;
                if(++cnt >= n - 1) { f = true; break; }
            }
        }
        printf("%d\n", f ? ans : -1);
    }
    inline void solve(int n, int m) {
        init(n), built(m), kruskal(n);
    }
}go;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, m;
    while(~scanf("%d %d", &n, &m)) {
        go.solve(n, m);
    }
    return 0;
}
