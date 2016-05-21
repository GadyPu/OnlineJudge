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
const int N = 11000;
const int INF = 0x3f3f3f3f;
struct edge { int to, w, next; }G[N << 1];
int tot, head[N], dist[N];
void init() {
    tot = 0, cls(head, -1);
}
void add_edge(int u, int v, int w) {
    G[tot] = (edge){ v, w, head[u] }; head[u] = tot++;
    G[tot] = (edge){ u, w, head[v] }; head[v] = tot++;
}
int bfs(int u) {
    queue<int> q;
    q.push(u);
    cls(dist, -1);
    int id = 0, maxd = 0;
    dist[u] = 0;
    while(!q.empty()) {
        u = q.front(); q.pop();
        if(dist[u] > maxd) {
            maxd = dist[id = u];
        }
        for(int i = head[u]; ~i; i = G[i].next) {
            edge &e = G[i];
            if(-1 == dist[e.to]) {
                dist[e.to] = dist[u] + e.w;
                q.push(e.to);
            }
        }
    }
    return id;
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    init();
    int u, v, w;
    while(~scanf("%d %d %d", &u, &v, &w)) {
        add_edge(u, v, w);
    }
    printf("%d\n", dist[bfs(bfs(1))]);
    return 0;
}
