#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<set>
using std::abs;
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
const int N = 5010;
const int M = 3000007;
const int INF = 0x3f3f3f3f;
typedef long long ll;
ll A[4][N];
struct HashSet {
    struct Node {
        ll v;
        int cnt;
    }arr[N * N];
    int tot, head[M], next[M];
    inline void init() {
        tot = 0;
        rep(i, M) head[i] = -1;
    }
    inline void insert(ll val) {
        bool f = false;
        int u = abs(val) % M;
        for (int i = head[u]; ~i; i = next[i]) {
            if (arr[i].v == val) {
                f = true;
                arr[i].cnt++;
            }
        }
        if (!f) {
            arr[tot].v = val, arr[tot].cnt = 1; next[tot] = head[u], head[u] = tot++;
        }
    }
    inline int find(ll val) {
        int u = abs(val) % M;
        for (int i = head[u]; ~i; i = next[i]) {
            if (arr[i].v == val) return arr[i].cnt;
        }
        return 0;
    }
}work;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n;
    while (~scanf("%d", &n)) {
        ll ans = 0;
        work.init();
        rep(i, n) {
            rep(j, 4) scanf("%lld", &A[j][i]);
        }
        rep(i, n) {
            rep(j, n) {
                work.insert(A[0][i] + A[1][j]);
            }
        }
        rep(i, n) {
            rep(j, n) {
                ans += work.find(-(A[2][i] + A[3][j]));
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
