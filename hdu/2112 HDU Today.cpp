#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<string>
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
using std::string;
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
    map<string, int> A;
    int start, end, tot, dist[210], head[N];
    inline void init() {
        tot = 0, A.clear();
        cls(head, -1), cls(dist, 0x3f);
    }
    inline void add_edge(int u, int v, int w) {
        G[tot] = { v, w, head[u] }; head[u] = tot++;
    }
    inline void built(int n) {
        char str[4][32];
        int u, v, w, k = 1;
        scanf("%s %s", str[0], str[1]);
        A[str[0]] = k++, A[str[1]] = k++;
        rep(i, n) {
            scanf("%s %s %d", str[2], str[3], &w);
            if (A.find(str[2]) == A.end()) A[str[2]] = k++;
            if (A.find(str[3]) == A.end()) A[str[3]] = k++;
            u = A[str[2]], v = A[str[3]];
            add_edge(u, v, w), add_edge(v, u, w);
        }
        start = A[str[0]], end = A[str[1]];
    }
    inline void dijkstra() {
        dist[start] = 0;
        priority_queue<P> q;
        q.push(P(0, start));
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
        printf("%d\n", dist[end] == (int)0x3f3f3f3f ? -1 : dist[end]);
    }
}go;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n;
    while (~scanf("%d", &n) && n != -1) {
        go.init();
        go.built(n);
        go.dijkstra();
    }
    return 0;
}
