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
const int N = 1000007;
const int INF = 0x3f3f3f3f;
typedef long long ll;
struct Hash_Set {
    ll num[N << 1];
    int tot, head[N], next[N];
    inline void init() {
        tot = 0, cls(head, -1);
    }
    inline void insert(ll val) {
        int u = abs(val) % N;
        num[tot] = val, next[tot] = head[u], head[u] = tot++;
    }
    inline bool find(ll val) {
        int u = abs(val) % N;
        for (int i = head[u]; ~i; i = next[i]) {
            if (num[i] == val) return true;
        }
        return false;
    }
}hash;
ll arr[N], sum[N];
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    ll k;
    int t, n, c = 1;
    scanf("%d", &t);
    while (t--) {
        hash.init();
        scanf("%d %lld", &n, &k);
        for (int i = 1; i <= n; i++) scanf("%lld", &arr[i]);
        for (int i = 1; i <= n; i++) {
            sum[i] = sum[i - 1] + (i & 1 ? arr[i] : -arr[i]);
        }
        bool f = false;
        for (int i = n; i > 0; i--) {
            hash.insert(sum[i]);
            if (f) break;
            if (i & 1) {
                if (hash.find(sum[i - 1] + k)) {
                    f = true;
                    break;
                }
            } else {
                if (hash.find(sum[i - 1] - k)) {
                    f = true;
                    break;
                }
            }
        }
        printf("Case #%d: %s\n", c++, f ? "Yes." : "No.");
    }
    return 0;
}
