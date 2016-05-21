#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cstdio>
#include<vector>
#include<ctime>
const int Max_N = 110000;
struct Node{
    int data, s, c;
    Node *ch[2];
    inline void set(int _v, int i, Node *p){
        data = _v, s = c = i;
        ch[0] = ch[1] = p;
    }
    inline void push_up(){
        s = ch[0]->s + ch[1]->s + c;
    }
    inline int cmp(int v) const{
        return data == v ? -1 : v > data;
    }
};
struct BinTree{
    int top;
    Node *root, *null;
    Node stack[Max_N], *tail, *store[Max_N];
    void init(){
        tail = &stack[0];
        null = tail++;
        null->set(0, 0, NULL);
        root = null;
        top = 0;
    }
    inline Node *newNode(int v){
        Node *p = null;
        if (!top) p = tail++;
        else p = store[--top];
        p->set(v, 1, null);
        return p;
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
        }
    }
    inline void del(Node* &x, int v){
        if (!x->s) return;
        x->s--;
        int d = x->cmp(v);
        if (-1 == d){
            if (x->c > 1){
                x->c--;
                return;
            } else if (!x->ch[0]->s || !x->ch[1]->s){
                store[top++] = x;
                x = x->ch[0]->s ? x->ch[0] : x->ch[1];
            } else {
                Node *ret = x->ch[1];
                for (; ret->ch[0]->s; ret = ret->ch[0]);
                del(x->ch[1], x->data = ret->data);
            }
        } else {
            del(x->ch[d], v);
        }
        if (x->s) x->push_up();
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
        printf("%d\n", x->data);
    }
    inline void rank(int v){
        int t, cur = 0;
        Node *x = root;
        for (; x->s;){
            t = x->ch[0]->s;
            if (v == x->data) break;
            else if (v < x->data) x = x->ch[0];
            else cur += t + x->c, x = x->ch[1];
        }
        printf("%d\n", cur + t + 1);
    }
    inline void succ(int v){
        int ret = 0;
        Node *x = root;
        while (x->s){
            if (x->data > v) ret = x->data, x = x->ch[0];
            else x = x->ch[1];
        }
        printf("%d\n", ret);
    }
    inline void pred(int v){
        int ret = 0;
        Node *x = root;
        while (x->s){
            if (x->data < v) ret = x->data, x = x->ch[1];
            else x = x->ch[0];
        }
        printf("%d\n", ret);
    }
}bt;
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    bt.init();
    int n, op, v;
    scanf("%d", &n);
    while (n--){
        scanf("%d %d", &op, &v);
        if (1 == op) bt.insert(v);
        else if (2 == op) bt.del(v);
        else if (3 == op) bt.rank(v);
        else if (4 == op) bt.kth(v);
        else if (5 == op) bt.pred(v);
        else bt.succ(v);
    }
    return 0;
}
