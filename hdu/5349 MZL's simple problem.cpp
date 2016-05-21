#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
using std::map;
using std::min;
using std::find;
using std::pair;
using std::vector;
using std::multimap;
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)
const int N = 1 << 20;
const int INF = 0x3f3f3f3f;
inline int read() {
    char c; int r;
    while (((c = getchar()) < '0' || c > '9') && c ^ '-');
    bool f = c == '-'; if (f) r = 0; else r = c - '0';
    while ((c = getchar()) >= '0' && c <= '9') (r *= 10) += c - '0';
    if (f) return -r; else return r;
}
struct Node {
    int v, s, c;
    Node *ch[2];
    inline void set(int _v, int _s, Node *p) {
        v = _v, s = c = _s;
        ch[0] = ch[1] = p;
    }
    inline void push_up() {
        s = ch[0]->s + ch[1]->s + c;
    }
    inline int cmp(int x) const {
        return x == v ? -1 : x > v;
    }
};
struct SizeBalanceTree {
    int top;
    Node *null, *root, *tail;
    Node stack[N], *pool[N >> 1];
    inline void init() {
        top = 0;
        tail = &stack[0];
        null = tail++;
        null->set(0, 0, NULL);
        root = null;
    }
    inline Node *newNode(int v) {
        Node *x = !top ? tail++ : pool[--top];
        x->set(v, 1, null);
        return x;
    }
    inline void rotate(Node *&x, int d) {
        Node *k = x->ch[!d]; x->ch[!d] = k->ch[d], k->ch[d] = x;
        k->s = x->s; x->push_up(); x = k;
    }
    inline void Maintain(Node *&x, int d) {
        if (!x->s) return;
        if (x->ch[d]->ch[d]->s > x->ch[!d]->s) rotate(x, !d);
        else if (x->ch[d]->ch[!d]->s > x->ch[!d]->s) rotate(x->ch[d], d), rotate(x, !d);
        else return;
        Maintain(x, 0), Maintain(x, 1);
    }
    inline void insert(Node *&x, int v) {
        if (!x->s) { x = newNode(v); return; }
        x->s++;
        int d = x->cmp(v);
        if (-1 == d) { x->c++; return; }
        insert(x->ch[d], v);
        x->push_up();
        Maintain(x, d);
    }
    inline void erase(Node *&x, int p) {
        if (!x->s) return;
        x->s--;
        int d = x->cmp(p);
        if (-1 == d) {
            if (x->c > 1) { x->c--; return; }
            else if (!x->ch[0]->s || !x->ch[1]->s) {
                pool[top++] = x;
                x = x->ch[0]->s ? x->ch[0] : x->ch[1];
            } else {
                Node *ret = x->ch[1];
                for (; ret->ch[0]->s; ret = ret->ch[0]);
                erase(x->ch[1], x->v = ret->v);
            }
        } else {
            erase(x->ch[d], p);
        }
        if(x->s) x->push_up();
    }
    inline void insert(int v) {
        insert(root, v);
    }
    inline void erase() {
        erase(root, kth(1));
    }
    inline int kth(int k) {
        Node *x = root;
        for (int t = 0; x->s; ) {
            t = x->ch[0]->s;
            if (k <= t) x = x->ch[0];
            else if (t + 1 <= k && k <= t + x->c) break;
            else k -= t + x->c, x = x->ch[1];
        }
        return x->v;
    }
    inline void query() {
        if(!root->s) { puts("0"); return; }
        printf("%d\n", kth(root->s));
    }
}sbt;
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    sbt.init();
    int n, v, op;
    while(~scanf("%d", &n)) {
        sbt.init();
        rep(i, n) {
            op = read();
            if(1 == op) v = read(), sbt.insert(v);
            if(2 == op) sbt.erase();
            if(3 == op) sbt.query();
        }
    }
    return 0;
}
