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
using std::map;
using std::pair;
using std::vector;
#define all(c) (c).begin(), (c).end()
#define cls(arr,val) memset(arr,val,sizeof(arr))
#define iter(c) decltype((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)
const int Max_N = 100010;
typedef unsigned long long ull;
#define mid ((l+r)>>1)
#define lc (root<<1)
#define rc (root<<1|1)
struct Node { int val; };
int arr[Max_N];
struct SegTree {
    Node seg[Max_N << 2];
    inline void init() { cls(seg, 0); }
    inline void push_down(int root) {
        if (seg[root].val != 0) {
            int &t = seg[root].val;
            seg[lc].val += t;
            seg[rc].val += t;
            t = 0;
        }
    }
    inline void update(int root, int l, int r, int x, int y){
        if (x > r || y < l) return;
        if (x <= l && y >= r) { seg[root].val += 1; return; }
        push_down(root);
        update(lc, l, mid, x, y);
        update(rc, mid + 1, r, x, y);
    }
    inline int query(int root, int l, int r, int p) {
        if (p > r || p < l) return 0;
        if (p <= l && p >= r) return seg[root].val;
        push_down(root);
        int ret = 0;
        ret += query(lc, l, mid, p);
        ret += query(rc, mid + 1, r, p);
        return ret;
    }
}seg;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, a, b;
    while (~scanf("%d", &n) && n) {
        seg.init();
        rep(i, n) scanf("%d %d", &a, &b), seg.update(1, 1, n, a, b);
        rep(i, n) arr[i] = seg.query(1, 1, n, i + 1);
        rep(i, n) printf("%d%c", arr[i], i < n - 1 ? ' ' : '\n');
    }
    return 0;
}
