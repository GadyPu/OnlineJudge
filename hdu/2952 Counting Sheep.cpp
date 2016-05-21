#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
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
char G[N][N];
bool vis[N][N];
int H, W;
const int dx[] = { 0, 0, -1, 1 }, dy[] = { -1, 1, 0, 0 };
void dfs(int x, int y) {
    vis[x][y] = true;
    rep(i, 4) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;
        if (vis[nx][ny] || G[nx][ny] == '.') continue;
        dfs(nx, ny);
    }
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t, ans;
    scanf("%d", &t);
    while (t--) {
        ans = 0;
        cls(vis, false);
        scanf("%d %d", &H, &W);
        rep(i, H) scanf("%s", G[i]);
        rep(i, H) {
            rep(j, W) {
                if (!vis[i][j] && G[i][j] == '#') ans++, dfs(i, j);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
