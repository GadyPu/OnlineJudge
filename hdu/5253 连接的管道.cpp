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
using std::sort;
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
const int N = 1100;
const int INF = 0x3f3f3f3f;
struct edge {
    int u, v, w;
    inline bool operator<(const edge &e) const {
        return w < e.w;
    }
}G[(N * N) << 1];
int H, W, E, X[N][N], par[N * N], rank[N * N];
namespace work {
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
    inline int kruskal() {
        sort(G, G + E);
        int res = 0;
        rep(i, E) {
            edge &e = G[i];
            if(unite(e.u, e.v)) {
                res += e.w;
            }
        }
        return res;
    }
    inline void init() {
        E = 0;
        rep(i, H) {
            rep(j, W) {
                scanf("%d", &X[i][j]);
                int v = i * W + j;
                par[v] = v, rank[v] = 0;
                if(i) {
                    G[E++] = (edge){ v, v - W, abs(X[i][j] - X[i - 1][j]) };
                }
                if(j) {
                    G[E++] = (edge){ v, v - 1, abs(X[i][j] - X[i][j - 1]) };
                }
            }
        }
    }
};
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t, v, k = 1;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &H, &W);
        work::init();
        v = work::kruskal();
        printf("Case #%d:\n%d\n", k++, v);
    }
    return 0;
}
