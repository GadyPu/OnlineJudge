#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<set>
using std::min;
using std::sort;
using std::pair;
using std::swap;
using std::vector;
using std::multiset;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cls(arr, val) memset(arr, val, sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for(int i = 0; i < (int)n; i++)
#define tr(c, i) for(iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 1 << 17;
const int INF = ~0u >> 1;
typedef unsigned long long ull;
bool isPrime(ull n) {
    for(int i = 2; (ull)i * i <= n; i++ ) {
        if(n % i == 0) {
            return false;
        }
    }
    return n != 1;
}
ull mod_pow(ull a, ull p) {
    ull ans = 1, M = p;
    while(p) {
        if(p & 1) ans = ans * a % M;
        a = a * a % M;
        p >>= 1;
    }
    return ans;
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    ull a, p;
    while(~scanf("%lld %lld", &p, &a), a + p) {
        if(isPrime(p)) { puts("no"); continue; }
        puts(a % p == mod_pow(a, p) ? "yes" : "no");
    }
    return 0;
}
