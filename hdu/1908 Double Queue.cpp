#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
#include<set>
using std::cin;
using std::cout;
using std::endl;
using std::find;
using std::set;
using std::map;
using std::pair;
using std::vector;
using std::multiset;
using std::multimap;
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)
const int Max_N = 200010;
typedef unsigned long long ull;
struct Node {
    int data, s, client;
    bool color;
    Node *fa, *ch[2];
    inline void setc(int _v, int c, int i, bool _color, Node *ptr) {
        data = _v, color = _color, s = i, client = c;
        fa = ch[0] = ch[1] = ptr;
    }
    inline void push_up() {
        s = ch[0]->s + ch[1]->s + 1;
    }
    inline void push_down() {
        for (Node *x = this; x->s; x = x->fa) x->s--;
    }
};
struct RedBlackTree {
    int top;
    Node *root, *null;
    Node stack[Max_N], *tail, *pool[Max_N];
    inline void init() {
        top = 0;
        tail = &stack[0];
        null = tail++;
        null->setc(0, 0, 0, 0, NULL);
        root = null;
    }
    inline Node *newNode(int v, int client) {
        Node *x = !top ? tail++ : pool[--top];
        x->setc(v, client, 1, 1, null);
        return x;
    }
    inline void rotate(Node* &x, bool d) {
        Node *y = x->ch[!d];
        x->ch[!d] = y->ch[d];
        if (y->ch[d] != null) y->ch[d]->fa = x;
        y->fa = x->fa;
        if (x->fa == null) root = y;
        else x->fa->ch[x->fa->ch[0] != x] = y;
        y->ch[d] = x;
        x->fa = y;
        y->s = x->s;
        x->push_up();
    }
    inline void insert(int v, int client)  {
        Node *x = root, *y = null;
        while (x->s) {
            x->s++;
            y = x, x = x->ch[v > x->data];
        }
        x = newNode(v, client);
        if (y != null) y->ch[v > y->data] = x;
        else root = x;
        x->fa = y;
        insert_fix(x);
    }
    inline void insert_fix(Node* &x) {
        while (x->fa->color) {
            Node *par = x->fa, *Gp = par->fa;
            bool d = par == Gp->ch[0];
            Node *uncle = Gp->ch[d];
            if (uncle->color) {
                par->color = uncle->color = 0;
                Gp->color = 1;
                x = Gp;
            } else if (x == par->ch[d]) {
                rotate(x = par, !d);
            } else {
                Gp->color = 1;
                par->color = 0;
                rotate(Gp, d);
            }
        }
        root->color = 0;
    }
    inline Node *find(Node *x, int data) {
        while (x->s && x->data != data) x = x->ch[x->data < data];
        return x;
    }
    inline void erase_fix(Node* &x) {
        while (x != root && !x->color) {
            bool d = x == x->fa->ch[0];
            Node *par = x->fa, *sibling = par->ch[d];
            if (sibling->color) {
                sibling->color = 0;
                par->color = 1;
                rotate(x->fa, !d);
                sibling = par->ch[d];
            } else if (!sibling->ch[0]->color && !sibling->ch[1]->color) {
                sibling->color = 1, x = par;
            } else {
                if (!sibling->ch[d]->color) {
                    sibling->ch[!d]->color = 0;
                    sibling->color = 1;
                    rotate(sibling, d);
                    sibling = par->ch[d];
                }
                sibling->color = par->color;
                sibling->ch[d]->color = par->color = 0;
                rotate(par, !d);
                break;
            }
        }
        x->color = 0;
    }
    inline void erase(int data) {
        Node *z = find(root, data);
        if (!z->s) return;
        Node *y = z, *x = null;
        if (z->ch[0]->s && z->ch[1]->s) {
            y = z->ch[1];
            while (y->ch[0]->s) y = y->ch[0];
        }
        x = y->ch[!y->ch[0]->s];
        x->fa = y->fa;
        if (!y->fa->s) root = x;
        else y->fa->ch[y->fa->ch[1] == y] = x;
        if (z != y) z->data = y->data, z->client = y->client;
        y->fa->push_down();
        if (!y->color) erase_fix(x);
        pool[top++] = y;
    }
    inline Node *kth(int k) {
        int t = 0;
        Node *x = root;
        for (; x->s;){
            t = x->ch[0]->s;
            if (k == t + 1) break;
            else if (k <= t) x = x->ch[0];
            else k -= t + 1, x = x->ch[1];
        }
        return x;
    }
    inline Node *operator[](int k) {
        return kth(k);
    }
    inline void go(int n) {
        int a, b;
        Node *ret = null;
        if (2 == n || 3 == n) {
            if (2 == n && root->s) ret = rbt[root->s];
            else if (3 == n && root->s) ret = rbt[1];
            if (!ret->s) printf("0\n");
            else printf("%d\n", ret->client), erase(ret->data);
        } else {
            scanf("%d %d", &a, &b);
            insert(b, a);
        }
    }
}rbt;
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n;
    rbt.init();
    while (~scanf("%d", &n) && n) {
        rbt.go(n);
    }
    return 0;
}


