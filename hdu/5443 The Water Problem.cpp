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
const int N = 1010;
const int INF = 0x3f3f3f3f;
typedef unsigned long long ull;
int n, arr[N], st[N + 5][11];
struct SparseTable {
    inline void init() {
        rep(i, n) st[i][0] = arr[i];
        for (int j = 1; (1 << j) <= n; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    inline int rmq(int a, int b) {
        int k = __builtin_clz((int)1) - __builtin_clz(b - a + 1);
        return max(st[a][k], st[b - (1 << k) + 1][k]);
    }
}go;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t, a, b, q;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        rep(i, n) scanf("%d", &arr[i]);
        go.init();
        scanf("%d", &q);
        while(q--) {
            scanf("%d %d", &a, &b);
            printf("%d\n", go.rmq(a - 1, b - 1));
        }
    }
    return 0;
}
