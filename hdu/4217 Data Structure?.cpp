#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
typedef long long ll;
const int MAX_N = 300100;
struct Node{
    int v, s, fix;
    Node *ch[2];
    inline void set(int _fix, int _v = 0, int _s = 0, Node *p = NULL){
        fix = _fix, v = _v, s = _s;
        ch[0] = ch[1] = p;
    }
    inline void push_up(){
        s = ch[0]->s + ch[1]->s + 1;
    }
};
int run(){
    static int x = 184082857;
    x += (x << 2) | 1;
    return x;
}
struct Treap{
    Node *tail, *null, *root;
    Node stack[MAX_N];
    int top;
    Node *store[MAX_N];
    void init(){
        tail = &stack[0];
        null = tail++;
        null->set(0x7fffffff);
        root = null;
        top = 0;
    }
    Node *newNode(int v){
        Node *p = null;
        if (top) p = store[--top];
        else p = tail++;
        p->set(run(), v, 1, null);
        return p;
    }
    void rotate(Node* &x, int d){
        Node *k = x->ch[!d];
        x->ch[!d] = k->ch[d];
        k->ch[d] = x;
        k->s = x->s;
        x->push_up();
        x = k;
    }
    void insert(Node* &x, int v){
        if (x == null){
            x = newNode(v);
            return;
        } else {
            int d = v > x->v;
            insert(x->ch[d], v);
            if (x->ch[d]->fix < x->fix) rotate(x, !d);
            x->push_up();
        }
    }
    void del(Node* &x, int v){
        if (x == null) return;
        x->s--;
        if (x->v == v){
            if (x->ch[0] == null || x->ch[1] == null){
                store[top++] = x;
                x = x->ch[0] == null ? x->ch[1] : x->ch[0];
            } else {
                int d = x->ch[0]->fix < x->ch[1]->fix;
                rotate(x, !d);
                del(x->ch[!d], v);
            }
        } else {
            del(x->ch[v>x->v], v);
        }
        if (x != null) x->push_up();
    }
    int find_kth(Node *x, int k){
        int t = 0;
        for (;;){
            t = x->ch[0]->s;
            if (k == t + 1) break;
            else if (k < t + 1) x = x->ch[0];
            else k -= t + 1, x = x->ch[1];
        }
        return x->v;
    }
}treap;
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    ll ans;
    int t, n, m, k, tmp, c = 1;
    scanf("%d", &t);
    while (t--){
        treap.init(), ans = 0;
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n; i++) treap.insert(treap.root, i);
        while (m--){
            scanf("%d", &k);
            ans += tmp = treap.find_kth(treap.root, k);
            treap.del(treap.root, tmp);
        }
        printf("Case %d: %lld\n", c++, ans);
    }
    return 0;
}
