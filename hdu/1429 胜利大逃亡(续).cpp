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
const int N = 22;
typedef unsigned long long ull;
char G[N][N];
bool vis[N][N][1030];
int H, W, T, Sx, Sy;
const int dx[] = { 0, 0, -1, 1 }, dy[] = { -1, 1, 0, 0 };
struct Node {
    int x, y, key, s;
    Node() {}
    Node(int i, int j, int k, int l) :x(i), y(j), key(k), s(l) {}
};
void bfs() {
    cls(vis, false);
    queue<Node> q;
    q.push(Node(Sx, Sy, 0, 0));
    vis[Sx][Sy][0] = true;
    while (!q.empty()) {
        Node t = q.front(); q.pop();
        if (G[t.x][t.y] == '^') {
            printf("%d\n", t.s < T ? t.s : -1);
            return;
        }
        rep(i, 4) {
            int key = t.key, x = t.x + dx[i], y = t.y + dy[i];
            if (x < 0 || x >= H || y < 0 || y >= W) continue;
            if (G[x][y] == '*' || vis[x][y][key]) continue;
            if (isupper(G[x][y]) && !(key & (1 << (G[x][y] - 'A')))) continue;
            if (islower(G[x][y])) key |= 1 << (G[x][y] - 'a');
            q.push(Node(x, y, key, t.s + 1));
            vis[x][y][key] = true;
        }
    }
    puts("-1");
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    while (~scanf("%d %d %d", &H, &W, &T)) {
        rep(i, H) {
            scanf("%s", G[i]);
            rep(j, W) {
                if (G[i][j] == '@') Sx = i, Sy = j;
            }
        }
        bfs();
    }
    return 0;
}
