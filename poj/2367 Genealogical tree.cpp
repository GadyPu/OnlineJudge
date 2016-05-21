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
using std::find;
using std::pair;
using std::queue;
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
struct TopSort {
    struct edge { int to, next; }G[(N * N) << 1];
    int tot, inq[N], head[N], topNum[N];
    inline void init() {
        tot = 0, cls(inq, 0), cls(head, -1);
    }
    inline void add_edge(int u, int v) {
        G[tot].to = v; G[tot].next = head[u]; head[u] = tot++;
    }
    inline void built(int n) {
        int v;
        for(int i = 1; i <= n; i++) {
            while(~scanf("%d", &v), v) {
                inq[v]++, add_edge(i, v);
            }
        }
    }
    inline void bfs(int n) {
        int k = 0;
        queue<int> q;
        rep(i, n) {
            if(!inq[i + 1]) {
                q.push(i + 1);
            }
        }
        while(!q.empty()) {
            int u = q.front(); q.pop();
            topNum[k++] = u;
            for(int i = head[u]; ~i; i = G[i].next) {
                if(--inq[G[i].to] == 0) {
                    q.push(G[i].to);
                }
            }
        }
        rep(i, k) printf("%d%c", topNum[i], i < k - 1 ? ' ' : '\n');
    }
    inline void solve(int n) {
        init(), built(n), bfs(n);
    }
}go;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n;
    while(~scanf("%d", &n)) {
        go.solve(n);
    }
    return 0;
}
