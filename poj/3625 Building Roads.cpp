#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<set>
using std::set;
using std::sort;
using std::pair;
using std::swap;
using std::multiset;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr, val) memset(arr, val, sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for(int i = 0; i < (int)n; i++)
#define tr(c, i) for(iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 1010;
const int INF = 0x3f3f3f3f;
typedef unsigned long long ull;
struct Node {
    int x, y;
    double w;
    Node() {}
    Node(int i, int j, double k) :x(i), y(j), w(k) {}
    inline bool operator<(const Node &t) const {
        return w < t.w;
    }
}G[(N * N) << 1];
struct P {
    double x, y;
    inline double calc(const P &t) const {
        return sqrt((x - t.x) * (x - t.x) + (y - t.y) * (y - t.y));
    }
}A[N];
struct Kruskal {
    int E, par[N], rank[N];
    inline void init() {
        E = 0;
        rep(i, N) {
            par[i] = i;
            rank[i] = 0;
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
    inline void built(int n, int m) {
        int u, v;
        for(int i = 1; i<= n; i++) scanf("%lf %lf", &A[i].x, &A[i].y);
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                G[E++] = Node(i, j, A[i].calc(A[j]));
            }
        }
        while (m--) {
            scanf("%d %d", &u, &v);
            G[E++] = Node(u, v, 0.0);
        }
    }
    inline double kruskal(int n) {
        int tot = 0;
        double ans = 0.0;
        sort(G, G + E);
        rep(i, E) {
            Node &e = G[i];
            if (unite(e.x, e.y)) {
                ans += e.w;
                if (++tot >= n - 1) return ans;
            }
        }
        return -1.0;
    }
    inline void solve(int n, int m) {
        init(), built(n, m);
        printf("%.2lf\n", kruskal(n));
    }
}go;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, m;
    while (~scanf("%d %d", &n, &m)) {
        go.solve(n, m);
    }
    return 0;
}
