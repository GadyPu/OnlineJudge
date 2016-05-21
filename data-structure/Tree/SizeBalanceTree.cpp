#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
const int MAX_N = 100100;
struct Node{
    int v, s, c;
    Node *ch[2];
    inline void set(int _v, int _s, Node *p){
        v = _v, s = c = _s;
        ch[0] = ch[1] = p;
    }
    inline void push_up(){
        s = ch[0]->s + ch[1]->s + c;
    }
    inline int cmp(int x) const{
        return x == v ? -1 : x > v;
    }
};
struct SizeBalanceTree{
    Node stack[MAX_N];
    Node *root, *null, *tail;
    Node *store[MAX_N];
    int top;
    void init(){
        tail = &stack[0];
        null = tail++;
        null->set(0, 0, NULL);
        root = null;
        top = 0;
    }
    inline Node *newNode(int v){
        Node *p = null;
        if (top) p = store[--top];
        else p = tail++;
        p->set(v, 1, null);
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
    inline void insert(Node* &x, int v){
        if (x == null){
            x = newNode(v);
            return;
        } else {
            x->s++;
            int d = x->cmp(v);
            if (-1 == d){
                x->c++;
                return;
            }
            insert(x->ch[d], v);
            x->push_up();
            Maintain(x, d);
        }
    }
    inline void del(Node*  &x, int v){
        if (x == null) return;
        x->s--;
        int d = x->cmp(v);
        if (-1 == d){
            if (x->c > 1){
                x->c--;
                return;
            } else if (x->ch[0] == null || x->ch[1] == null){
                store[top++] = x;
                x = x->ch[0] == null ? x->ch[1] : x->ch[0];
            } else {
                Node *ret = x->ch[1];
                for (; ret->ch[0] != null; ret = ret->ch[0]);
                del(x->ch[1], x->v = ret->v);
            }
        } else {
            del(x->ch[d], v);
        }
        if (x != null) x->push_up();
    }
    inline void insert(int v){
        insert(root, v);
    }
    inline void del(int v){
        del(root, v);
    }
    inline void kth(int k){
        int t;
        Node *x = root;
        for (; x->s;){
            t = x->ch[0]->s;
            if (k <= t) x = x->ch[0];
            else if (t + 1 <= k && k <= t + x->c) break;
            else k -= t + x->c, x = x->ch[1];
        }
        printf("%d\n", x->v);
    }
    inline void rank(int v){
        int t, cur;
        Node *x = root;
        for (cur = 0; x->s;){
            t = x->ch[0]->s;
            if (v == x->v) break;
            else if (v < x->v) x = x->ch[0];
            else cur += t + x->c, x = x->ch[1];
        }
        printf("%d\n", cur + t + 1);
    }
    inline void succ(int v){
        int ret = 0;
        Node *x = root;
        while (x->s){
            if (x->v > v) ret = x->v, x = x->ch[0];
            else x = x->ch[1];
        }
        printf("%d\n", ret);
    }
    inline void pred(int v){
        int ret = 0;
        Node *x = root;
        while (x->s){
            if (x->v < v) ret = x->v, x = x->ch[1];
            else x = x->ch[0];
        }
        printf("%d\n", ret);
    }
}SBT;
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    SBT.init();
    int n, op, v;
    scanf("%d", &n);
    while (n--){
        scanf("%d %d", &op, &v);
        if (1 == op) SBT.insert(v);
        else if (2 == op) SBT.del(v);
        else if (3 == op) SBT.rank(v);
        else if (4 == op) SBT.kth(v);
        else if (5 == op) SBT.pred(v);
        else SBT.succ(v);
    }
    return 0;
}
