#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<set>
using std::set;
using std::sort;
using std::pair;
using std::swap;
using std::multiset;
using std::priority_queue;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr, val) memset(arr, val, sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for(int i = 0; i < (int)n; i++)
#define tr(c, i) for(iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 310;
const int INF = 0x3f3f3f3f;
typedef unsigned long long ull;
char G[N][N];
bool vis[N][N];
int H, W;
const int dx[] = { 0, 0, -1, 1 }, dy[] = { -1, 1, 0, 0 };
struct P {
    int x, y, s;
    P(int i = 0, int j = 0, int k = 0) :x(i), y(j), s(k) {}
    inline bool operator<(const P &t) const {
        return s > t.s;
    }
}S;
int bfs() {
    priority_queue<P> q;
    q.push(S);
    vis[S.x][S.y] = true;
    while (!q.empty()) {
        P t = q.top(); q.pop();
        rep(i, 4) {
            int x = t.x + dx[i], y = t.y + dy[i];
            if (x < 0 || x >= H || y < 0 || y >= W) continue;
            if (vis[x][y] || G[x][y] == 'R' || G[x][y] == 'S') continue;
            if (G[x][y] == 'E') {
                q.push(P(x, y, t.s + 1));
                vis[x][y] = true;
            }
            if (G[x][y] == 'B') {
                vis[x][y] = true;
                q.push(P(x, y, t.s + 2));
            }
            if (G[x][y] == 'T') return t.s + 1;
        }
         
    }
    return -1;
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    while (~scanf("%d %d", &H, &W), H + W) {
        rep(i, H) {
            scanf("%s", G[i]);
            rep(j, W) {
                if (G[i][j] == 'Y') S.x = i, S.y = j;
                vis[i][j] = false;
            }
        }
        printf("%d\n", bfs());
    }
    return 0;
}
