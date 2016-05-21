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
const int N = 110;
typedef unsigned long long ull;
char G[N][N];
bool vis[N][N][11][4]; // 访问标志
int H, W, K, Sx, Sy, Dx, Dy;
const int dx[] = { 0, 0, -1, 1 }, dy[] = { -1, 1, 0, 0 };
struct Node{
    // x坐标，y坐标 方向 转弯次数
    int x, y, dir, turn;
    Node() {}
    Node(int i, int j, int k, int l) :x(i), y(j), dir(k), turn(l) {}
};
bool bfs() {
    cls(vis, false);
    queue<Node> q;
    rep(i, 4) {
        int x = Sx + dx[i], y = Sy + dy[i];
        if (x < 0 || x >= H || y < 0 || y >= W || G[x][y] == '*') continue;
        q.push(Node(x, y, i, 0));
        vis[x][y][0][i] = true;
    }
    while (!q.empty()) {
        Node t = q.front(); q.pop();
        if (t.x == Dx && t.y == Dy) return true;
        rep(i, 4) {
            int x = t.x + dx[i], y = t.y + dy[i];
            if (x < 0 || x >= H || y < 0 || y >= W || G[x][y] == '*') continue;
            if (t.dir == i) {
                bool &p = vis[x][y][t.turn][i];
                if (!p) {
                    q.push(Node(x, y, t.dir, t.turn));
                    p = true;
                }
            } else {
                bool &p = vis[x][y][t.turn + 1][i];
                if (t.turn + 1 <= K && !p) {
                    q.push(Node(x, y, i, t.turn + 1));
                    p = true;
                }
            }
        }
    }
    return false;
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &H, &W);
        rep(i, H) scanf("%s", G[i]);
        scanf("%d %d %d %d %d", &K, &Sy, &Sx, &Dy, &Dx);
        Sx--, Sy--, Dx--, Dy--;
        puts(bfs() ? "yes" : "no");
    }
    return 0;
}
