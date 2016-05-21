#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
const int Max_N = 1100;
struct Node{
    int v, s;
    Node *pre, *ch[2];
    inline void set(int _v = 0, int _s = 0, Node *p = NULL){
        v = _v, s = _s;
        pre = ch[0] = ch[1] = p;
    }
    inline  void push_up(){
        s = ch[0]->s + ch[1]->s + 1;
    }
    inline void link(Node *x, bool d){
        ch[d] = x;
        x->pre = this;
    }
};
struct SplayTree{
    Node *tail, *root, *null;
    Node stack[Max_N], *ptr[Max_N];
    void init(){
        tail = &stack[0];
        null = tail++;
        null->set();
        root = null;
    }
    inline  Node *newNode(int v){
        Node *p = tail++;
        p->set(v, 1, null);
        return p;
    }
    inline void rotate(Node *x, int d){
        Node *y = x->pre;
        y->ch[!d] = x->ch[d];
        if (x->ch[d] != null) x->ch[d]->pre = y;
        x->pre = y->pre;
        if (y->pre != null) y->pre->ch[y->pre->ch[0] != y] = x;
        x->ch[d] = y;
        y->pre = x;
        y->push_up(), x->push_up();
        if (y == root) root = x;
    }
    inline void update(Node *x){
        if (x != null){
            update(x->ch[0]);
            update(x->ch[1]);
            x->push_up();
        }
    }
    void gogo(int n){
        int i, a, b;
        for (i = 0; i <= n; i++) ptr[i] = newNode(i);
        for (i = 1; i <= n; i++){
            scanf("%d %d", &a, &b);
            if (-1 == a || -1 == b){
                if (-1 == a && b != -1) ptr[i]->link(ptr[b], 1);
                if (-1 == b && a != -1) ptr[i]->link(ptr[a], 0);
            } else {
                ptr[i]->link(ptr[a], 0);
                ptr[i]->link(ptr[b], 1);
            }
            ptr[i]->push_up();
            if (ptr[i]->pre == null) root = ptr[i];
        }
        update(root);
    }
    inline void work(){
        int i, t;
        char buf[50];
        scanf("%d", &t);
        while (t--){
            scanf("%s %d", buf, &i);
            if ('s' == buf[0]){
                printf("%d\n", ptr[i]->s);
            } else if ('r' == buf[0]){
                if (ptr[i] == root) continue;
                rotate(ptr[i], ptr[i]->pre->ch[0] == ptr[i]);
            } else {
                if (ptr[i] == root) printf("-1\n");
                else printf("%d\n", ptr[i]->pre->v);
            }
        }
    }
}spt;
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n;
    while (~scanf("%d", &n)){
        spt.init(), spt.gogo(n), spt.work();
    }
    return 0;
}
