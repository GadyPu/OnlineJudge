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
#define iter(c) decltype((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)
const int Max_N = 110000;
typedef int key_t;
typedef unsigned long long ull;
struct Node {
    key_t key;
    Node *ch[2];
    double fix;
    int size;
    ull sum[5];
    bool vis;
    void set(const key_t &k, double pri, Node *p) {
        key = k, fix = pri, size = 1;
        vis = false;
        ch[0] = ch[1] = p;
        rep(i, 5) sum[i] = 0;
    }
    inline int cmp(const key_t v) const {
        return v == key ? -1 : v > key;
    }
};
struct Treap {
    int top;
    Node *tail, *root, *null;
    Node stack[Max_N], *pool[Max_N];
    inline double get_fix() {
        return rand() / (double)RAND_MAX;
    }
    inline void init() {
        top = 0;
        tail = &stack[0];
        null = tail++;
        null->set(0, 1.0, NULL);
        null->size = 0;
        root = null;
    }
    inline Node *newNode(const key_t &k, double pri) {
        Node *p = null;
        if (!top) p = tail++;
        else p = pool[--top];
        p->set(k, pri, null);
        return p;
    }
    inline void rotate(Node *&x, int d) {
        Node *k = x->ch[!d];
        x->ch[!d] = k->ch[d];
        k->ch[d] = x;
        x->vis = k->vis = false;
        x = k;
    }
    inline void insert(Node *&x, const key_t &k, double p) {
        if (x == null) { x = newNode(k, p); return; }
        int d = x->cmp(k);
        if (-1 == d) { x->vis = false; return; }
        insert(x->ch[d], k, p);
        if (x->fix > x->ch[d]->fix) rotate(x, !d);
        x->vis = false;
        return;
    }
    inline void erase(Node *&x, const key_t &k) {
        if (!x->size) return;
        int d = x->cmp(k);
        if (-1 == d) {
            if (!x->ch[0]->size || !x->ch[1]->size) {
                pool[top++] = x;
                x = x->ch[0]->size ? x->ch[0] : x->ch[1];
            } else {
                int c = x->ch[0]->fix < x->ch[1]->fix;
                rotate(x, !c);
                erase(x->ch[!c], k);
            }
        } else {
            erase(x->ch[d], k);
        }
        if (x->size) x->vis = false;
        return;
    }
    inline void insert(const key_t &k) {
        insert(root, k, get_fix());
    }
    inline void erase(const key_t &k) {
        erase(root, k);
    }
    inline int count(Node *x) {
        return !x->size ? 0 : x->size;
    }
    inline void dfs(Node *x) {
        if (!x->size) return;
        if (!x->vis) {
            Node *lch = x->ch[0], *rch = x->ch[1];
            dfs(lch); dfs(rch);
            int lcnt = count(lch);
            int rcnt = count(rch);
            x->size = lcnt + 1 + rcnt;
            rep(i, 5) x->sum[i] = 0;
            if (lch->size) rep(i, 5) x->sum[i] = lch->sum[i];
            x->sum[lcnt % 5] += x->key;
            if (rch->size) rep(i, 5) x->sum[(lcnt + 1 + i) % 5] += rch->sum[i];
            x->vis = true;
        }
    }
    inline void go() {
        int x;
        char buf[256];
        scanf("%s", buf);
        if (buf[0] == 'a') {
            scanf("%d", &x);
            insert(x);
        } else if (buf[0] == 'd') {
            scanf("%d", &x);
            erase(root, x);
        } else {
            dfs(root);
            if (!root->size) puts("0");
            else printf("%lld\n", root->sum[2]);
        }
    }
}trp;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int Q;
    while (~scanf("%d", &Q)) {
        trp.init();
        rep(q, Q) trp.go();
    }
    return 0;
}
