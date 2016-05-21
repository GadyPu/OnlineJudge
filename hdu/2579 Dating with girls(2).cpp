#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<map>
#include<set>
using std::cin;
using std::cout;
using std::endl;
using std::find;
using std::sort;
using std::pair;
using std::queue;
using std::vector;
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
const int INF = ~0u >> 1;
typedef unsigned long long ull;
char maze[N][N];
bool vis[N][N][11];
int r, c, k, Sx, Sy, Dx, Dy;
const int dx[4] = { -1, 1, 0, 0 }, dy[4] = { 0, 0, -1, 1 };
struct Node {
    int x, y, s;
    Node(int i = 0, int j = 0, int k = 0) :x(i), y(j), s(k) {}
};
queue<Node> que;
void bfs() {
    cls(vis, 0);
    while (!que.empty()) que.pop();
    que.push(Node(Sx, Sy, 0));
    vis[Sx][Sy][0] = 1;
    while (!que.empty()) {
        Node tp = que.front(); que.pop();
        if (tp.x == Dx && tp.y == Dy) { printf("%d\n", tp.s); return; }
        rep(i, 4) {
            int nx = dx[i] + tp.x, ny = dy[i] + tp.y, ns = tp.s + 1;
            if (nx < 0 || nx >= r || ny < 0 || ny >= c || vis[nx][ny][ns % k]) continue;
            if (maze[nx][ny] == '#' && ns % k != 0) continue;
            vis[nx][ny][ns % k] = 1;
            que.push(Node(nx, ny, ns));
        }
    }
    puts("Please give me another chance!");
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d %d", &r, &c, &k);
        rep(i, r) {
            scanf("%s", maze[i]);
            rep(j, c) {
                if (maze[i][j] == 'Y') Sx = i, Sy = j;
                else if (maze[i][j] == 'G') Dx = i, Dy = j;
            }
        }
        bfs();
    }
    return 0;
}
