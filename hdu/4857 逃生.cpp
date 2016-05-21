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
using std::priority_queue;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cls(arr, val) memset(arr, val, sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for(int i = 0; i < (int)n; i++)
#define tr(c, i) for(iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 30010;
const int INF = 0x3f3f3f3f;
struct cmp {
    inline bool operator()(int &a, int &b) {
        return a < b;
    }
};
struct TopSort {
    struct edge { int to, next; }G[N * 8];
    int tot, inq[N], head[N], topNum[N];
    inline void init(int n) {
        tot = 0;
        rep(i, n + 1) {
            head[i] = -1;
            inq[i] = topNum[i] = 0;
        }
    }
    inline void add_edge(int u, int v) {
        G[tot] = (edge){ v, head[u] }; head[u] = tot++;
        G[tot] = (edge){ u, head[v] }; head[v] = tot++;
    }
    inline void built(int m) {
        int u, v;
        while(m--) {
            scanf("%d %d", &u, &v);
            inq[u]++, add_edge(v, u);
        }
    }
    inline void bfs(int n) {
        int k = 0;
        priority_queue<int, vector<int>, cmp> q;
        rep(i, n) {
            if(!inq[i + 1]) {
                q.push(i + 1);
            }
        }
        while(!q.empty()) {
            int u = q.top(); q.pop();
            topNum[k++] = u;
            for(int i = head[u]; ~i; i = G[i].next) {
                edge &e = G[i];
                if(--inq[e.to] == 0) {
                    q.push(e.to);
                }
            }
        }
        for(int i = k - 1; ~i; i--) printf("%d%c", topNum[i], i > 0 ? ' ' : '\n');
    }
    inline void solve(int n, int m) {
        init(n), built(m), bfs(n);
    }
}go;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t, n, m;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        go.solve(n, m);
    }
    return 0;
}
