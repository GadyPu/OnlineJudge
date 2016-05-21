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
const int N = 510;
const int INF = 0x3f3f3f3f;
struct SPFA {
    struct edge { int to, w, next; }G[N * 10];
    bool vis[N];
    int tot, inq[N], head[N], dist[N];
    inline void init(int n) {
        tot = 0;
        rep(i, n + 1) {
            head[i] = -1;
            inq[i] = vis[i] = 0;
            dist[i] = INF;
        }
    }
    inline void add_edge(int u, int v, int w) {
        G[tot] = (edge){ v, w, head[u] }; head[u] = tot++;
    }
    inline void built(int m, int w) {
        int u, v, x;
        while(m--) {
            scanf("%d %d %d", &u, &v, &x);
            add_edge(u, v, x), add_edge(v, u, x);
        }
        while(w--) {
            scanf("%d %d %d", &u, &v, &x);
            add_edge(u, v, -x);
        }
    }
    inline bool spfa(int n, int s = 1) {
        queue<int> q;
        q.push(s);
        dist[s] = 0, vis[s] = true;
        while(!q.empty()) {
            int u = q.front(); q.pop();
            vis[u] = false;
            for(int i = head[u]; ~i; i = G[i].next) {
                edge &e = G[i];
                if(dist[e.to] > dist[u] + e.w) {
                    dist[e.to] = dist[u] + e.w;
                    if(!vis[e.to]) {
                        vis[e.to] = true;
                        q.push(e.to);
                        inq[e.to]++;
                    }
                }
                if(inq[e.to] > n) return true;
            }
        }
        return false;
    }
    inline void solve(int n, int m, int w) {
        init(n), built(m, w);
        puts(spfa(n) ? "YES" : "NO");
    }
}go;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t, n, m, w;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d %d", &n, &m, &w);
        go.solve(n, m, w);
    }
    return 0;
}
