#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstdio>
#define lc root<<1
#define rc root<<1|1
typedef unsigned long long ull;
const int Max_N = 100010;
int Mod;
struct Node {
    ull sum, add, mul;
};
struct SegTree {
    Node seg[Max_N << 2];
    inline void push_up(int root) {
        seg[root].sum = (seg[lc].sum + seg[rc].sum) % Mod;
    }
    inline void built(int root, int l, int r) {
        seg[root].add = 0, seg[root].mul = 1;
        if (l == r) {
            scanf("%lld", &seg[root].sum);
            seg[root].sum %= Mod;
            return;
        }
        int mid = (l + r) >> 1;
        built(lc, l, mid);
        built(rc, mid + 1, r);
        push_up(root);
    }
    inline void push_down(int root, int len) {
        if (seg[root].add != 0 || seg[root].mul != 1) {
            ull &_add = seg[root].add, &_mul = seg[root].mul;
            seg[lc].sum = (seg[lc].sum * _mul + (len - (len >> 1)) * _add) % Mod;
            seg[lc].mul = (seg[lc].mul * _mul) % Mod;
            seg[lc].add = (seg[lc].add * _mul + _add) % Mod;
            seg[rc].sum = (seg[rc].sum * _mul + (len >> 1) * _add) % Mod;
            seg[rc].mul = (seg[rc].mul * _mul) % Mod;
            seg[rc].add = (seg[rc].add * _mul + _add) % Mod;
            _add = 0, _mul = 1;
        }
    }
    inline void update(int root, int l, int r, int x, int y, ull val, ull mul) {
        if (x > r || y < l) return;
        if (x <= l && y >= r) {
            seg[root].add = (seg[root].add * mul + val) % Mod;
            seg[root].mul = (seg[root].mul * mul) % Mod;
            seg[root].sum = (seg[root].sum * mul + val * (r - l + 1)) % Mod;
            return;
        }
        push_down(root, r - l + 1);
        int mid = (l + r) >> 1;
        update(lc, l, mid, x, y, val, mul);
        update(rc, mid + 1, r, x, y, val, mul);
        push_up(root);
    }
    inline ull query(int root, int l, int r, int x, int y) {
        if (x > r || y < l) return 0;
        if (x <= l && y >= r) {
            return seg[root].sum;
        }
        push_down(root, r - l + 1);
        ull ret = 0;
        int mid = (l + r) >> 1;
        ret += query(lc, l, mid, x, y);
        ret += query(rc, mid + 1, r, x, y);
        return ret %= Mod;
    }
}seg;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, m, a, b, c, d;
    while (~scanf("%d %d", &n, &Mod)) {
        seg.built(1, 1, n);
        scanf("%d", &m);
        while (m--) {
            scanf("%d", &a);
            if (1 == a) {
                scanf("%d %d %d", &b, &c, &d);
                seg.update(1, 1, n, b, c, 0, d);
            } else if (2 == a) {
                scanf("%d %d %d", &b, &c, &d);
                seg.update(1, 1, n, b, c, d, 1);
            } else {
                scanf("%d %d", &b, &c);
                printf("%lld\n", seg.query(1, 1, n, b, c));
            }
        }
    }
    return 0;
}