#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
#include<set>
using std::cin;
using std::cout;
using std::endl;
using std::find;
using std::set;
using std::map;
using std::pair;
using std::vector;
using std::multiset;
using std::multimap;
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)
const int Max_N = 200010;
typedef unsigned long long ull;
struct Node {
    int v, p, s;
    Node *ch[2];
    inline void setc(int _v, int _p, int _s, Node *ptr) {
        v = _v, s = _s, p = _p;
        ch[0] = ch[1] = ptr;
    }
    inline void push_up() {
        s = ch[0]->s + ch[1]->s + 1;
    }
    inline int cmp(int x) const {
        return p == x ? -1 : x > p;
    }
};
struct SBT {
    int top;
    Node *null, *root, *tail;
    Node stack[Max_N], *pool[Max_N];
    inline void init() {
        top = 0;
        tail = &stack[0];
        null = tail++;
        null->setc(0, 0, 0, NULL);
        root = null;
    }
    inline Node *newNode(int v, int p) {
        Node *x = !top ? tail++ : pool[--top];
        x->setc(v, p, 1, null);
        return x;
    }
    inline void rotate(Node *&x, int d) {
        Node *k = x->ch[!d]; x->ch[!d] = k->ch[d], k->ch[d] = x;
        k->s = x->s;
        x->push_up();
        x = k;
    }
    inline void Maintain(Node *&x, int d) {
        if (!x->s) return;
        if (x->ch[d]->ch[d]->s > x->ch[!d]->s) rotate(x, !d);
        else if (x->ch[d]->ch[!d]->s > x->ch[!d]->s) rotate(x->ch[d], d), rotate(x, !d);
        else return;
        Maintain(x, 0), Maintain(x, 1);
    }
    inline void insert(Node *&x, int v, int p) {
        if (!x->s) { x = newNode(v, p); return; }
        x->s++;
        int d = x->cmp(p);
        insert(x->ch[d], v, p);
        x->push_up();
        Maintain(x, d);
    }
    inline void erase(Node *&x, int p) {
        if (!x->s) return;
        x->s--;
        int d = x->cmp(p);
        if (-1 == d) {
            if (!x->ch[0]->s || !x->ch[1]->s) {
                pool[top++] = x;
                x = x->ch[0]->s ? x->ch[0] : x->ch[1];
            } else {
                Node *ret = x->ch[1];
                for (; ret->ch[0]->s; ret = ret->ch[0]);
                x->v = ret->v, x->p = ret->p;
                erase(x->ch[1], x->p);
            }
        } else {
            erase(x->ch[d], p);
        }
    }
    inline Node *kth(int k){
        int t = 0;
        Node *x = root;
        for (; x->s;){
            t = x->ch[0]->s;
            if (k == t + 1) break;
            else if (k <= t) x = x->ch[0];
            else k -= t + 1, x = x->ch[1];
        }
        return x;
    }
    inline Node *operator[](int k) {
        return kth(k);
    }
    inline void go(int n) {
        int a, b;
        Node *ret = null;
        if (2 == n || 3 == n) {
            if (2 == n && root->s) ret = sbt[root->s];
            else if (3 == n && root->s) ret = sbt[1];
            if (!ret->s) printf("0\n");
            else printf("%d\n", ret->v), erase(root, ret->p);
        } else {
            scanf("%d %d", &a, &b);
            insert(root, a, b);
        }
    }
}sbt;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n;
    sbt.init();
    while (~scanf("%d", &n) && n) {
        sbt.go(n);
    }
    return 0;
}
