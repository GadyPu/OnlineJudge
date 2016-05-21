#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using std::sort;
using std::swap;
const int Max_N = 100010;
struct node{
    int val, pos;
}rec[100001];
inline bool cmp(const node &a, const node &b){
    if (a.val == b.val) return a.pos < b.pos;
    return a.val < b.val;
}
struct Node{
    int v, s, rsz, rev;
    Node *pre, *ch[2];
    inline void set(int _v = -1, int _s = 0, Node *p = NULL){
        v = _v, s = _s, rev = rsz = 0;
        pre =  ch[0] = ch[1] = p;
    }
    inline void update(){
        rev ^= 1;
        swap(ch[0], ch[1]);
    }
    inline void push_up(){
        s = ch[0]->s + ch[1]->s + 1;
        rsz = ch[0]->rsz + ch[1]->rsz;
        if (v != -1) rsz++;
    }
    inline void push_down(){
        if (rev != 0){
            rev ^= 1;
            ch[0]->update();
            ch[1]->update();
        }
    }
};
struct SplayTree{
    int top = 0;
    Node *tail, *root, *null;
    Node stack[Max_N], *store[Max_N], *ptr[Max_N];
    void init(int n){
        top = 0;
        tail = &stack[0];
        null = tail++;
        null->set();
        root = newNode(-1);
        root->ch[1] = newNode(-1);
        root->ch[1]->pre = root;
        Node *x = built(1, n);
        root->ch[1]->ch[0] = x;
        x->pre = root->ch[1];
        root->ch[1]->push_up();
        root->push_up();
    }
    inline Node *built(int l, int r){
        Node *p = null;
        if (l > r) return null;
        int mid = (l + r) >> 1;
        p = newNode(rec[mid].val), ptr[mid] = p;
        p->ch[0] = built(l, mid - 1);
        if (p->ch[0] != null) p->ch[0]->pre = p;
        p->ch[1] = built(mid + 1, r);
        if (p->ch[1] != null) p->ch[1]->pre = p;
        p->push_up();
        return p;
    }
    inline Node *newNode(int v){
        Node *p = null;
        if (!top) p = tail++;
        else p = store[--top];
        p->set(v, 1, null);
        return p;
    }
    inline void rotate(Node *x, int d){
        Node *y = x->pre;
        y->push_down(), x->push_down();
        y->ch[!d] = x->ch[d];
        if (x->ch[d] != null) x->ch[d]->pre = y;
        x->pre = y->pre;
        if (y->pre != null) y->pre->ch[y->pre->ch[0] != y] = x;
        x->ch[d] = y;
        y->pre = x;
        y->push_up();
        if (y == root) root = x;
    }
    inline void splay(Node *x, Node *f){
        for (; x->pre != f; x->push_down()){
            if (x->pre->pre == f){
                rotate(x, x->pre->ch[0] == x);
            } else {
                Node *y = x->pre, *z = y->pre;
                if (z->ch[0] == y){
                    if (y->ch[0] == x) rotate(y, 1), rotate(x, 1);
                    else rotate(x, 0), rotate(x, 1);
                } else {
                    if (y->ch[1] == x) rotate(y, 0), rotate(x, 0);
                    else rotate(x, 1), rotate(x, 0);
                }
            }
        }
        x->push_up();
    }
    inline Node *select(Node *x, int k){
        int t = 0;
        for (;;){
            x->push_down();
            t = x->ch[0]->s;
            if (k == t + 1) break;
            else if (k < t + 1) x = x->ch[0];
            else k -= t + 1, x = x->ch[1];
        }
        return x;
    }
    inline void del(){
        Node *x = root;
        store[top++] = x;
        root = root->ch[1];
        root->pre = null;
        splay(select(root, 1), null);
        root->ch[0] = x->ch[0];
        root->ch[0]->pre = root;
        root->push_up();
    }
    inline void solve(int n) {
        const int N = n + 2;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &rec[i].val);
            rec[i].pos = i;
        }
        init(n), sort(rec + 1, rec + n + 1, cmp);
        splay(root->ch[1], null);
        for (int i = 1; i <= n; i++){
            splay(ptr[rec[i].pos], null);
            root->ch[0]->update();
            printf("%d", root->ch[0]->rsz + i);
            if (i != n) printf(" ");
            del();
        }
        printf("\n");
    }
}spt;
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n;
    while (~scanf("%d", &n) && n) {
        spt.solve(n);
    }
    return 0;
}
