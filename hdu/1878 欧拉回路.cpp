#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
using std::map;
using std::cin;
using std::cout;
using std::endl;
using std::find;
using std::sort;
using std::pair;
using std::vector;
using std::multimap;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr,val) memset(arr,val,sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 1010;
typedef unsigned long long ull;
struct Node  { int to, next; };
struct Euler {
    Node G[N];
    bool vis[N];
    int tot, inq[N], head[N];
    inline void init() {
        tot = 0;
        cls(vis, false), cls(inq, 0), cls(head, -1);
    }
    inline void add_edge(int u, int v) {
        G[tot].to = v; G[tot].next = head[u]; head[u] = tot++;
    }
    inline void dfs(int u) {
        vis[u] = true;
        for (int i = head[u]; ~i; i = G[i].next) {
            if (!vis[G[i].to]) dfs(G[i].to);
        }
    }
    inline void work(int n, int m) {
        init();
        int u, v;
        bool f = true;
        rep(i, m) {
            scanf("%d %d", &u, &v);
            inq[u]++, inq[v]++;
            add_edge(u, v), add_edge(v, u);
        }
        rep(i, n) {
            if (inq[i + 1] & 1) { f = false; break; }
        }
        if (!f) { puts("0"); return; }
        dfs(1);
        rep(i, n) {
            if (!vis[i + 1]) { f = false; break; }
        }
        puts(f ? "1" : "0");
    }
}go;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, m;
    while (~scanf("%d", &n), n) {
        scanf("%d", &m);
        go.work(n, m);
    }
    return 0;
}
