/*
* this code is made by Bug_Pu
* Problem: 1738
* Verdict: Accepted
* Submission Date: 2015-05-19 19:26:48
* Time: 420MS
* Memory: 40160KB
*/
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#define lc root<<1
#define rc root<<1|1
const int Max_N = 50010;
const int INF = ~0u >> 1;
struct Node {
    int data, s, c;
    bool color;
    Node *fa, *ch[2];
    inline void set(int _v, bool _color, int i, Node *p) {
        data = _v, color = _color, s = c = i;
        fa = ch[0] = ch[1] = p;
    }
    inline void push_up() {
        s = ch[0]->s + ch[1]->s + c;
    }
    inline void push_down() {
        for (Node *x = this; x->s; x = x->fa) x->s--;
    }
    inline int cmp(int v) const {
        return data == v ? -1 : v > data;
    }
};
struct RedBlackTree {
    int top, ans, tot, sum, arr[Max_N];
    Node *null, *tail;
    Node stack[Max_N * 18], *store[Max_N << 2], *ptr[Max_N << 2];
    inline void init(int n) {
        top = 0;
        tail = &stack[0];
        null = tail++;
        null->set(0, 0, 0, NULL);
        for (int i = 1; i <= n; i++) scanf("%d", &arr[i]);
        seg_built(1, 1, n);
    }
    inline Node *newNode(int v) {
        Node *p = null;
        if (!top) p = tail++;
        else p = store[--top];
        p->set(v, 1, 1, null);
        return p;
    }
    inline void rotate(int root, Node* &x, bool d) {
        Node *y = x->ch[!d];
        x->ch[!d] = y->ch[d];
        if (y->ch[d]->s) y->ch[d]->fa = x;
        y->fa = x->fa;
        if (!x->fa->s) ptr[root] = y;
        else x->fa->ch[x->fa->ch[0] != x] = y;
        y->ch[d] = x;
        x->fa = y;
        y->s = x->s;
        x->push_up();
    }
    inline void insert(int root, int v) {
        Node *x = ptr[root], *y = null;
        while (x->s) {
            x->s++, y = x;
            int d = x->cmp(v);
            if (-1 == d) {
                x->c++;
                return;
            }
            x = x->ch[d];
        }
        x = newNode(v);
        if (y->s) y->ch[v > y->data] = x;
        else ptr[root] = x;
        x->fa = y;
        insert_fix(root, x);
    }
    inline void insert_fix(int root, Node* &x) {
        while (x->fa->color) {
            Node *par = x->fa, *Gp = par->fa;
            bool d = par == Gp->ch[0];
            Node *uncle = Gp->ch[d];
            if (uncle->color) {
                par->color = uncle->color = 0;
                Gp->color = 1;
                x = Gp;
            } else if (x == par->ch[d]) {
                rotate(root, x = par, !d);
            } else {
                Gp->color = 1;
                par->color = 0;
                rotate(root, Gp, d);
            }
        }
        ptr[root]->color = 0;
    }
    inline Node *find(Node *x, int data) {
        while (x->s && x->data != data) x = x->ch[x->data < data];
        return x;
    }
    inline void del_fix(int root, Node* &x) {
        while (x != ptr[root] && !x->color) {
            bool d = x == x->fa->ch[0];
            Node *par = x->fa, *sibling = par->ch[d];
            if (sibling->color) {
                sibling->color = 0;
                par->color = 1;
                rotate(root, x->fa, !d);
                sibling = par->ch[d];
            } else if (!sibling->ch[0]->color && !sibling->ch[1]->color) {
                sibling->color = 1, x = par;
            } else {
                if (!sibling->ch[d]->color) {
                    sibling->ch[!d]->color = 0;
                    sibling->color = 1;
                    rotate(root, sibling, d);
                    sibling = par->ch[d];
                }
                sibling->color = par->color;
                sibling->ch[d]->color = par->color = 0;
                rotate(root, par, !d);
                break;
            }
        }
        x->color = 0;
    }
    inline void del(int root, int data) {
        Node *z = find(ptr[root], data);
        if (!z->s) return;
        if (z->c > 1) {
            z->c--;
            z->push_down();
            return;
        }
        Node *y = z, *x = null;
        if (z->ch[0]->s && z->ch[1]->s) {
            y = z->ch[1];
            while (y->ch[0]->s) y = y->ch[0];
        }
        x = y->ch[!y->ch[0]->s];
        x->fa = y->fa;
        if (!y->fa->s) ptr[root] = x;
        else y->fa->ch[y->fa->ch[1] == y] = x;
        if (z != y) z->data = y->data, z->c = y->c;
        y->fa->push_down();
        for (Node *k = y->fa; y->c > 1 && k->s && k != z; k = k->fa) k->s -= y->c - 1;
        if (!y->color) del_fix(root, x);
        store[top++] = y;
    }
    inline Node* get_min(Node *x) {
        for (; x->ch[0]->s; x = x->ch[0]);
        return x;
    }
    inline int count(Node *x, int v) {
        int res = 0, t = 0;
        for (; x->s;) {
            t = x->ch[0]->s;
            if (v < x->data) x = x->ch[0];
            else res += t + x->c, x = x->ch[1];
        }
        return res;
    }
    inline void seg_built(int root, int l, int r) {
        ptr[root] = null;
        for (int i = l; i <= r; i++) insert(root, arr[i]);
        if (l == r) return;
        int mid = (l + r) >> 1;
        seg_built(lc, l, mid);
        seg_built(rc, mid + 1, r);
    }
    inline void seg_modify(int root, int l, int r, int pos, int v){
        if (pos > r || pos < l) return;
        del(root, arr[pos]);
        insert(root, v);
        if (l == r) return;
        int mid = (l + r) >> 1;
        seg_modify(lc, l, mid, pos, v);
        seg_modify(rc, mid + 1, r, pos, v);
    }
    inline void seg_query_min(int root, int l, int r, int x, int y) {
        if (x > r || y < l) return;
        if (x <= l && y >= r) {
            Node *ret = get_min(ptr[root]);
            if (ret->data < ans) ans = ret->data;
            return;
        }
        int mid = (l + r) >> 1;
        seg_query_min(lc, l, mid, x, y);
        seg_query_min(rc, mid + 1, r, x, y);
    }
    inline void seg_query_tot(int root, int l, int r, int x, int y, int val) {
        if (x > r || y < l) return;
        if (x <= l && y >= r) {
            tot += find(ptr[root], val)->c;
            return;
        }
        int mid = (l + r) >> 1;
        seg_query_tot(lc, l, mid, x, y, val);
        seg_query_tot(rc, mid + 1, r, x, y, val);
    }
    inline void seg_query_count(int root, int l, int r, int x, int y, int val) {
        if (x > r || y < l) return;
        if (x <= l && y >= r) {
            sum += count(ptr[root], val);
            return;
        }
        int mid = (l + r) >> 1;
        seg_query_count(lc, l, mid, x, y, val);
        seg_query_count(rc, mid + 1, r, x, y, val);
    }
    inline void gogo(int n) {
        int a, b, c, d;
        scanf("%d", &a);
        if (1 == a) {
            scanf("%d %d", &b, &c);
            seg_modify(1, 1, n, b, c), arr[b] = c;
        } else if (2 == a) {
            ans = INF, tot = 0;
            scanf("%d %d", &b, &c);
            seg_query_min(1, 1, n, b, c);
            seg_query_tot(1, 1, n, b, c, ans);
            printf("%d %d\n", ans, tot);
        } else {
            sum = 0;
            scanf("%d %d %d", &b, &c, &d);
            seg_query_count(1, 1, n, b, c, d);
            printf("%d\n", sum);
        }
    }
}rbt;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, m;
    while (~scanf("%d %d", &n, &m)) {
        rbt.init(n);
        while (m--) rbt.gogo(n);
    }
    return 0;
}



