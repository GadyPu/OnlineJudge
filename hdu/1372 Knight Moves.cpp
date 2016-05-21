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
const int N = 8;
typedef unsigned long long ull;
bool vis1[N][N], vis2[N][N];
const int dx[8] = { 1, 2, 1, 2, -1, -2, -1, -2 }, dy[8] = { -2, -1, 2, 1, 2, 1, -2, -1 };
int Sx, Sy, Dx, Dy;
struct Node {
    int x, y, s;
    Node(int i = 0, int j = 0, int k = 0) :x(i), y(j), s(k) {}
};
int dbfs() {
    if (Sx == Dx && Sy == Dy) return 0;
    cls(vis1, false), cls(vis2, false);
    queue<Node> p, q;
    p.push(Node(Sx, Sy, 0)), q.push(Node(Dx, Dy, 0));
    vis1[Sx][Sy] = true, vis2[Dx][Dy] = true;
    int ans1 = 0, ans2 = 0;
    while (!p.empty() && !q.empty()) {
        int tq = sz(p);
        while (tq--) {
            Node t = p.front(); p.pop();
            rep(i, 8) {
                int nx = t.x + dx[i], ny = t.y + dy[i];
                if (nx < 0 || nx >= N || ny < 0 || ny >= N || vis1[nx][ny]) continue;
                ans1 = t.s;
                if (vis2[t.x][t.y]) return ans1 + ans2 + 1;
                p.push(Node(nx, ny, ans1 + 1));
                vis1[nx][ny] = true;
            }
        }
        int tp = sz(q);
        while (tp--) {
            Node t = q.front(); q.pop();
            rep(i, 8) {
                int nx = t.x + dx[i], ny = t.y + dy[i];
                if (nx < 0 || nx >= N || ny < 0 || ny >= N || vis2[nx][ny]) continue;
                ans2 = t.s;
                if (vis1[t.x][t.y]) return ans1 + ans2 + 1;
                q.push(Node(nx, ny, ans2 + 1));
                vis2[nx][ny] = true;
            }
        }
    }
    return 0;
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    char s1[N], s2[N];
    while (~scanf("%s %s", s1, s2)) {
        Sx = s1[0] - 'a';
        Sy = s1[1] - '0' - 1;
        Dx = s2[0] - 'a';
        Dy = s2[1] - '0' - 1;
        printf("To get from %s to %s takes %d knight moves.\n", s1, s2, dbfs());
    }
    return 0;
}
