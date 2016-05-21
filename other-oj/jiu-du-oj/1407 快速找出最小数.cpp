#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#define lc root<<1
#define rc root<<1|1
#define mid ((l+r)>>1)
using std::min;
const int Max_N = 100010;
const int INF = ~0u >> 1;
struct Node {
    int val, add;
};
struct SegTree {
    Node seg[Max_N << 2];
    inline void push_up(int root) {
        seg[root].val = min(seg[lc].val, seg[rc].val);
    }
    inline void built(int root, int l, int r) {
        seg[root].add = 0;
        if (l == r) {
            scanf("%d", &seg[root].val);
            return;
        }
        built(lc, l, mid);
        built(rc, mid + 1, r);
        push_up(root);
    }
    inline void push_down(int root) {
        if (seg[root].add != 0) {
            int &_add = seg[root].add;
            seg[lc].add += _add;
            seg[lc].val += _add;
            seg[rc].add += _add;
            seg[rc].val += _add;
            _add = 0;
        }
    }
    inline void update(int root, int l, int r, int x, int y, int v) {
        if (x > r || y < l) return;
        if (x <= l && y >= r) {
            seg[root].add += v;
            seg[root].val += v;
            return;
        }
        push_down(root);
        update(lc, l, mid, x, y, v);
        update(rc, mid + 1, r, x, y, v);
        push_up(root);
    }
    inline int query(int root, int l, int r, int x, int y) {
        if (x > r || y < l) return INF;
        if (x <= l && y >= r) return seg[root].val;
        push_down(root);
        int v1 = query(lc, l, mid, x, y);
        int v2 = query(rc, mid + 1, r, x, y);
        return min(v1, v2);
    }
}seg;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    char buf[100];
    int n, m, a, b, c;
    while (~scanf("%d", &n)) {
        seg.built(1, 1, n);
        scanf("%d\n", &m);
        while (m--) {
            gets(buf);
            char *p = strchr(buf, ' ');
            if (strchr(++p, ' ')) {
                sscanf(buf, "%d %d %d", &a, &b, &c);
                if (a <= b) {
                    seg.update(1, 1, n, ++a, ++b, c);
                } else {
                    seg.update(1, 1, n, ++a, n, c);
                    seg.update(1, 1, n, 1, ++b, c);
                }
            } else {
                sscanf(buf, "%d %d", &a, &b);
                if (a <= b) {
                    printf("%d\n", seg.query(1, 1, n, ++a, ++b));
                } else {
                    int v1 = seg.query(1, 1, n, ++a, n);
                    int v2 = seg.query(1, 1, n, 1, ++b);
                    printf("%d\n", min(v1, v2));
                }
            }
        }
    }
    return 0;
}
