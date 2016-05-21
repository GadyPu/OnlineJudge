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
using std::pair;
using std::vector;
using std::unique;
using std::lower_bound;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr,val) memset(arr,val,sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
const int Max_N = 100010;
typedef unsigned long long ull;
int n, m;
vector<int> vec;
void solve() {
    int ans = 0;
    sort(all(vec));
    vec.erase(unique(all(vec)), vec.end());
    rep(i, sz(vec)) {
        vector<int>::iterator ite = lower_bound(all(vec), m - vec[i]);
        if ((ite != vec.end() && *ite + vec[i] == m) ||  vec[i] << 1 == m) ans++;
    }
    vec.clear();
    printf("%d\n", ans);
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t, v;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &m);
        rep(i, n) scanf("%d", &v), vec.pb(v);
        solve();
    }
    return 0;
}
