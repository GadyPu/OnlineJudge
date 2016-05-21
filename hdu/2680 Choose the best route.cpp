#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<map>
using std::min;
using std::cin;
using std::cout;
using std::endl;
using std::find;
using std::sort;
using std::pair;
using std::vector;
using std::multimap;
using std::priority_queue;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr,val) memset(arr,val,sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 20010;
const int INF = 0x3f3f3f3f;
typedef unsigned long long ull;
struct P {
    int w, v;
    P(int i = 0, int j = 0) :w(i), v(j) {}
    inline bool operator<(const P &a) const {
        return w > a.w;
    }
};
struct Node { int to, w, next; };
struct Dijkstra {
    Node G[N];
    int tot, dist[N], head[N];
    inline void init() {
        tot = 0, cls(dist, 0x3f), cls(head, -1);
    }
    inline void add_edge(int u, int v, int w) {
        G[tot] = { v, w, head[u] }; head[u] = tot++;
    }
    inline void built(int m) {
        int u, v, w;
        while (m--) {
            scanf("%d %d %d", &u, &v, &w);
            add_edge(v, u, w);
        }
    }
    inline void dijkstra(int s) {
        priority_queue<P> q;
        q.push(P(0, s));
        dist[s] = 0;
        while (!q.empty()) {
            P t = q.top(); q.pop();
            int u = t.v;
            if (dist[u] < t.w) continue;
            for (int i = head[u]; ~i; i = G[i].next) {
                int &w = dist[G[i].to];
                if (w > dist[u] + G[i].w) {
                    w = dist[u] + G[i].w;
                    q.push(P(w, G[i].to));
                }
            }
        }
    }
    inline void work(int s) {
        dijkstra(s);
        int k, v, ans = INF;
        scanf("%d", &k);
        while (k--) {
            scanf("%d", &v);
            ans = min(ans, dist[v]);
        }
        printf("%d\n", ans == INF ? -1 : ans);
    }
}go;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, m, s;
    while (~scanf("%d %d %d", &n, &m, &s)) {
        go.init();
        go.built(m);
        go.work(s);
    }
    return 0;
}
