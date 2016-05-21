#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
using std::max;
using std::cin;
using std::cout;
using std::endl;
using std::find;
using std::sort;
using std::map;
using std::pair;
using std::vector;
using std::multimap;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr,val) memset(arr,val,sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 1; i <= (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 1010;
const int INF = 0x7fffffff;
typedef long long ll;
ll p, ans, arr[N], sum[N];
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t, n;
    scanf("%d", &t);
    while (t--) {
        ans =  -INF;
        scanf("%d %lld", &n, &p);
        rep(i, n) scanf("%lld", &arr[i]);
        rep(i, n) {
            ll tmp = arr[i]; arr[i] = p;
            rep(j, n) {
                sum[j] = sum[j - 1] > 0 ? sum[j - 1] + arr[j] : arr[j];
                ans = max(ans, sum[j]);
            }
            arr[i] = tmp;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
