#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
using std::map;
using std::min;
using std::find;
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
const int N = 1010;
const int INF = 0x3f3f3f3f;
map<int, int> A;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, v, ans;;
    while(~scanf("%d", &n)) {
        A.clear();
        rep(i, n + 1) {
            scanf("%d", &v);
            A[v]++;
            if(2 == A[v]) ans = v;
        }
        printf("%d\n", ans);
    }
    return 0;
}
