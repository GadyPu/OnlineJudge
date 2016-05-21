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
const int N = 210;
typedef unsigned long long ull;
int H, G[N][N], vis[N][N];
const int dx[] = { 0, 0, -1, 1 }, dy[] = { -1, 1, 0, 0 };
struct Node {
    int x, y, s;
    Node(int i = 0, int j = 0, int k = 0) :x(i), y(j), s(k) {}
    inline bool operator<(const Node &a) const {
        return s > a.s;
    }
};
inline void read() {
    rep(i, H) {
        rep(j, H) {
            scanf("%d", &G[i][j]);
            vis[i][j] = -1;
        }
    }
}
int bfs() {
    priority_queue<Node> q;
    q.push(Node(0, 0, G[0][0]));
    while (!q.empty()) {
        Node t = q.top(); q.pop();
        if (t.x == H - 1 && t.y == H - 1) break;
        rep(i, 4) {
            int x = t.x + dx[i], y = t.y + dy[i];
            if (x < 0 || x >= H || y < 0 || y >= H) continue;
            if (t.s + G[x][y] < vis[x][y] || vis[x][y] == -1) {
                q.push(Node(x, y, t.s + G[x][y]));
                vis[x][y] = t.s + G[x][y];
            }
        }
    }
    return vis[H - 1][H - 1];
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int k = 1;
    while (~scanf("%d", &H), H) {
        read();
        printf("Problem %d: %d\n", k++, bfs());
    }
    return 0;
}
