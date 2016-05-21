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
#define sz(c) (int)(c).size()
#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cls(arr,val) memset(arr,val,sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define fork(i, k, n) for(int i = (int)k; i<= (int)n; i++)
#define forp(i, k, p) for(int i = (int)k; i > p; i--)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)
const int Max_N = 1010;
typedef unsigned long long ull;
int dp[Max_N][Max_N], arr[Max_N];
int main() {
#ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("out.txt","w+",stdout);
#endif
    int n, q, x, y;
    while(~scanf("%d %d",&n, &q)) {
        rep(i,n) scanf("%d",&arr[i + 1]);
        cls(dp, 0);
        fork(i, 1, n) {
            fork(j, i + 1, n) dp[i][j] += dp[i][j - 1] + (int)(arr[i] > arr[j]);
        }
        forp(j, n, 0) {
            forp(i, j ,0) dp[i][j] += dp[i + 1][j];
        }
        rep(i, q) scanf("%d %d",&x, &y), printf("%d\n",dp[x][y]);
    }
    return 0;
}
