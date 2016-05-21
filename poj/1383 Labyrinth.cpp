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
using std::make_pair;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cls(arr, val) memset(arr, val, sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for(int i = 0; i < (int)n; i++)
#define tr(c, i) for(iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 1010;
const int INF = 0x3f3f3f3f;
struct P {
    int x, y, s;
    P(int i = 0, int j = 0, int k = 0) :x(i), y(j), s(k) {}
};
int H, W;
char G[N][N];
bool vis[N][N];
const int dx[] = { 0, 0, -1, 1}, dy[] = { -1, 1, 0, 0};
 P bfs(int sx, int sy) {
    P res;
    queue<P> q;
    q.push(P(sx, sy));
    cls(vis, false);
    vis[sx][sy] = true;
    while(!q.empty()) {
        P t = q.front(); q.pop();
        if(t.s > res.s) {
            res = P(t.x, t.y, t.s);
        }
        rep(i, 4) {
            int x = dx[i] + t.x, y = dy[i] + t.y;
            if(x < 0 || x >= H || y < 0 || y >= W) continue;
            if(vis[x][y] || '#' == G[x][y]) continue;
            vis[x][y] = true;
            q.push(P(x, y, t.s + 1));
        }
    }
    return res;
}
void solve() {
    int sx, sy;
    rep(i, H) {
        scanf("%s", G[i]);
        rep(j, W) {
            if(G[i][j] == '.') sx = i, sy = j;
        }
    }
    P res = bfs(sx, sy);
    res = bfs(res.x, res.y);
    printf("Maximum rope length is %d.\n", res.s);
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &W, &H);
        solve();
    }
    return 0;
}
