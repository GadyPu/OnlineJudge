#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<set>
using std::set;
using std::min;
using std::pair;
using std::swap;
using std::vector;
using std::multiset;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cls(arr, val) memset(arr, val, sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for(int i = 0; i < (int)n; i++)
#define tr(c, i) for(iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 1 << 17;
const int INF = ~0u >> 1;
int arr[N];
struct Node {
    bool rev;
    int dat, s, mval, delta;
    Node *fa, *ch[2];
    inline void set(int _dat, int _s, Node *p) {
        rev = delta =0;
        dat = mval = _dat, s = _s;
        fa = ch[0] = ch[1] = p;
    }
    inline bool dir() const {
        return this == fa->ch[0];
    }
    inline void link(Node *x, bool d) {
        ch[d] = x, x->fa = this;
    }
    inline void push_up() {
        s = ch[0]->s + ch[1]->s + 1;
        mval = min(dat, min(ch[0]->mval, ch[1]->mval));
    }
    inline void update() {
        if(!s) return;
        rev ^= 1;
        swap(ch[0], ch[1]);
    }
    inline void add(int v) {
        if(!s) return;
        delta += v;
        mval += v;
        dat += v;
    }
    inline void push_down() {
        if(delta) {
            ch[0]->add(delta);
            ch[1]->add(delta);
            delta = 0;
        }
        if(rev) {
            ch[0]->update();
            ch[1]->update();
            rev ^= 1;
        }
    }
};
#define RRL root->ch[1]->ch[0]
struct SplayTree {
    int top;
    Node *root, *tail;
    Node *null, stack[N], *pool[N >> 1];
    inline void init(int n) {
        top = 0, tail = &stack[0];
        null = tail++;
        null->set(INF, 0, NULL);
        root = newNode(INF);
        root->link(newNode(INF), 1);
        Node *x = built(1, n);
        root->ch[1]->link(x, 0);
        root ->ch[1]->push_up();
        root->push_up();
        splay(x, null);
    }
    inline Node *newNode(int v) {
        Node *p = !top ? tail++ : pool[--top];
        p->set(v, 1, null);
        return p;
    }
    inline Node *built(int l, int r) {
        if(l > r) return null;
        int mid = (l + r) >> 1;
        Node *p = newNode(arr[mid]);
        p->ch[0] = built(l, mid - 1);
        if(p->ch[0]->s) p->ch[0]->fa = p;
        p->ch[1] = built(mid + 1, r);
        if(p->ch[1]->s) p->ch[1]->fa = p;
        p->push_up();
        return p;
    }
    inline void rotate(Node *&x, bool d) {
        Node *y = x->fa;
        y->push_down(), x->push_down();
        y->ch[!d] = x->ch[d];
        if(x->ch[d]->s) x->ch[d]->fa = y;
        x->fa = y->fa;
        if(y->fa->s) y->fa->ch[!y->dir()] = x;
        x->ch[d] = y;
        y->fa = x, y->push_up();
        if(y == root) root = x;
    }
    inline void splay(Node *x, Node *f) {
        for(;x->fa !=f ;x->push_down()) {
            if(x->fa->fa == f) {
                rotate(x, x->dir());
            } else {
                bool d = x->fa->dir();
                if(d == x->dir()) rotate(x->fa, d), rotate(x, d);
                else rotate(x, !d), rotate(x, d);
            }
        }
        x->push_up();
    }
    inline Node *select(Node *x, int k) {
        for(int t = 0; x->s; ) {
            x->push_down();
            t = x->ch[0]->s;
            if(t == k) break;
            if(k < t) x = x->ch[0];
            else k -= t + 1, x = x->ch[1];
        }
        return x;
    }
    inline void get_range(int l, int r) {
        splay(select(root, l - 1), null);
        splay(select(root, r + 1), root);
    }
    inline void add(int l, int r, int v) {
        get_range(l, r);
        RRL->add(v);
        splay(RRL, null);
    }
    inline void insert(int k, int v) {
        splay(select(root, k), null);
        splay(select(root, k + 1), root);
        root->ch[1]->link(newNode(v), 0);
        root->ch[1]->push_up();
        root->push_up();
        splay(RRL, null);
    }
    inline void reverse(int l, int r) {
        get_range(l, r);
        RRL->update();
    }
    inline void revolve(int l, int r, int k) {
        int len = (r - l + 1);
        k = (k % len + len) % len;
        if(!k) return;
        if(1 == k) {
            erase(r);
            insert(l - 1, pool[--top]->dat);
        } else {
            splay(select(root, r - k + 1), null);
            splay(select(root, r + 1), root);
            splay(select(root, l - 1), root);
            splay(select(root, r), root->ch[1]);
            Node *x = root->ch[0]->ch[1];
            root->ch[0]->ch[1] = null;
            root->ch[0]->push_up();
            root->ch[1]->ch[0]->link(x, 1);
            splay(x, null);
        }
    }
    inline void erase(int k) {
        splay(select(root, k), null);
        Node *ret = root;
        root = root->ch[1];
        root->fa = null;
        splay(select(root, 0), null);
        root->ch[0] = ret->ch[0];
        root->ch[0]->fa = root;
        root->push_up();
        pool[top++] = ret;
    }
    inline void query(int l, int r) {
        get_range(l, r);
        printf("%d\n", RRL->mval);
    }
}spt;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    char buf[20];
    int n, q, a, b, c;
    while(~scanf("%d", &n)) {
        rep(i, n) scanf("%d", &arr[i + 1]);
        spt.init(n);
        scanf("%d", &q);
        while(q--) {
            scanf("%s", buf);
            if('D' == buf[2]) {
                scanf("%d %d %d", &a, &b, &c);
                spt.add(a, b, c);
            } else if('S' == buf[2]) {
                scanf("%d %d", &a, &b);
                spt.insert(a, b);
            } else if('V' == buf[2] && 'E' == buf[3]) {
                scanf("%d %d", &a, &b);
                spt.reverse(a, b);
            } else if('V' == buf[2] && 'O' == buf[3]) {
                scanf("%d %d %d", &a, &b, &c);
                spt.revolve(a, b, c);
            } else if('L' == buf[2]) {
                scanf("%d", &a);
                spt.erase(a);
            } else if('N' == buf[2]) {
                scanf("%d %d", &a, &b);
                spt.query(a, b);
            }
        }
    }
    return 0;
}
