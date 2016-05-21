#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
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
const int Max_N =210;
typedef unsigned long long ull;
const int dx[] = { 0, 0, 1, -1 }, dy[] = { 1, -1, 0, 0 };
bool vis[Max_N][Max_N];
char maze[Max_N][Max_N];
int N, M, Sx, Sy, Dx, Dy;
struct Node {
    int x, y, s;
    Node(int i = 0, int j = 0, int k = 0) :x(i), y(j), s(k) {}
    bool operator<(const Node &a) const {
        return s > a.s;
    }
};
void bfs() {
    cls(vis, false);
    priority_queue<Node> que;
    que.push(Node(Sx, Sy, 0));
    vis[Sx][Sy] = true;
    while (!que.empty()) {
        Node tp = que.top(); que.pop();
        if (tp.x == Dx && tp.y == Dy) { printf("%d\n", tp.s); return; }
        rep(i, 4) {
            int nx = dx[i] + tp.x, ny = dy[i] + tp.y;
            if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
            if (maze[nx][ny] == '#' || vis[nx][ny]) continue;
            if (maze[nx][ny] == 'x') que.push(Node(nx, ny, tp.s + 2));
            else que.push(Node(nx, ny, tp.s + 1));
            vis[nx][ny] = true;
        }
    }
    puts("Poor ANGEL has to stay in the prison all his life.");
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    while (~scanf("%d %d", &N, &M)) {
        rep(i, N) {
            scanf("%s", maze[i]);
            rep(j, M) {
                if (maze[i][j] == 'a') Dx = i, Dy = j;
                else if (maze[i][j] == 'r') Sx = i, Sy = j;
            }
        }
        bfs();
     }
    return 0;
}
