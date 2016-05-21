#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<set>
using std::set;
using std::pair;
using std::swap;
using std::queue;
using std::multiset;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr, val) memset(arr, val, sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for(int i = 0; i < (int)n; i++)
#define tr(c, i) for(iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 5010;
const int INF = 0x3f3f3f3f;
struct Node {
    int x, y, s;
    Node(int i = 0, int j = 0, int k = 0) :x(i), y(j), s(k) {}
}P[N / 10];
char G[N][N];
bool vis[N][N];
int H, W, tot, Sx, Sy, cost;
const int dx[] = { 0, 0, -1, 1 }, dy[] = { -1, 1, 0, 0 };
int bfs() {
    queue<Node> q;
    q.push(Node(Sx, Sy));
    while (!q.empty()) {
        Node t = q.front(); q.pop();
        rep(i, 4) {
            int x = dx[i] + t.x, y = dy[i] + t.y;
            if (x < 0 || x >= H || y < 0 || y >= W) continue;
            if (vis[x][y] || G[x][y] == '#') continue;
            vis[x][y] = true;
            if (G[x][y] == 'C') return t.s;
            if (G[x][y] == '*') q.push(Node(x, y, t.s + 1));
            if (G[x][y] == 'P') {
                rep(i, tot) {
                    Node &k = P[i];
                    q.push(Node(k.x, k.y, t.s));
                    vis[k.x][k.y] = true;
                }
            }
        }
    }
    return -1;
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    while (~scanf("%d %d %d", &H, &W, &cost)) {
        tot = 0;
        rep(i, H) {
            scanf("%s", G[i]);
            rep(j, W) {
                vis[i][j] = false;
                if (G[i][j] == 'Y') Sx = i, Sy = j;
                if (G[i][j] == 'P') P[tot++] = Node(i, j);
            }
        }
        int ret = bfs();
        if (-1 == ret) puts("Damn teoy!");
        else printf("%d\n", ret * cost);
    }
    return 0;
}
