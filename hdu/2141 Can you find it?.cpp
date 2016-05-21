#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
using std::map;
using std::abs;
using std::find;
using std::pair;
using std::vector;
using std::multimap;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr, val) memset(arr, val, sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for(int i = 0; i < (int)n; i++)
#define tr(c, i) for(iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 500007;
const int INF = 0x3f3f3f3f;
struct Hash_Set {
    int tot, num[N], head[N], next[N];
    inline void init() {
        tot = 0, cls(head, -1);
    }
    inline void insert(int val) {
        int u = abs(val) % N;
        num[tot] = val, next[tot] = head[u], head[u] = tot++;
    }
    inline bool find(int val) {
        int u = abs(val) % N;
        for (int i = head[u]; ~i; i = next[i]) {
            if (num[i] == val) return true;
        }
        return false;
    }
}hash;
int A[3][510];
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int l, n, m, t, v, k = 1;
    while (~scanf("%d %d %d", &l, &n, &m)) {
        hash.init();
        rep(i, l) scanf("%d", &A[0][i]);
        rep(i, n) scanf("%d", &A[1][i]);
        rep(i, m) scanf("%d", &A[2][i]);
        rep(i, l) {
            rep(j, n) {
                int val = A[0][i] + A[1][j];
                hash.insert(val);
            }
        }
        scanf("%d", &t);
        printf("Case %d:\n", k++);
        while (t--) {
            bool f = false;
            scanf("%d", &v);
            rep(i, m) {
                if (hash.find(v - A[2][i])) f = true;
            }
            puts(f ? "YES" : "NO");
        }
    }
    return 0;
}
