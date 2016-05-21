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
const int N = 1 << 20;
char buf[N];
struct Node {
    int s;
    char dat;
    Node *fa, *ch[2];
    inline void set(int i, char j, Node *p) {
        s = i, dat = j;
        fa = ch[0] = ch[1] = p;
    }
    inline void push_up() {
        s = ch[0]->s + ch[1]->s + 1;
    }
    inline bool dir() const {
        return fa->ch[0] == this;
    }
    inline void link(Node *x, bool d) {
        ch[d] = x;
        x->fa = this;
    }
};
struct SplayTree {
    Node *root, *tail, *null, stack[N];
    inline void init(int n) {
        tail = &stack[0];
        null = tail++;
        null->set(0, '.', NULL);
        root = newNode('.');
        root->link(newNode('.'), 1);
        Node *x = built(1, n);
        root->ch[1]->link(x, 0);
        root->ch[1]->push_up();
        root->push_up();
        splay(x, null);
    }
    inline Node *built(int l, int r) {
        if(l > r) return null;
        int mid = (l + r) >> 1;
        Node *p = newNode(buf[mid - 1]);
        p->ch[0] = built(l, mid -1);
        if(p->ch[0] != null) p->ch[0]->fa = p;
        p->ch[1] = built(mid + 1, r);
        if(p->ch[1] != null) p->ch[1]->fa = p;
        p->push_up();
        return p;
    }
    inline Node *newNode(char dat) {
        Node *p = tail++;
        p->set(1, dat, null);
        return p;
    }
    inline void rotate(Node *&x, bool d) {
        Node *y = x->fa;
        y->ch[!d] = x->ch[d];
        x->fa = y->fa;
        if(x->ch[d]->s) x->ch[d]->fa = y;
        if(y->fa->s) y->fa->ch[!y->dir()] = x;
        x->ch[d] = y;
        y->fa = x, y->push_up();
        if (y == root) root = x;
    }
    inline void splay(Node *x, Node *f) {
        if(x == root) return;
        while(x->fa != f) {
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
            t = x->ch[0]->s;
            if(t == k) break;
            else if(k < t) x = x->ch[0];
            else k -= t + 1, x = x->ch[1];
        }
        return x;
    }
    inline void insert(char dat, int k) {
        if(k > root->s) k = root->s - 2;
        k--;
        splay(select(root, k), null);
        splay(select(root, k + 1), root);
        Node *x = newNode(dat);
        root->ch[1]->link(x, 0);
        root->ch[1]->push_up();
        root->push_up();
        splay(x, null);
    }
    inline char operator[](int k) {
        splay(select(root, k), null);
        return root->dat;
    }
}spt;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int q, k;
    char op, dat;
    while(~scanf("%s", buf)) {
        scanf("%d", &q);
        spt.init(strlen(buf));
        while(q--) {
            getchar();
            scanf("%c", &op);
            if(op == 'Q') {
                scanf(" %d", &k);
                printf("%c\n", spt[k]);
            } else {
                scanf(" %c %d", &dat, &k);
                spt.insert(dat, k);
            }
        }
    }
    return 0;
}
