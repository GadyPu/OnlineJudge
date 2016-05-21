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
using std::queue;
using std::vector;
using std::multimap;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr,val) memset(arr,val,sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 12;
typedef unsigned long long ull;
bool vis[2][N][N];
char G[2][N][N];
int H, W, T;
const int dx[] = { 0, 0, -1, 1 }, dy[] = { -1, 1, 0, 0 };
struct Node {
    int c, x, y, s;
    Node(int i = 0, int j = 0, int k = 0, int l = 0) :c(i), x(j), y(k), s(l) {}
};
bool bfs() {
    cls(vis, false);
    queue<Node> q;
    q.push(Node());
    vis[0][0][0] = true;
    while (!q.empty()) {
        Node t = q.front(); q.pop();
        if (G[t.c][t.x][t.y] == 'P') return t.s <= T;
        rep(i, 4) {
            int nx = t.x + dx[i], ny = t.y + dy[i];
            char &ch = G[t.c][nx][ny];
            if (nx < 0 || nx >= H || ny < 0 || ny >= W ) continue;
            if (ch == '*' || vis[t.c][nx][ny]) continue;
            if (ch == '#') {
                if (G[t.c ^ 1][nx][ny] == '#' || G[t.c ^ 1][nx][ny] == '*') continue;
                if (vis[t.c ^ 1][nx][ny]) continue;
                q.push(Node(t.c ^ 1, nx, ny, t.s + 1));
                vis[t.c ^ 1][nx][ny] = vis[t.c][nx][ny] = true;
                continue;
            }
            q.push(Node(t.c, nx, ny, t.s + 1));
            vis[t.c][nx][ny] = true;
        }
    }
    return false;
}
inline void input(bool d) {
    rep(i, H) scanf("%s", G[d][i]);
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d %d", &H, &W, &T);
        input(0), input(1);
        puts(bfs() ? "YES" : "NO");
    }
    return 0;
}
