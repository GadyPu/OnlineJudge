#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<set>
using std::set;
using std::sort;
using std::pair;
using std::swap;
using std::multiset;
using std::priority_queue;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr, val) memset(arr, val, sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for(int i = 0; i < (int)n; i++)
#define tr(c, i) for(iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 200010;
const int INF = 0x3f3f3f3f;
typedef unsigned long long ull;
struct edge {
    int u, v, w;
    inline bool operator<(const edge &x) const {
        return w < x.w;
    }
}G[N];
struct Kruskal {
    int E, sum, par[N], rank[N];
    inline void init(int n) {
        E = sum = 0;
        rep(i, n + 1) {
            par[i] = i, rank[i] = 0;
        }
    }
    inline void built(int m) {
        int u, v, w;
        while (m--) {
            scanf("%d %d %d", &u, &v, &w);
            G[E++] = { u, v, w }, sum += w;
        }
    }
    inline int find(int x) {
        while (x != par[x]) {
            x = par[x] = par[par[x]];
        }
        return x;
    }
    inline bool unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (rank[x] < rank[y]) {
            par[x] = y;
        } else {
            par[y] = x;
            rank[x] += rank[x] == rank[y];
        }
        return true;
    }
    inline int kruskal() {
        int ans = 0;
        sort(G, G + E);
        rep(i, E) {
            edge &e = G[i];
            if (unite(e.u, e.v)) {
                ans += e.w;
            }
        }
        return ans;
    }
    inline void solve(int n, int m) {
        init(n), built(m);
        printf("%d\n", sum - kruskal());
    }
}go;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, m;
    while (~scanf("%d %d", &n, &m), n + m) {
        go.solve(n, m);
    }
    return 0;
}
