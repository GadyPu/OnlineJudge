#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<map>
using std::min;
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
const int N = 210;
const int INF = ~0u >> 1;
typedef unsigned long long ull;
char G[N][N];
int H, W, Sx, Sy, Dx, Dy, dist[2][N][N];
const int dx[] = { 0, 0, -1, 1 }, dy[] = { -1, 1, 0, 0 };
struct Node {
    int x, y;
    Node(int i = 0, int j = 0) :x(i), y(j) {}
}Y, M;
void bfs(int x, int y, bool d) {
    queue<Node> q;
    q.push(Node(x, y));
    dist[d][x][y] = 0;
    while (!q.empty()) {
        Node t = q.front(); q.pop();
        rep(i, 4) {
            int nx = t.x + dx[i], ny = t.y + dy[i];
            if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;
            if (G[nx][ny] == '#' || dist[d][nx][ny]) continue;
            dist[d][nx][ny] = dist[d][t.x][t.y] + 1;
            q.push(Node(nx, ny));
        }
    }
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    while (~scanf("%d %d", &H, &W)) {
        cls(dist, 0);
        vector<Node> kfc;
        rep(i, H) {
            scanf("%s", G[i]);
            rep(j, W) {
                if (G[i][j] == 'Y') Sx = i, Sy = j;
                if (G[i][j] == 'M') Dx = i, Dy = j;
                if (G[i][j] == '@') kfc.pb(Node(i, j));
            }
        }
        bfs(Sx, Sy, 0), bfs(Dx, Dy, 1);
        int res = INF;
        rep(i, sz(kfc)) {
            Node &k = kfc[i];
            int A = dist[0][k.x][k.y], B = dist[1][k.x][k.y];
            if (!A || !B) continue;
            res = min(res, A + B);
        }
        printf("%d\n", res * 11);
    }
    return 0;
}
