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
const int Max_N = 110;
const int Mod = 110;
typedef unsigned long long ull;
const int dx[] = { 0, 0, -1, 1 }, dy[] = { -1, 1, 0, 0 };
bool vis[Max_N][Max_N];
char maze[Max_N][Max_N];
int N, M, res, fa[Max_N][Max_N], dir[Max_N][Max_N];
struct Node {
    int x, y, s;
    Node(int i = 0, int j = 0, int k = 0) :x(i), y(j), s(k) {}
    inline bool operator<(const Node &a) const {
        return s > a.s;
    }
};
void bfs() {
    cls(vis, false), cls(fa, 0), cls(dir, 0);
    priority_queue<Node> q;
    q.push(Node());
    while (!q.empty()) {
        Node t = q.top(); q.pop();
        if (t.x == N - 1 && t.y == M - 1) { res = t.s; return; }
        rep(i, 4) {
            int nx = t.x + dx[i], ny = t.y + dy[i];
            char &ch = maze[nx][ny];
            if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
            if (ch == 'X' || vis[nx][ny]) continue;
            if ('0' <= ch && ch <= '9') q.push(Node(nx, ny, t.s + 1 + ch - '0'));
            else q.push(Node(nx, ny, t.s + 1));
            vis[nx][ny] = true;
            fa[nx][ny] = t.x * Mod + t.y;
            dir[nx][ny] = i;
        }
    }
    res = -1;
}
void show_path(int x, int y) {
    if (-1 == res) { printf("God please help our poor hero.\nFINISH\n"); return; }
    int fx, fy;
    vector<int> path;
    for (;;) {
        fx = fa[x][y] / Mod;
        fy = fa[x][y] % Mod;
        if (!x && !y) break;
        path.push_back(dir[x][y]);
        x = fx, y = fy;
    }
    printf("It takes %d seconds to reach the target position, let me show you the way.\n", res);
    fx = fy = 0;
    for (int i = sz(path) - 1, j = 1; ~i && j <= res; i--) {
        x = fx + dx[path[i]], y = fy + dy[path[i]];
        char &ch = maze[x][y];
        if ('0' <= ch && ch <= '9') {
            int t = ch - '0';
            printf("%ds:(%d, %d)->(%d, %d)\n", j++, fx, fy, x, y);
            while (t--) printf("%ds:FIGHT AT (%d,%d)\n", j++, x, y);
        }
        else printf("%ds:(%d, %d)->(%d, %d)\n", j++, fx, fy, x, y);
        fx = x, fy = y;
    }
    puts("FINISH");
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    while (~scanf("%d %d", &N, &M)) {
        rep(i, N) scanf("%s", maze[i]);
        bfs();
        show_path(N - 1, M - 1);
    }
    return 0;
}
