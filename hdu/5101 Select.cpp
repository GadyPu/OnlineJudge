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
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr,val) memset(arr,val,sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 1010;
typedef long long ll;
int num[N], arr[N * 100], rec[N][102];
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    ll ans;
    int t, n, k, tot;
    scanf("%d", &t);
    while (t--) {
        ans = tot = 0;
        scanf("%d %d", &n, &k);
        rep(i, n) {
            scanf("%d", &num[i]);
            rep(j, num[i]) scanf("%d", &rec[i][j]),  arr[tot++] = rec[i][j];
        }
        sort(arr, arr + tot);
        rep(i, tot) ans += tot - (lower_bound(arr + i, arr + tot, k - arr[i] + 1) - arr);
        rep(i, n) {
            sort(rec[i], rec[i] + num[i]);
            rep(j, num[i]) {
                ans -= num[i] - (lower_bound(rec[i] + j, rec[i] + num[i], k - rec[i][j] + 1) - rec[i]);
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
