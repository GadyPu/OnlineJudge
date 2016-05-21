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
const int N = 2010;
const int INF = 0x3f3f3f3f;
struct TopSort {
    struct edge { int to, next; }G[N * N];
    int tot, inq[N], head[N];
    inline void init() {
        tot = 0, cls(inq, 0), cls(head, -1);
    }
    inline void add_edge(int u, int v) {
        G[tot].to = v; G[tot].next = head[u]; head[u] = tot++;
    }
    void built(int n) {
        char buf[N];
        rep(i, n) {
            scanf("%s", buf);
            rep(j, n) {
                int f = buf[j] - '0';
                if(!f) continue;
                inq[j + 1]++;
                add_edge(i + 1, j + 1);
            }
        }
    }
    inline bool bfs(int n) {
        int topNum = 0;
        queue<int> q;
        rep(i, n) {
            if(!inq[i + 1]) {
                q.push(i + 1);
            }
        }
        while(!q.empty()) {
            int u = q.front(); q.pop();
            topNum++;
            for(int i = head[u]; ~i; i = G[i].next) {
                if(--inq[G[i].to] == 0) {
                    q.push(G[i].to);
                }
            }
        }
        return topNum == n;
    }
    inline void solve(int n) {
        static int k = 1;
        init(), built(n);
        printf("Case #%d: %s\n", k++, !bfs(n) ? "Yes" : "No");
    }
}go;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t, n;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        go.solve(n);
    }
    return 0;
}
