#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#define lc root<<1
#define rc root<<1|1
#define mid ((l+r)>>1)
using std::max;
using std::min;
const int Max_N = 1000010;
const int INF = 0x7fffffff;
int tmax, tmin, ans1[Max_N], ans2[Max_N];
struct Node { int tmin, tmax; };
struct SegTree {
    Node seg[Max_N * 3];
    inline void push_up(int root) {
        seg[root].tmax = max(seg[lc].tmax, seg[rc].tmax);
        seg[root].tmin = min(seg[lc].tmin, seg[rc].tmin);
    }
    inline void built(int root, int l, int r) {
        if (l == r) {
            scanf("%d", &seg[root].tmax);
            seg[root].tmin = seg[root].tmax;
            return;
        }
        built(lc, l, mid);
        built(rc, mid + 1, r);
        push_up(root);
    }
    inline void query(int root, int l, int r, int x, int y) {
        if (x > r || y < l) return;
        if (x <= l && y >= r) {
            tmax = max(tmax, seg[root].tmax);
            tmin = min(tmin, seg[root].tmin);
            return;
        }
        query(lc, l, mid, x, y);
        query(rc, mid + 1, r, x, y);
    }
}seg;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif    
    int i, d, n, k;
    while (~scanf("%d %d", &n, &k)) {
        d = 0, seg.built(1, 1, n);
        for (i = 0; i + k <= n; i++) {
            tmax = -INF, tmin = INF;
            seg.query(1, 1, n, i + 1, i + k);
            ans1[d] = tmin, ans2[d++] = tmax;
        }
        for (i = 0; i < d; i++) {
            printf("%d%c", ans1[i], i < d - 1 ? ' ' : '\n');
        }
        for (i = 0; i < d; i++) {
            printf("%d%c", ans2[i], i < d - 1 ? ' ' : '\n');
        }
    }
    return 0;
}
