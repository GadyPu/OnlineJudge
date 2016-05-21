#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
#include<set>
using std::set;
using std::map;
using std::min;
using std::max;
using std::cin;
using std::cout;
using std::endl;
using std::find;
using std::sort;
using std::pair;
using std::vector;
#define sz(c) (int)(c).size()
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr,val) memset(arr,val,sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 1; i <= (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)
#define mid ((l+r)>>1)
#define lc (root<<1)
#define rc (root<<1|1)
const int Max_N = 100010;
const int INF = 0x3f3f3f3f;
typedef unsigned long long ull;
int n, m, k, tmin, tmax;
struct SegTree {
    struct Node { int max, min; }seg[Max_N << 2];
    inline void built(int root, int l, int r) {
        if (l == r) {
            scanf("%d", &seg[root].max), seg[root].min = seg[root].max;
            return;
        }
        built(lc, l, mid);
        built(rc, mid + 1, r);
        seg[root].max = max(seg[lc].max, seg[rc].max);
        seg[root].min = min(seg[lc].min, seg[rc].min);
    }
    inline void query(int root, int l, int r, int x, int y) {
        if (x > r || y < l) return;
        if (x <= l && y >= r) {
            tmin = min(tmin, seg[root].min);
            tmax = max(tmax, seg[root].max);
            return;
        }
        query(lc, l, mid, x, y);
        query(rc, mid + 1, r, x, y);
    }
    inline int query(int l, int r) {
        tmin = INF, tmax = -INF;
        query(1, 1, n, l, r);
        return tmax - tmin;
    }
}seg;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int l, r, ans;
    while (~scanf("%d %d %d", &n, &m, &k)) {
        l = 1, ans = 0;
        seg.built(1, 1, n);
        rep(i, n) {
            r = i;
            if (l > r) continue;
            while (seg.query(l, r) > k) l++;
            if (seg.query(l, r) >= m && seg.query(l, r) <= k) ans = max(ans, r - l + 1);
        }
        printf("%d\n", ans);
    }
    return 0;
}
