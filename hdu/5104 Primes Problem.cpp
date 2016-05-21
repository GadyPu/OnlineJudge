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
using std::multiset;
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
const int N = 10010;
typedef unsigned long long ull;
bool P[N];
int tot, prime[1500];
bool isPrim(int n) {
    for (int i = 2; i * i <= n; i++) if (n % i == 0) return false;
    return n != 1;
}
inline void init() {
    for (int i = 1; i < N;i++) {
        if (isPrim(i)) prime[tot++] = i, P[i] = true;
        else P[i] = false;
    }
}
inline void solve(int n) {
    int res = 0;
    for (int i = 0; i < tot && prime[i] < n; i++) {
        for (int j = i; j < tot && prime[j] < n; j++) {
            int t = n - prime[i] - prime[j];
            if (t >= prime[j] && P[t]) res++;
        }
    }
    printf("%d\n", res);
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n;
    init();
    while (~scanf("%d", &n)) {
        solve(n);
    }
    return 0;
}
