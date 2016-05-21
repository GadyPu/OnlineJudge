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
using std::lower_bound;
using std::upper_bound;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cls(arr, val) memset(arr, val, sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for(int i = 0; i < (int)n; i++)
#define tr(c, i) for(iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 110;
const int INF = 0x3f3f3f3f;
vector<int> vec;
int a, b, c, d, e;
inline int cube(int x) {
    return x * x * x;
}
void solve() {
    int ans = 0, ret = 0;
    for(int i = -50; i <= 50; i++) {
        if(!i) continue;
        for(int j = -50; j <= 50; j++) {
            if(!j) continue;
            for(int k = -50; k <= 50; k++) {
                if(!k) continue;
                ret = a * cube(i) + b * cube(j) + c * cube(k);
                vec.pb(ret);
            }
        }
    }
    sort(all(vec));
    for(int i = -50; i <= 50; i++) {
        if(!i) continue;
        for(int j = -50; j <= 50; j++) {
            if(!j) continue;
            ret = d * cube(i) + e * cube(j);
            ans += upper_bound(all(vec), -ret) - lower_bound(all(vec), -ret);
        }
    }
    vec.clear();
    printf("%d\n", ans);
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    while(~scanf("%d %d %d %d %d", &a, &b, &c, &d, &e)) {
        solve();
    }
    return 0;
}
