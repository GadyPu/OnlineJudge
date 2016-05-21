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
using std::multiset;
using std::multimap;
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr,val) memset(arr,val,sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)
#define lc (root<<1)
#define rc (root<<1|1)
#define mid ((l+r)>>1)
const int Max_N = 500100;
typedef unsigned long long ull;
struct Node { int val; };
struct P {
    int v, id;
    friend bool operator<(const P &a, const P &b) {
        return a.v == b.v ? a.id < b.id : a.v < b.v;
    }
}rec[Max_N];
struct SegTree {
    Node seg[Max_N << 2];
    inline void init() {
        cls(seg, 0);
    }
    inline void insert(int root, int l, int r, int p) {
        if (p > r || p < l) return;
        if (p <= l && p >= r) { seg[root].val++; return; }
        insert(lc, l, mid, p);
        insert(rc, mid + 1, r, p);
        seg[root].val = seg[lc].val + seg[rc].val;
    }
    inline ull query(int root, int l, int r, int x, int y) {
        if (x > r || y < l) return 0;
        if (x <= l && y >= r) return seg[root].val;
        ull ret = 0;
        ret += query(lc, l, mid, x, y);
        ret += query(rc, mid + 1, r, x, y);
        return ret;
    }
}seg;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n;
    while (~scanf("%d", &n) && n) {
        seg.init();
        ull res = 0;
        for (int i = 1; i <= n; i++) scanf("%d", &rec[i].v), rec[i].id = i;
        sort(rec + 1, rec + n + 1);
        for (int i = 1; i <= n; i++) {
            res += seg.query(1, 1, n, rec[i].id, n);
            seg.insert(1, 1, n, rec[i].id);
        }
        printf("%lld\n", res);
    }
    return 0;
}
