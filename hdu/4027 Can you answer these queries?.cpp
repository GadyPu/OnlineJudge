#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<cmath>
#define lc root<<1
#define rc root<<1|1
#define mid ((l+r)>>1)
typedef unsigned long long ull;
const int Max_N = 100010;
struct Node { ull val; bool flag; };
struct SegTree {
    Node seg[Max_N << 2];
    inline void push_up(int root) {
        seg[root].val = seg[lc].val + seg[rc].val;
    }
    inline void built(int root, int l, int r) {
        seg[root].flag = false;
        if (l == r) {
            scanf("%lld", &seg[root].val);
            return;
        }
        built(lc, l, mid);
        built(rc, mid + 1, r);
        push_up(root);
    }
    inline void update(int root, int l, int r, int x, int y) {
        if (x > r || y < l || seg[root].flag) return;
        if (l == r) {
            seg[root].val = (ull)sqrt((double)seg[root].val);
            if (1 == seg[root].val) seg[root].flag = true;
            return;
        }
        update(lc, l, mid, x, y);
        update(rc, mid + 1, r, x, y);
        push_up(root);
        seg[root].flag = seg[lc].flag && seg[rc].flag;
    }
    inline ull query(int root, int l, int r, int x, int y) {
        if (x > r || y < l) return 0;
        if (x <= l && y >= r) return seg[root].val;
        ull v1 = query(lc, l, mid, x, y);
        ull v2 = query(rc, mid + 1, r, x, y);
        return v1 + v2;
    }
}seg;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, q, a, b, c, k = 1;
    while (~scanf("%d", &n)) {
        seg.built(1, 1, n);
        scanf("%d", &q);
        printf("Case #%d:\n", k++);
        while (q--) {
            scanf("%d %d %d", &a, &b, &c);
            if (b > c) b ^= c ^= b ^= c;
            if (!a) seg.update(1, 1, n, b, c);
            else printf("%lld\n", seg.query(1, 1, n, b, c));
        }
        printf("\n");
    }
    return 0;
}
