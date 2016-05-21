#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstdio>
#define lc root<<1
#define rc root<<1|1
using std::max;
const int Max_N = 200010;
const int INF = 0x3f3f3f3f;
int MOD;
struct Node { int val; };
struct SegTree {
    Node seg[Max_N << 2];
    inline void push_up(int root) {
        seg[root].val = max(seg[lc].val, seg[rc].val);
    }
    inline void update(int root, int l, int r, int pos, int t) {
        if (pos > r || pos < l) return;
        if (pos <= l && pos >= r) {
            seg[root].val += t;
            return;
        }
        int mid = (l + r) >> 1;
        update(lc, l, mid, pos, t);
        update(rc, mid + 1, r, pos, t);
        push_up(root);
    }
    inline int query(int root, int l, int r, int x, int y) {
        if (x > r || y < l) return -INF;
        if (x <= l && y >= r) return seg[root].val;
        int mid = (l + r) >> 1;
        int v1 = query(lc, l, mid, x, y);
        int v2 = query(rc, mid + 1, r, x, y);
        return max(v1, v2);
    }
}seg;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    char ch;
    int n, v, res, len = 0;
    while (~scanf("%d %d", &n, &MOD)) {
        res = 0;
        for (int i = 0; i < n; i++) {
            getchar();
            scanf("%c %d", &ch, &v);
            if (ch == 'A') ++len, seg.update(1, 1, n, len, (res + v) % MOD);
            else printf("%d\n", res = seg.query(1, 1, n, len - v + 1, n));
        }
    }
    return 0;
}
