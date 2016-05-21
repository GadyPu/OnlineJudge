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
using std::fabs;
using std::sort;
using std::pair;
using std::vector;
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
struct Node {
    int t, x;
    bool operator<(const Node &b) const {
        return t < b.t;
    }
}rec[N];
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t, n, k = 1;
    scanf("%d", &t);
    while (t--) {
        double ans = 0.0;
        scanf("%d", &n);
        rep(i, n) scanf("%d %d", &rec[i].t, &rec[i].x);
        sort(rec, rec + n);
        for (int i = 1; i < n; i++) {
            ans = max(ans, fabs((double)rec[i].x - rec[i - 1].x) / (rec[i].t - rec[i - 1].t));
        }
        printf("Case #%d: %.2lf\n", k++, ans);
    }
    return 0;
}
