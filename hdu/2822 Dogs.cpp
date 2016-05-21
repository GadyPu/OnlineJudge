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
const int N = 1010;
typedef unsigned long long ull;
const int dx[] = { 0, 0, -1, 1 }, dy[] = { -1, 1, 0, 0 };
bool vis[N][N];
char rec[N][N];
int m, n, Sx, Sy, Dx, Dy;
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
        Node tmp = que.top(); que.pop();
        if (tmp.x == Dx && tmp.y == Dy) { printf("%d\n", tmp.s); return; }
        rep(i, 4) {
            int nx = tmp.x + dx[i], ny = tmp.y + dy[i];
            if (nx < 0 || nx >= m || ny < 0 || ny >= n || vis[nx][ny]) continue;
            if (rec[nx][ny] == 'X') que.push(Node(nx, ny, tmp.s));
            else que.push(Node(nx, ny, tmp.s + 1));
            vis[nx][ny] = true;
        }
    }
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    while (~scanf("%d %d", &m, &n) && m + n) {
        rep(i, m) scanf("%s", rec[i]);
        scanf("%d %d %d %d", &Sx, &Sy, &Dx, &Dy);
        Sx--, Sy--, Dx--, Dy--;
        bfs();
    }
    return 0;
}
