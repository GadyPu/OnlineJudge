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
const int N = 32;
typedef unsigned long long ull;
char G[N][N][N];
bool vis[N][N][N];
int L, R, C, Sx, Sy, Sz, Dx, Dy, Dz;
const int dx[] = { -1, 1, 0, 0, 0, 0 };
const int dy[] = { 0, 0, -1, 1, 0, 0 }, dz[] = { 0, 0, 0, 0, -1, 1 };
struct Node {
    int x, y, z, s;
    Node() {}
    Node(int i, int j, int k, int l) :x(i), y(j), z(k), s(l) {}
};
int bfs() {
    cls(vis, false);
    queue<Node> q;
    q.push(Node(Sx, Sy, Sz, 0));
    vis[Sx][Sy][Sz] = true;
    while (!q.empty()) {
        Node t = q.front(); q.pop();
        if (t.x == Dx && t.y == Dy && t.z == Dz) return t.s;
        rep(i, 6) {
            int x = t.x + dx[i], y = t.y + dy[i], z = t.z + dz[i];
            if (x < 0 || x >= L || y < 0 || y >= R || z < 0 || y >= C) continue;
            if (vis[x][y][z] || G[x][y][z] == '#') continue;
            q.push(Node(x, y, z, t.s + 1));
            vis[x][y][z] = true;
        }
    }
    return 0;
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    while (~scanf("%d %d %d", &L, &R, &C) && L + R + C) {
        rep(i, L) {
            rep(j, R) {
                scanf("%s", G[i][j]);
                rep(k, C) {
                    if (G[i][j][k] == 'S') Sx = i, Sy = j, Sz = k;
                    if (G[i][j][k] == 'E') Dx = i, Dy = j, Dz = k;
                }
            }
        }
        int ret = bfs();
        if (!ret) puts("Trapped!");
        else printf("Escaped in %d minute(s).\n", ret);
     }
    return 0;
}
