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
using std::queue;
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
int n, m, G[N][N];
bool vis[N], flag[N];
typedef unsigned long long ull;
void bfs() {
    bool f = false;
    queue<int> que;
    rep(i, n) {
        if (!flag[i]) {
            vis[i] = true;
            que.push(i);
        }
    }
    while (!que.empty()) {
        int p = que.front(); que.pop();
        rep(i, n) {
            if (G[p][i]) {
                if (vis[i]) continue;
                que.push(i);
                vis[i] = true;
            }
        }
    }
    rep(i, n) {
        if (!vis[i]) { f = true; break; }
    }
    puts(f ? "NO" : "YES");
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int a, b;
    while (~scanf("%d %d", &n, &m)) {
        cls(vis, 0), cls(flag, 0), cls(G, 0);
        rep(i, m) {
            scanf("%d %d", &a, &b);
            G[b - 1][a - 1] = 1;
            flag[a - 1] = 1;
        }
        bfs();
    }
    return 0;
}
