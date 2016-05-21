/************************
*
*     Red Balck Tree
*
*************************/
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<queue>
using std::queue;
const int Max_N = 10010;
struct Node {
    int data, s;
    bool color;
    Node *fa, *ch[2];
    inline void set(int _v, int i, bool _color, Node *p) {
        data = _v, color = _color, s = i;
        fa = ch[0] = ch[1] = p;
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
    Node stack[Max_N], *tail, *store[Max_N];
    void init() {
        tail = &stack[0];
        null = tail++;
        null->set(0, 0, 0, NULL);
        root = null;
        top = 0;
    }
    inline Node *newNode(int v) {
        Node *p = null;
        if (!top) p = tail++;
        else p = store[--top];
        p->set(v, 1, 1, null);
        return p;
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
    inline void insert(int v)  {
        Node *x = root, *y = null;
        while (x->s){
            x->s++;
            y = x, x = x->ch[v > x->data];
        }
        x = newNode(v);
        if (y != null) y->ch[v > y->data] = x;
        else root = x;
        x->fa = y;
        insert_fix(x);
    }
    inline void insert_fix(Node* &x) {
        while (x->fa->color){
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
    inline void del_fix(Node* &x) {
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
    inline void del(int data) {
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
        if (z != y) z->data = y->data;
        y->fa->push_down();
        if (!y->color) del_fix(x);
        store[top++] = y;
    }
    inline int kth(int k) {
        int t = 0;
        Node *x = root;
        for (; x->s;){
            t = x->ch[0]->s;
            if (k == t + 1) break;
            else if (k <= t) x = x->ch[0];
            else k -= t + 1, x = x->ch[1];
        }
        return x->data;
    }
    int operator[] (int k) {
        return kth(k);
    }
}rbt;
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, v, c = 1;
    char buf[100];
    while (~scanf("%d", &n)) {
        rbt.init(); queue<int> q;
        printf("Case #%d:\n", c++);
        while (n--) {
            scanf("%s", buf);
            if ('i' == buf[0]) {
                scanf("%d", &v);
                rbt.insert(v), q.push(v);
            } else if ('o' == buf[0]) {
                v = q.front(); q.pop();
                rbt.del(v);
            } else {
                printf("%d\n", rbt[((int)q.size() >> 1) + 1]);
            }
        }
    }
    return 0;
}
/************************
*
*    Size Balance Tree
*
*************************/
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<queue>
using std::queue;
const int Max_N = 10010;
struct Node {
    int v, s;
    Node *ch[2];
    inline void set(int _v, int _s, Node *p) {
        v = _v, s = _s;
        ch[0] = ch[1] = p;
    }
    inline void push_up() {
        s = ch[0]->s + ch[1]->s + 1;
    }
    inline int cmp(int x) const {
        return x == v ? -1 : x > v;
    }
};
struct SizeBalanceTree {
    Node stack[Max_N];
    Node *root, *null, *tail;
    Node *store[Max_N];
    int top;
    void init() {
        tail = &stack[0];
        null = tail++;
        null->set(0, 0, NULL);
        root = null;
        top = 0;
    }
    inline Node *newNode(int v) {
        Node *p = null;
        if (top) p = store[--top];
        else p = tail++;
        p->set(v, 1, null);
        return p;
    }
    inline void rotate(Node* &x, int d) {
        Node *k = x->ch[!d];
        x->ch[!d] = k->ch[d];
        k->ch[d] = x;
        k->s = x->s;
        x->push_up();
        x = k;
    }
    inline void Maintain(Node* &x, int d) {
        if (x->ch[d] == null) return;
        if (x->ch[d]->ch[d]->s > x->ch[!d]->s) {
            rotate(x, !d);
        } else if (x->ch[d]->ch[!d]->s > x->ch[!d]->s) {
            rotate(x->ch[d], d), rotate(x, !d);
        } else {
            return;
        }
        Maintain(x, 0), Maintain(x, 1);
    }
    inline void insert(Node* &x, int v) {
        if (x == null) {
            x = newNode(v);
            return;
        } else {
            x->s++;
            int d = x->cmp(v);
            insert(x->ch[d], v);
            x->push_up();
            Maintain(x, d);
        }
    }
    inline void del(Node*  &x, int v) {
        if (!x->s) return;
        x->s--;
        int d = x->cmp(v);
        if (-1 == d) {
            if (!x->ch[0]->s || !x->ch[1]->s) {
                store[top++] = x;
                x = x->ch[0]->s ? x->ch[0] : x->ch[1];
            } else {
                Node *ret = x->ch[1];
                for (; ret->ch[0] != null; ret = ret->ch[0]);
                del(x->ch[1], x->v = ret->v);
            }
        } else {
            del(x->ch[d], v);
        }
        if (x->s) x->push_up();
    }
    inline void insert(int v) {
        insert(root, v);
    }
    inline void del(int v) {
        del(root, v);
    }
    inline int kth(int k) {
        int t;
        Node *x = root;
        for (; x->s;) {
            t = x->ch[0]->s;
            if (k <= t) x = x->ch[0];
            else if (t + 1 == k) break;
            else k -= t + 1, x = x->ch[1];
        }
        return x->v;
    }
    int operator[] (int k) {
        return kth(k);
    }
}sbt;
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, v, c = 1;
    char buf[100];
    while (~scanf("%d", &n)) {
        sbt.init(); queue<int> q;
        printf("Case #%d:\n", c++);
        while (n--) {
            scanf("%s", buf);
            if ('i' == buf[0]) {
                scanf("%d", &v);
                sbt.insert(v), q.push(v);
            } else if ('o' == buf[0]) {
                v = q.front(); q.pop();
                sbt.del(v);
            } else {
                printf("%d\n", sbt[((int)q.size() >> 1) + 1]);
            }
        }
    }
    return 0;
}
