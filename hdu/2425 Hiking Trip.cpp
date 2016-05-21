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
const int N = 110;
typedef unsigned long long ull;
bool vis[N][N];
char trip[N][N];
const int dx[] = { 0, 0, -1, 1 }, dy[] = { -1, 1, 0, 0 };
int R, C, Vs, Vp, Vt, Sx, Sy, Dx, Dy;
struct Node {
    int x, y, s;
    Node(int i = 0, int j = 0, int k = 0) :x(i), y(j), s(k) {}
    inline bool operator<(const Node &a) const {
        return s > a.s;
    }
};
int bfs() {
    cls(vis, false);
    priority_queue<Node> que;
    que.push(Node(Sx, Sy, 0));
    vis[Sx][Sy] = true;
    while (!que.empty()) {
        Node tmp = que.top(); que.pop();
        if (tmp.x == Dx && tmp.y == Dy) return tmp.s;
        rep(i, 4) {
            int nx = dx[i] + tmp.x, ny = dy[i] + tmp.y;
            char &ch = trip[nx][ny];
            if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
            if (ch == '@' || vis[nx][ny]) continue;
            if (ch == 'T') que.push(Node(nx, ny, tmp.s + Vt));
            else if (ch == '.') que.push(Node(nx, ny, tmp.s + Vs));
            else if (ch == '#') que.push(Node(nx, ny, tmp.s + Vp));
            vis[nx][ny] = true;
        }
    }
    return -1;
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int k = 1;
    while (~scanf("%d %d", &R, &C)) {
        scanf("%d %d %d", &Vp, &Vs, &Vt);
        rep(i, R) scanf("%s", trip[i]);
        scanf("%d %d %d %d", &Sx, &Sy, &Dx, &Dy);
        printf("Case %d: %d\n", k++, bfs());
    }
    return 0;
}
