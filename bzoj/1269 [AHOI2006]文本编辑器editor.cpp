#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using std::swap;
const int Max_N = 3000010;
struct Node{
    char chr;
    int s;
    bool rev;
    Node *pre, *ch[2];
    inline void 
    set(char _chr = ' ', int _s = 0, Node *p = NULL){
        chr = _chr, s = _s, rev = 0;
        pre = ch[0] = ch[1] = p;
    }
    inline void push_up(){
        s = ch[0]->s + ch[1]->s + 1;
    }
    inline void update(){
        rev ^= 1;
        swap(ch[0], ch[1]);
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
    char buf[Max_N];
    Node *tail, *root, *null;
    Node stack[Max_N], *store[Max_N];
    int top, pos;
    void init(){
        top = 0, pos = 0;
        tail = &stack[0];
        null = tail++;
        null->set();
        root = newNode(' ');
        root->ch[1] = newNode(' ');
        root->ch[1]->pre = root;
        root->ch[1]->push_up();
        root->push_up();
    }
    inline Node *newNode(char chr){
        Node *p = null;
        if (!top) p = tail++;
        else p = store[--top];
        p->set(chr, 1, null);
        return p;
    }
    inline void rotate(Node *x, int c){
        Node *y = x->pre;
        y->push_down(), x->push_down();
        y->ch[!c] = x->ch[c];
        x->pre = y->pre;
        if (x->ch[c] != null) x->ch[c]->pre = y;
        if (y->pre != null) y->pre->ch[y->pre->ch[0] != y] = x;
        x->ch[c] = y;
        y->pre = x;
        y->push_up();
        if (y == root) root = x;
    }
    inline void splay(Node *x, Node *f){
        if (x == root) return;
        for (; x->pre != f; x->push_down()){
            if (x->pre->pre == f){
                rotate(x, x->pre->ch[0] == x);
            } else {
                Node *y = x->pre, *z = y->pre;
                if (z->ch[0] == y){
                    if (y->ch[0] == x)
                        rotate(y, 1), rotate(x, 1);
                    else rotate(x, 0), rotate(x, 1);
                } else {
                    if (y->ch[1] == x)
                        rotate(y, 0), rotate(x, 0);
                    else rotate(x, 1), rotate(x, 0);
                }
            }
        }
        x->push_up();
    }
    inline Node *built(int l, int r){
        if (l > r) return null;
        int mid = (l + r) >> 1;
        Node *p = newNode(buf[mid]);
        p->ch[0] = built(l, mid - 1);
        if (p->ch[0] != null) p->ch[0]->pre = p;
        p->ch[1] = built(mid + 1, r);
        if (p->ch[1] != null) p->ch[1]->pre = p;
        p->push_up();
        return p;
    }
    inline void recycle(Node *x){
        if (x != null){
            recycle(x->ch[0]);
            store[top++] = x;
            recycle(x->ch[1]);
        }
    }
    inline Node *select(Node *x, int k){
        for (int t = 0; x != null;){
            x->push_down();
            t = x->ch[0]->s;
            if (k == t + 1) break;
            else if (k <= t) x = x->ch[0];
            else k -= t + 1, x = x->ch[1];
        }
        return x;
    }
    inline void get_range(int x, int y){
        splay(select(root, x + 1), null);
        splay(select(root, y + 2), root);
    }
    inline void Gets(char *s){
        char c;
        while (c = getchar(), c != '\n') *s++ = c;
        *s = '\0';
    }
    inline void insert(int n){
        char c;
        scanf("%c", &c);
        Gets(buf + 1);
        get_range(pos, pos);
        Node *ret = built(1, n);
        root->ch[1]->ch[0] = ret;
        ret->pre = root->ch[1];
        root->ch[1]->push_up();
        root->push_up();
    }
    inline void del(int n){
        get_range(pos, pos + n);
        Node* &ret = root->ch[1];
        ret->ch[0]->pre = null;
#ifdef LOCAL
        recycle(ret->ch[0]);
#endif
        ret->ch[0] = null;
        ret->push_up();
        root->push_up();
    }
    inline void rotate(int n){
        get_range(pos, pos + n);
        root->ch[1]->ch[0]->update();
    }
    inline  void get(){
        splay(select(root, pos + 2), null);
        printf("%c\n", root->chr);
    }
    inline void move(){
        scanf("%d", &pos);
    }
    inline void prev(){
        pos--;
    }
    inline void next(){
        pos++;
    }
}spt;
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    spt.init();
    int m, n;
    char str[100];
    scanf("%d", &m);
    while (m--){
        scanf("%s", str);
        switch (str[0]){
            case 'M':
                spt.move();
                break;
            case 'I':
                scanf("%d", &n);
                spt.insert(n);
                break;
            case 'D':
                scanf("%d", &n);
                spt.del(n);
                break;
            case 'N':
                spt.next();
                break;
            case 'P':
                spt.prev();
                break;
            case 'R':
                scanf("%d", &n);
                spt.rotate(n);
                break;
            case 'G':
                spt.get();
                break;
        }
    }
    return 0;
}
