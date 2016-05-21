#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
using std::map;
using std::min;
using std::sort;
using std::pair;
using std::vector;
using std::multimap;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cls(arr, val) memset(arr, val, sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for(int i = 0; i < (int)n; i++)
#define tr(c, i) for(iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 2100000;
const int INF = 0x3f3f3f3f;
short hash[N << 1 | 1];
int a, b, c, d;
inline int squre(int x) {
    return x * x;
}
void solve() {
    cls(hash, 0);
    int ans = 0, ret = 0;
    for(int i = -100; i <= 100; i++) {
        if(!i) continue;
        for(int j = -100; j <= 100; j++) {
            if(!j) continue;
            ret = a * squre(i) + b * squre(j);
            hash[N - ret]++;
        }
    }
    for(int i = -100; i <= 100; i++) {
        if(!i) continue;
        for(int j = -100; j <= 100; j++) {
            if(!j) continue;
            ret = c * squre(i) + d * squre(j) + N;
            if(ret >= 0 && ret <= 2 * N) ans += hash[ret];
        }
    }
    printf("%d\n", ans);
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    while(~scanf("%d %d %d %d", &a, &b, &c, &d)) {
        if(a < 0 && b < 0 && c < 0 && d < 0 || a > 0 && b > 0 && c > 0 && d > 0) {
            puts("0");
            continue;
        }
        solve();
    }
    return 0;
}
