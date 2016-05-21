#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
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
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 100010;
typedef long long ll;
int A[N], B[N];
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    ll ans;
    int t, n, m, k, p;
    scanf("%d", &t);
    while (t--) {
        ans = 0;
        scanf("%d %d", &n, &m);
        rep(i, n) scanf("%d", &A[i]);
        rep(i, m) scanf("%d", &B[i]);
        sort(A, A + n), sort(B, B + m);
        k = n - 1, p = 0;
        while (k > -1 && p < m && A[k] > B[p]) ans += A[k--] - B[p++];
        printf("%lld\n", ans);
    }
    return 0;
}
