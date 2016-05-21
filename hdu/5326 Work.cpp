#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<set>
using std::set;
using std::pair;
using std::swap;
using std::queue;
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
const int N = 110;
const int INF = 0x3f3f3f3f;
struct edge { int to, next; }G[N << 1];
bool inq[N];
int tot, size[N], head[N];
void init(int n) {
    tot = 0;
    rep(i, n + 1) {
        head[i] = -1;
        inq[i] = size[i] = false;
    }
}
inline void add_edge(int u, int v) {
    G[tot].to = v, G[tot].next = head[u], head[u] = tot++;
}
void dfs(int u) {
    size[u] = 1;
    for (int i = head[u]; ~i; i = G[i].next) {
        edge &e = G[i];
        dfs(e.to);
        size[u] += size[e.to];
    }
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, k, u, v;
    while (~scanf("%d %d", &n, &k)) {
        init(n);
        rep(i, n - 1) {
            scanf("%d %d", &u, &v);
            add_edge(u, v);
            inq[v] = true;
        }
        for(int i = 1; i <= n; i++) {
            if (!inq[i]) {
                u = i;
                break;
            }
        }
        int sum = 0;
        dfs(u);
        for (int i = 1; i <= n; i++) {
            if (size[i] == k + 1) sum++;
        }
        printf("%d\n", sum);
    }
    return 0;
}
