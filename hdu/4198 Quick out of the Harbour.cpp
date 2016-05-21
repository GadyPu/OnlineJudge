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
bool vis[N][N];
char G[N][N];
int H, W, C, Sx, Sy, Dx, Dy;
const int dx[] = { 0, 0, -1, 1 }, dy[] = { -1, 1, 0, 0 };
struct Node {
    int x, y, s;
    Node(int i = 0, int j = 0, int k = 0) :x(i), y(j), s(k) {}
    inline bool operator<(const Node &a) const {
        return s > a.s;
    }
};
int bfs() {
    priority_queue<Node> q;
    q.push(Node(Sx, Sy, 0));
    vis[Sx][Sy] = true;
    while (!q.empty()) {
        Node t = q.top(); q.pop();
        if (t.x == Dx && t.y == Dy) return t.s;
        rep(i, 4) {
            int x = t.x + dx[i], y = t.y + dy[i];
            if (x < 0 || x >= H || y < 0 || y >= W) continue;
            if (G[x][y] == '#' || vis[x][y]) continue;
            if (G[x][y] == '@') q.push(Node(x, y, t.s + C + 1));
            else if (G[x][y] == '.') q.push(Node(x, y, t.s + 1));
            vis[x][y] = true;
        }
    }
    return -1;
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t;
    scanf("%d\n", &t);
    while (t--) {
        scanf("%d %d %d", &H, &W, &C);
        rep(i, H) {
            scanf("%s", G[i]);
            rep(j, W) {
                vis[i][j] = false;
                if (G[i][j] == 'S') Sx = i, Sy = j;
                if (i == H - 1 || i == 0 || j == 0 || j == W - 1) {
                    if (G[i][j] != '#') Dx = i, Dy = j;
                }
            }
        }
        printf("%d\n", bfs() + 1);
    }
    return 0;
}
