#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
using std::map;
using std::min;
using std::find;
using std::pair;
using std::vector;
using std::multimap;
using std::lower_bound;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cls(arr, val) memset(arr, val, sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for(int i = 0; i < (int)n; i++)
#define tr(c, i) for(iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 1000000;
const int INF = 0x3f3f3f3f;
int tot, prime[N + 10];
bool is_prime[N + 10];
inline void init() {
    tot = 0;
    rep(i, N) is_prime[i] = true;
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i <= N; i++) {
        if(is_prime[i]) {
            prime[tot++] = i;
            for(int j = 2 * i; j <= N; j += i) is_prime[j] = false;
        }
    }
}
void solve(int x) {
    rep(i, tot) {
        int p = lower_bound(prime, prime + tot, prime[i] + x) - prime;
        if(prime[i] + x == prime[p]) {
            printf("%d %d\n", prime[p], prime[i]);
            return;
        }
    }
    puts("FAIL");
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    init();
    int t, n;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        solve(n);
    }
    return 0;
}
