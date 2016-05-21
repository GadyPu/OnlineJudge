#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
#include<set>
using std::cin;
using std::cout;
using std::endl;
using std::find;
using std::sort;
using std::set;
using std::map;
using std::pair;
using std::vector;
using std::lower_bound;
#define sz(c) (int)(c).size()
#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cls(arr,val) memset(arr,val,sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)
const int Max_N = 10010;
typedef unsigned long long ull;
struct PrimeSpilt {
    int tot, prime[Max_N];
    inline bool isPrime(int n) {
        for(int i = 2; i * i <= n; i++) {
            if(!(n % i)) return false;
        }
        return n != 1;
    }
    inline void init() {
        tot = 0;
        for(int i = 1;i < Max_N ;i++) {
            if(isPrime(i)) prime[tot++] = i;
        }
    }
    inline void work(int n) {
        int ans = 0;
        for(int i = 0;i < tot && prime[i] < n; i++) {
            int p = lower_bound(prime + i, prime + tot, n - prime[i]) - prime;
            if(prime[i] + prime[p] == n && i != p) ans++;
        }
        printf("%d\n", ans);
    }
}go;
int main() {
#ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("out.txt","w+",stdout);
#endif
    int n;
    go.init();
    while(~scanf("%d", &n) && n) go.work(n);
    return 0;
}
