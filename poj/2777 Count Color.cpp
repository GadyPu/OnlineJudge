#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<set>
using std::set;
using std::sort;
using std::pair;
using std::swap;
using std::queue;
using std::multiset;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr, val) memset(arr, val, sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for(int i = 0; i < (int)n; i++)
#define tr(c, i) for(iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 100000;
const int INF = 0x3f3f3f3f;
typedef unsigned long long ull;
#define lc (root<<1)
#define rc (root<<1|1)
#define mid ((l + r)>>1)
bool color[40];
struct SegTree {
    struct Node { int c; }seg[N << 2];
    inline void push_down(int root) {
        if (seg[root].c > 0) {
            seg[lc].c = seg[rc].c = seg[root].c;
            seg[root].c = 0;
        }
    }
    inline void update(int root, int l, int r, int x, int y, int col) {
        if (x > r || y < l) return;
        if (x <= l && y >= r) {
            seg[root].c = col;
            return;
        }
        push_down(root);
        update(lc, l, mid, x, y, col);
        update(rc, mid + 1, r, x, y, col);
    }
    inline void built(int root, int l, int r) {
        seg[root].c = 1;
        if (l == r) return;
        built(lc, l, mid);
        built(rc, mid + 1, r);
    }
    inline void query(int root, int l, int r, int x, int y) {
        if (x > r || y < l) return;
        if (seg[root].c > 0) {
            color[seg[root].c] = true;
            return;
        }
        query(lc, l, mid, x, y);
        query(rc, mid + 1, r, x, y);
    }
}work;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    char ch;
    int n, q, t, c, x, y;
    while (~scanf("%d %d %d", &n, &t, &q)) {
        work.built(1, 1, n);
        while (q--) {
            getchar();
            scanf("%c", &ch);
            if ('C' == ch) {
                scanf("%d %d %d", &x, &y, &c);
                work.update(1, 1, n, x, y, c);
            } else {
                scanf("%d %d", &x, &y);
                memset(color, false, sizeof(color));
                work.query(1, 1, n, x, y);
                int tot = 0;
                for (int i = 1; i < t + 2; i++) { if (color[i]) tot++; }
                printf("%d\n", tot);
            }
        }
    }
    return 0;
}
