#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<set>
using std::max;
using std::sort;
using std::pair;
using std::swap;
using std::queue;
using std::multiset;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr, val) memset(arr, val, sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for(int i = 0; i < (int)n; i++)
#define tr(c, i) for(iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 30;
const int INF = 0x3f3f3f3f;
typedef unsigned long long ull;
struct Node {
    int v, w;
}A[N];
bool vis[N];
int W, K, n, ans;
void dfs(int cur, int w, int v, int tot) {
    if (tot == K) {
        ans = max(ans, v);
        return;
    }
    for (int i = cur; i < n; i++) {
        if (!vis[i] && tot + 1 <= K && w + A[i].w <= W) {
            vis[i] = true;
            dfs(i + 1, w + A[i].w, v + A[i].v, tot + 1);
            vis[i] = false;
        }
    }
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t;
    scanf("%d", &t);
    while (t--) {
        ans = -INF;
        scanf("%d %d", &n, &K);
        rep(i, n) {
            vis[i] = false;
            scanf("%d %d", &A[i].v, &A[i].w);
        }
        scanf("%d", &W);
        dfs(0, 0, 0, 0);
        printf("%d\n", ans);
    }
    return 0;
}
