#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#define lc root<<1
#define rc root<<1|1
#define mid ((l+r)>>1)
typedef unsigned long long ull;
const int Max_N = 50010;
const int Mod = 1000000007;
struct Node { int val; };
struct SegTree {
    Node seg[Max_N << 2];
    inline void push_up(int root) {
        seg[root].val = (ull)seg[lc].val * seg[rc].val % Mod;
    }
    inline void built(int root, int l, int r) {
        if (l == r) {
            scanf("%d", &seg[root].val);
            return;
        }
        built(lc, l, mid);
        built(rc, mid + 1, r);
        push_up(root);
    }
    inline void update(int root, int l, int r, int p, int v) {
        if (p > r || p < l) return;
        if (p <= l && p >= r) {
            seg[root].val = v;
            return;
        }
        update(lc, l, mid, p, v);
        update(rc, mid + 1, r, p, v);
        push_up(root);
    }
    inline int query(int root, int l, int r, int x, int y) {
        if (x > r || y < l) return 1;
        if (x <= l && y >= r) return seg[root].val;
        int v1 = query(lc, l, mid, x, y);
        int v2 = query(rc, mid + 1, r, x, y);
        return (ull)v1 * v2 % Mod;
    }
}seg;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t, n, q, a, b, c;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        seg.built(1, 1, n);
        scanf("%d", &q);
        while (q--) {
            scanf("%d %d %d", &a, &b, &c);
            if (!a) printf("%d\n", seg.query(1, 1, n, b, c));
            else seg.update(1, 1, n, b, c);
        }
    }
    return 0;
}
