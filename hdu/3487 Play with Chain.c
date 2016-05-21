#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Max_N 300100
#define _size(T) ((T)==null ? 0 : (T)->size)
typedef struct _spt{
    int val, size, rev;
    struct _spt *pre, *ch[2];
}splay;
splay *root, *null, stack[Max_N];
int N, cnt = 0, sz = 0;
void pushup(splay *x){
    if (x == null) return;
    x->size = _size(x->ch[0]) + _size(x->ch[1]) + 1;
}
void update(splay *x){
    splay *tmp = null;
    if (x == null) return;
    x->rev ^= 1;
    tmp = x->ch[0];
    x->ch[0] = x->ch[1];
    x->ch[1] = tmp;
}
void pushdown(splay *x){
    if (x == null) return;
    if (x->rev != 0){
        x->rev ^= 1;
        update(x->ch[0]);
        update(x->ch[1]);
    }
}
splay *_calloc(int val){
    splay *p = &stack[sz++];
    p->pre = p->ch[0] = p->ch[1] = null;
    p->size = 1, p->val = val, p->rev = 0;
    return p;
}
void rotate(splay *x, int c){
    splay *y = x->pre;
    pushdown(y), pushdown(x);
    y->ch[!c] = x->ch[c];
    if (x->ch[c] != null) x->ch[c]->pre = y;
    x->pre = y->pre;
    if (y->pre != null) y->pre->ch[y->pre->ch[0] != y] = x;
    x->ch[c] = y;
    y->pre = x;
    pushup(y);
    if (y == root) root = x;
}
void splay_splay(splay *x, splay *f){
    if (x == root) return;
    for (; x->pre != f; pushdown(x)){
        if (x->pre->pre == f){
            rotate(x, x->pre->ch[0] == x);
        } else {
            splay *y = x->pre, *z = y->pre;
            if (z->ch[0] == y){
                if (y->ch[0] == x) rotate(y, 1), rotate(x, 1);
                else rotate(x, 0), rotate(x, 1);
            } else {
                if (y->ch[1] == x) rotate(y, 0), rotate(x, 0);
                else rotate(x, 1), rotate(x, 0);
            }
        }
    }
    pushup(x);
}
splay *built(int l, int r){
    int mid = 0;
    splay *p = null;
    if (l > r) return null;
    mid = (l + r) >> 1;
    p = _calloc(mid);
    p->ch[0] = built(l, mid - 1);
    if (p->ch[0] != null) p->ch[0]->pre = p;
    p->ch[1] = built(mid + 1, r);
    if (p->ch[1] != null) p->ch[1]->pre = p;
    pushup(p);
    return p;
}
void initialize(int l, int r){
    null = _calloc(-1);
    null->size = 0;
    root = _calloc(-1);
    root->ch[1] = _calloc(-1);
    root->ch[1]->pre = root;
    splay *x = built(l, r);
    root->ch[1]->ch[0] = x;
    x->pre = root->ch[1];
    pushup(root->ch[1]);
    pushup(root);
}
splay *select(splay *x, int k){
    int t = 0;
    splay *ret = x;
    for (;;){
        pushdown(ret);
        t = _size(ret->ch[0]);
        if (k == t) break;
        else if (k < t) ret = ret->ch[0];
        else k -= t + 1, ret = ret->ch[1];
    }
    return ret;
}
splay *get_range(int l, int r){
    splay_splay(select(root, l - 1), null);
    splay_splay(select(root, r + 1), root);
    return root->ch[1]->ch[0];
}
void travel(splay *x){
    if (x != null){
        pushdown(x);
        travel(x->ch[0]);
        printf("%d", x->val);
        if (cnt++ < N - 1) printf(" ");
        travel(x->ch[1]);
    }
}
void reverse(int l, int r){
    splay *ret = get_range(l, r);;
    update(ret);
}
void cut(int a, int b, int c){
    splay *ret = get_range(a, b);
    root->ch[1]->ch[0] = null;
    pushup(root->ch[1]);
    pushup(root);
    get_range(1, N - (b - a + 1));
    splay_splay(select(root, c), null);
    splay_splay(select(root, c + 1), root);
    root->ch[1]->ch[0] = ret;
    ret->pre = root->ch[1];
    pushup(root->ch[1]);
    pushup(root);
}
void print(int l, int r){
    splay *ret = get_range(l, r);
    travel(ret);
}
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    char buf[100], s[100];
    int m, a, b, c;
    while (~scanf("%d %d", &N, &m) && N != -1 && m != -1){
        sz = cnt = 0;
        getchar();
        initialize(1, N);
        while (m--){
            gets(buf);
            if ('C' == buf[0]){
                sscanf(buf, "%s %d %d %d", s, &a, &b, &c);
                cut(a, b, c);
            } else {
                sscanf(buf, "%s %d %d", s, &a, &b);
                reverse(a, b);
            }
        }
        print(1, N);
        printf("\n");
    }
    return 0;
}
