#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<set>
using std::set;
using std::sort;
using std::pair;
using std::swap;
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
const int N = 1010;
const int INF = ~0u >> 1;
typedef unsigned long long ull;
struct Node {
    int v;
    Node *ch[2];
    inline void set(int dat, Node *p) {
        v = dat, ch[0] = ch[1] = p;
    }
};
struct BST {
    Node *root, *tail, *null, stack[N];
    inline void init() {
        tail = &stack[0];
        null = tail++;
        null->set(INF, NULL);
        root = null;
    }
    inline Node *newNode(int dat) {
        Node *p = tail++;
        p->set(dat, null);
        return p;
    }
    inline void insert(Node *&x, int dat) {
        if (x == null) { x = newNode(dat); return; }
        insert(x->ch[dat > x->v], dat);
    }
    inline void insert(int dat) {
        insert(root, dat);
    }
    inline void find(int dat) {
        Node *x = root;
        while (x->v != dat) {
            if (dat < x->v) {
                putchar('E');
                x = x->ch[0];
            } else {
                putchar('W');
                x = x->ch[1];
            }
        }
        putchar('\n');
    }
}go;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t, n, v, q;
    scanf("%d", &t);
    while (t--) {
        go.init();
        scanf("%d", &n);
        rep(i, n) {
            scanf("%d", &v);
            go.insert(v);
        }
        scanf("%d", &q);
        while (q--) {
            scanf("%d", &v);
            go.find(v);
        }
    }
    return 0;
}