/*
* this code is made by Bug_Pu
* Problem: 1738
* Verdict: Accepted
* Submission Date: 2015-05-19 18:59:53
* Time: 508MS
* Memory: 33128KB
*/
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#define lc root<<1
#define rc root<<1|1
using std::sort;
using std::lower_bound;
using std::upper_bound;
const int Max_N = 50010;
const int INF = ~0u >> 1;
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
    int top, ans, tot, sum, arr[Max_N];
    Node *null, *tail, stack[Max_N * 18];
    Node *store[Max_N << 2], *ptr[Max_N << 2];
    inline void init(int n) {
        top = 0; 
        tail = &stack[0];
        null = tail++;
        null->set(0, 0, NULL);
        for (int i = 1; i <= n; i++) scanf("%d", &arr[i]);
        seg_built(1, 1, n);
    }
    inline Node *newNode(int v) {
        Node *p = null;
        if (!top) p = tail++;
        else p = store[--top];
        p->set(v, 1, null);
        return p;
    }
    inline void rotate(Node *&x, int d) {
        Node *k = x->ch[!d];
        x->ch[!d] = k->ch[d];
        k->ch[d] = x;
        k->s = x->s;
        x->push_up();
        x = k;
    }
    inline void Maintain(Node *&x, int d) {
        if (!x->ch[d]->s) return;
        if (x->ch[d]->ch[d]->s > x->ch[!d]->s) {
            rotate(x, !d);
        } else if (x->ch[d]->ch[!d]->s > x->ch[!d]->s) {
            rotate(x->ch[d], d), rotate(x, !d);
        } else {
            return;
        }
        Maintain(x, 0), Maintain(x, 1);
    }
    inline void insert(Node *&x, int v) {
        if (x == null) {
            x = newNode(v);
            return;
        } else {
            x->s++;
            int d = x->cmp(v);
            if (-1 == d) {
                x->c++;
                return;
            }
            insert(x->ch[d], v);
            x->push_up();
            Maintain(x, d);
        }
    }
    inline void del(Node *&x, int v) {
        if (!x->s) return;
        x->s--;
        int d = x->cmp(v);
        if (-1 == d) {
            if (x->c > 1) {
                x->c--;
                return;
            } else if (!x->ch[0]->s || !x->ch[1]->s) {
                store[top++] = x;
                x = x->ch[0]->s ? x->ch[0] : x->ch[1];
            } else {
                Node *ret = x->ch[1];
                for (; ret->ch[0]->s; ret = ret->ch[0]);
                del(x->ch[1], x->v = ret->v);
            }
        } else {
            del(x->ch[d], v);
        }
        if (x->s) x->push_up();
    }
    inline Node *get_min(Node *x) {
        for (; x->ch[0]->s; x = x->ch[0]);
        return x;
    }
    inline int find(Node *x, int v) {
        while (x->s && x->v != v) x = x->ch[v > x->v];
        return x->c;
    }
    inline int count(Node *x, int v) {
        int res = 0, t = 0;
        for (; x->s;) {
            t = x->ch[0]->s;
            if (v < x->v) x = x->ch[0];
            else res += t + x->c, x = x->ch[1];
        }
        return res;
    }
    inline void seg_built(int root, int l, int r) {
        ptr[root] = null;
        for (int i = l; i <= r; i++) insert(ptr[root], arr[i]);
        if (l == r) return;
        int mid = (l + r) >> 1;
        seg_built(lc, l, mid);
        seg_built(rc, mid + 1, r);
    }
    inline void seg_modify(int root, int l, int r, int pos, int v){
        if (pos > r || pos < l) return;
        del(ptr[root], arr[pos]);
        insert(ptr[root], v);
        if (l == r) return;
        int mid = (l + r) >> 1;
        seg_modify(lc, l, mid, pos, v);
        seg_modify(rc, mid + 1, r, pos, v);
    }
    inline void seg_query_min(int root, int l, int r, int x, int y) {
        if (x > r || y < l) return;
        if (x <= l && y >= r) {
            Node *ret = get_min(ptr[root]);
            if (ret->v < ans) ans = ret->v;
            return;
        }
        int mid = (l + r) >> 1;
        seg_query_min(lc, l, mid, x, y);
        seg_query_min(rc, mid + 1, r, x, y);
    }
    inline void seg_query_tot(int root, int l, int r, int x, int y, int val) {
        if (x > r || y < l) return;
        if (x <= l && y >= r) {
            tot += find(ptr[root], val);
            return;
        }
        int mid = (l + r) >> 1;
        seg_query_tot(lc, l, mid, x, y, val);
        seg_query_tot(rc, mid + 1, r, x, y, val);
    }
    inline void seg_query_count(int root, int l, int r, int x, int y, int val) {
        if (x > r || y < l) return;
        if (x <= l && y >= r) {
            sum += count(ptr[root], val);   
            return;
        }
        int mid = (l + r) >> 1;
        seg_query_count(lc, l, mid, x, y, val);
        seg_query_count(rc, mid + 1, r, x, y, val);
    }
    inline void gogo(int n) {
        int a, b, c, d;
        scanf("%d", &a);
        if (1 == a) {
            scanf("%d %d", &b, &c);
            seg_modify(1, 1, n, b, c), arr[b] = c;
        } else if (2 == a) {
            ans = INF, tot = 0;
            scanf("%d %d", &b, &c);
            seg_query_min(1, 1, n, b, c);
            seg_query_tot(1, 1, n, b, c, ans);
            printf("%d %d\n", ans, tot);
        } else {
            sum = 0;
            scanf("%d %d %d", &b, &c, &d);
            seg_query_count(1, 1, n, b, c, d);
            printf("%d\n", sum);
        }
    }
}sbt;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif;
    int n, m;
    while (~scanf("%d %d", &n, &m)) {
        sbt.init(n);
        while (m--) sbt.gogo(n);
    }
    return 0;
}
