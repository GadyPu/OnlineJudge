#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<map>
using std::abs;
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
const int N = 10;
typedef unsigned long long ull;
bool vis[N][N];
char G[N][N];
int H, W, T, Sx, Sy, Dx, Dy;
const int dx[] = { 0, 0, -1, 1 }, dy[] = { -1, 1, 0, 0 };
bool dfs(int x, int y, int s) {
    // 找到一个解就直接返回
    if (s == T && x == Dx && y == Dy) return true;
    int tmp = abs(x - Dx) + abs(y - Dy) - abs(T - s);
    // 当前位置到终点的所需要的时间大于剩下的时间
    // 奇偶性剪枝 ，起点和终点确定以后就可以确定走的步数是奇数还是偶数(没这个会超时滴%>_<%)
    if (tmp > 0 || tmp & 1) return false;
    rep(i, 4) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;
        if (vis[nx][ny] || G[nx][ny] == 'X') continue;
        vis[nx][ny] = true;
        if (dfs(nx, ny, s + 1)) return true;
        vis[nx][ny] = false;
    }
    return false;
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    while (~scanf("%d %d %d", &H, &W, &T) && H + W + T) {
        int tot = 0;
        rep(i, H) {
            scanf("%s", G[i]);
            rep(j, W) {
                vis[i][j] = false;
                if (G[i][j] == 'S') Sx = i, Sy = j;
                if (G[i][j] == 'D') Dx = i, Dy = j;
                if (G[i][j] == 'X') tot++;
            }
        }
        // 能走的格子个数比时间少的话，直接不符合，不用再搜了
        if (H * W - tot <= T) { puts("NO"); continue; }
        vis[Sx][Sy] = true;
        puts(dfs(Sx, Sy, 0) ? "YES" : "NO");
    }
    return 0;
}
