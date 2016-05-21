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
const int N = 10010;
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
    int tot, head[N], dist[N];
    inline void init() {
        tot = 0, cls(head, -1);
    }
    inline void add_edge(int u, int v, int w) {
        G[tot] = { v, w, head[u] }; head[u] = tot++;
    }
    inline void built(int n) {
        int u, v, w;
        rep(i, n) {
            scanf("%d %d %d", &u, &v, &w);
            add_edge(u, v, w), add_edge(v, u, w);
        }
    }
    inline void dijkstra(vector<int> &st) {
        cls(dist, 0x3f);
        priority_queue<P> q;
        rep(i, sz(st)) {
            q.push(P(0, st[i]));
            dist[st[i]] = 0;
        }
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
    inline void work(int s, int d) {
        int v, ans = 0x3f3f3f3f;
        vector<int> A, B;
        while (s--) { scanf("%d", &v); A.push_back(v); }
        while (d--) { scanf("%d", &v); B.push_back(v); }
        dijkstra(A);
        rep(i, sz(B)) ans = min(ans, dist[B[i]]);
        printf("%d\n", ans);
    }
}go;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, s, d;
    while (~scanf("%d %d %d", &n, &s, &d)) {
        go.init();
        go.built(n);
        go.work(s, d);
    }
    return 0;
}
