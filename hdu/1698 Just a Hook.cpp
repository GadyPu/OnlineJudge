#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#define lc root<<1
#define rc root<<1|1
#define mid ((l+r)>>1)
const int Max_N = 100010;
struct Node { int v, add; };
struct SegTree {
    Node seg[Max_N << 2];
    inline void built(int root, int l, int r) {
        seg[root].add = 0;
        if (l == r) {
            seg[root].v = 1;
            return;
        }
        built(lc, l, mid);
        built(rc, mid + 1, r);
        seg[root].v = seg[lc].v + seg[rc].v;
    }
    inline void push_down(int root, int len) {
        if (seg[root].add != 0) {
            int &x = seg[root].add;
            seg[lc].add = seg[rc].add = x;
            seg[lc].v = (len - (len >> 1)) * x;
            seg[rc].v = (len >> 1) * x;
            x = 0;
        }
    }
    inline void update(int root, int l, int r, int x, int y, int add) {
        if (x > r || y < l) return;
        if (x <= l && y >= r) {
            seg[root].add = add;
            seg[root].v = (r - l + 1) * add;
            return;
        }
        push_down(root, r - l + 1);
        update(lc, l, mid, x, y, add);
        update(rc, mid + 1, r, x, y, add);
        seg[root].v = seg[lc].v + seg[rc].v;
    }
    inline int query() {
        return seg[1].v;
    }
}seg;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t, n, m, a, b, c, k = 1;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &m);
        seg.built(1, 1, n);
        while (m--) {
            scanf("%d %d %d", &a, &b, &c);
            seg.update(1, 1, n, a, b, c);
        }
        printf("Case %d: The total value of the hook is %d.\n", k++, seg.query());
    }
    return 0;
}
