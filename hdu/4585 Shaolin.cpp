#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
const int Max_N = 101000;
const int INF = 0x7fffffff;
struct Node{
    int v, id, s;
    Node *ch[2];
    inline void
    set(int _v = 0, int _id = 0, int _s = 0, Node *p = NULL){
        ch[0] = ch[1] = p;
        v = _v, id = _id, s = _s;
    }
    inline void push_up(){
        s = ch[0]->s + ch[1]->s + 1;
    }
    inline int cmp(int x) const{
        return x > v;
    }
};
struct SizeBalanceTree{
    Node *tail, *root, *null;
    Node stack[Max_N];
    void init(){
        tail = &stack[0];
        null = tail++;
        null->set();
        root = null;
    }
    inline Node *newNode(int v, int id){
        Node *p = tail++;
        p->set(v, id, 1, null);
        return p;
    }
    inline void rotate(Node* &x, int d){
        Node *k = x->ch[!d];
        x->ch[!d] = k->ch[d];
        k->ch[d] = x;
        k->s = x->s;
        x->push_up();
        x = k;
    }
    inline void Maintain(Node* &x, int d){
        if (x->ch[d] == null) return;
        if (x->ch[d]->ch[d]->s > x->ch[!d]->s){
            rotate(x, !d);
        } else if (x->ch[d]->ch[!d]->s > x->ch[!d]->s){
            rotate(x->ch[d], d), rotate(x, !d);
        } else {
            return;
        }
        Maintain(x, 0), Maintain(x, 1);
    }
    inline void insert(Node* &x, int v, int id){
        if (x == null){
            x = newNode(v, id);
            return;
        } else {
            x->s++;
            int d = x->cmp(v);
            insert(x->ch[d], v, id);
            x->push_up();
            Maintain(x, d);
        }
    }
    inline void insert(int v, int id){
        insert(root, v, id);
    }
    inline Node *select(Node *x, int v, int dx){
        Node *pre = null;
        while (x != null && x->v != v){
            int d = x->cmp(v);
            if (d == !dx) pre = x;
            x = x->ch[d];
        }
        x = x->ch[dx];
        if (x == null){
            return pre;
        } else {
            while (x->ch[!dx] != null) x = x->ch[!dx];
            return x;
        }
    }
    inline int calc(Node *r, int k) {
        if (r == null) return INF;
        return std::abs(r->v - k);
    }
    inline void gogo(int id, int v){
        int ans = 0;
        Node *k1 = select(root, v, 0);
        Node *k2 = select(root, v, 1);
        int d1 = calc(k1, v), d2 = calc(k2, v);
        ans = d1 > d2 ? k2->id : k1->id;
        printf("%d %d\n", id, ans);
    }
}sbt;
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, id, v;
    while (~scanf("%d", &n) && n){
        sbt.init();
        sbt.insert((int)1e9, 1);
        for (int i = 0; i < n; i++){
            scanf("%d %d", &id, &v);
            sbt.insert(v, id);
            sbt.gogo(id, v);
        }
    }
    return 0;
}
