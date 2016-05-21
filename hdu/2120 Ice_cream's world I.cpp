#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
using std::map;
using std::min;
using std::find;
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
const int N = 1010;
const int INF = 0x3f3f3f3f;
struct UinonFind {
    int ans, par[N], rank[N];
    inline void init(int n) {
        ans = 0;
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
    inline void unite(int x, int y) {
        x = find(x), y = find(y);
        if(x == y) { ans++; return; }
        if(rank[x] < rank[y]) {
            par[x] = y;
        } else {
            par[y] = x;
            rank[x] += rank[x] == rank[y];
        }
    }
    inline void solve(int n, int m) {
        init(n);
        int x, y;
        while(m--) {
            scanf("%d %d", &x, &y);
            unite(x, y);
        }
        printf("%d\n", ans);
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
