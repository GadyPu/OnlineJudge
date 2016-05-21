#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
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
const int N = 11000;
typedef unsigned long long ull;
struct P {
    int w, v;
    P(int i = 0, int j = 0) :w(i), v(j) {}
    inline bool operator<(const P &a) const {
        return w > a.w;
    }
};
struct Node { int to, w, next; };
int n, m;
struct Dijkstra {
    Node G[N];
    int tot, dist[N], head[N];
    inline void init() {
        tot = 0;
        cls(head, -1), cls(dist, 0x3f);
    }
    inline void add_edge(int u, int v, int w) {
        G[tot] = { v, w, head[u] }; head[u] = tot++;
    }
    inline void built(int m) {
        int u, v, w;
        rep(i, m) {
            scanf("%d %d %d", &u, &v, &w);
            add_edge(u, v, w), add_edge(v, u, w);
        }
    }
    inline void dijkstra(int s) {
        dist[s] = 0;
        priority_queue<P> q;
        q.push(P(0, s));
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
        printf("%d\n", dist[n]);
    }
}go;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    while (~scanf("%d %d", &n, &m), n + m) {
        go.init();
        go.built(m);
        go.dijkstra(1);
    }
    return 0;
}
