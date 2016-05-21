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
const int N = 100010;
const int INF = 0x3f3f3f3f;
int n, d, ans;
vector<int> G[N];
void init() {
    rep(i, n) {
        G[i].clear();
    }
}
void built() {
    int u, v;
    rep(i, n - 1) {
        scanf("%d %d", &u, &v);
        G[u].pb(v);
        G[v].pb(u);
    }
}
void dfs(int u, int fa, int dep) {
    if(dep > d) ans++;
    int m = sz(G[u]);
    for(int i = 0; i < m; i++) {
        int to = G[u][i];
        if(to != fa) {
            dfs(to, u, dep + 1);
        }
    }
}
void solve() {
    ans = 0;
    init(), built();
    dfs(0, -1, 0);
    printf("%d\n", ans);
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &d);
        solve();
    }
    return 0;
}
