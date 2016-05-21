#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<map>
using std::cin;
using std::cout;
using std::endl;
using std::find;
using std::sort;
using std::map;
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
const int N = 510;
typedef unsigned long long ull;
struct Node { int to, next; };
struct cmp {
    inline bool operator()(int &a, int &b) const {
        return a > b;
    }
};
struct TopSort {
    Node G[N];
    int tot, inq[N], head[N], topNum[N];
    inline void init() {
        tot = 0;
        cls(inq, 0), cls(head, -1), cls(topNum, 0);
    }
    inline void add_edge(int u, int v) {
        G[tot].to = v; G[tot].next = head[u]; head[u] = tot++;
    }
    inline void built(int m) {
        int u, v;
        rep(i, m) {
            scanf("%d %d", &u, &v);
            --u, --v;
            inq[v]++;
            add_edge(u, v);
        }
    }
    inline void bfs(int n) {
        int k = 0;
        priority_queue<int, vector<int>, cmp> q;
        rep(i, n) { if (!inq[i]) q.push(i); }
        while (!q.empty()) {
            int u = q.top(); q.pop();
            topNum[k++] = u + 1;
            for (int i = head[u]; ~i; i = G[i].next) {
                if (--inq[G[i].to] == 0) q.push(G[i].to);
            }
        }
        rep(i, n) printf("%d%c", topNum[i], i < n - 1 ? ' ' : '\n');
    }
}work;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, m;
    while (~scanf("%d %d", &n, &m)) {
        work.init();
        work.built(m);
        work.bfs(n);
    }
    return 0;
}
