#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstdio>
const int Max_N = 1000100;
struct Node{
    int data, s, c;
    bool color;
    Node *fa, *ch[2];
    inline void set(int _v, int i, bool _color, Node *p){
        data = _v, color = _color, s = c = i;
        fa = ch[0] = ch[1] = p;
    }
    inline void push_up(){
        s = ch[0]->s + ch[1]->s + c;
    }
    inline void push_down(){
        for (Node *x = this; x->s; x = x->fa) x->s--;
    }
};
struct RedBlackTree{
    int top;
    Node *root, *null;
    Node stack[Max_N], *tail, *store[Max_N];
    void init(){
        tail = &stack[0];
        null = tail++;
        null->set(0, 0, 0, NULL);
        root = null;
        top = 0;
    }
    inline Node *newNode(int v){
        Node *p = null;
        if (!top) p = tail++;
        else p = store[--top];
        p->set(v, 1, 1, null);
        return p;
    }
    inline void rotate(Node* &x, bool d){
        Node *y = x->ch[!d];
        x->ch[!d] = y->ch[d];
        if (y->ch[d] != null) y->ch[d]->fa = x;
        y->fa = x->fa;
        if (x->fa == null) root = y;
        else x->fa->ch[x->fa->ch[0] != x] = y;
        y->ch[d] = x;
        x->fa = y;
        x->push_up();
        y->push_up();
    }
    inline void insert(int v){
        Node *x = root, *y = null;
        while (x->s) x->s++, y = x, x = x->ch[v > x->data];
        /*if (v == x->data) x->c++;*/
        x = newNode(v);
        if (y != null) y->ch[v > y->data] = x;
        else root = x;
        x->fa = y;
        insert_fix(x);
    }
    inline void insert_fix(Node* &x){
        while (x->fa->color){
            Node *par = x->fa, *Gp = par->fa;
            bool d = par == Gp->ch[0];
            Node *uncle = Gp->ch[d];
            if (uncle->color){
                par->color = uncle->color = 0;
                Gp->color = 1;
                x = Gp;
            } else if (x == par->ch[d]){
                rotate(x = par, !d);
            } else {
                Gp->color = 1;
                par->color = 0;
                rotate(Gp, d);
            }
        }
        root->color = 0;
    }
    inline int find_kth(Node *x, int k){
        int t = 0;
        for (; x->s;){
            t = x->ch[0]->s;
            if (k == t + 1) break;
            else if (k <= t) x = x->ch[0];
            else k -= t + 1, x = x->ch[1];
        }
        return x->data;
    }
    inline void find_kth(int k){
        printf("%d\n", find_kth(root, root->s - k + 1));
    }
}rbt;
int main(){
#ifdef LOCAL  
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif  
    char ch;
    int i, n, k, d;
    while (~scanf("%d %d", &n, &k)){
        rbt.init();
        for (i = 0; i < n; i++){
            getchar();
            scanf("%c", &ch);
            if ('I' == ch) scanf("%d", &d), rbt.insert(d);
            else rbt.find_kth(k);
        }
    }
    return 0;
}
