#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INF 0x3f3f3f3f
#define Max_N 50010
#define _max(a,b) ((a)>(b)?(a):(b))
#define _size(T) ((T)==null ? 0 : (T)->size)
typedef struct _spt{
    int val, max, rev, size, delta;
    struct _spt *pre, *ch[2];
}splay;
int sz = 0;
splay *root, *null, stack[Max_N];
void push_up(splay *x){
    if (x == null) return;
    x->size = _size(x->ch[0]) + _size(x->ch[1]) + 1;
    x->max = _max(x->val, _max(x->ch[0]->max, x->ch[1]->max));
}
void update(splay *x){
    splay *t = null;
    if (x == null) return;
    x->rev ^= 1;
    t = x->ch[0];
    x->ch[0] = x->ch[1];
    x->ch[1] = t;
}
void push_down(splay *x){
    int t = 0;
    if (x== null) return;
    if (x->delta != 0){
        t = x->delta;
        if (x->ch[0] != null){
            x->ch[0]->delta += t;
            x->ch[0]->max += t;
            x->ch[0]->val += t;
        }
        if (x->ch[1] != null){
            x->ch[1]->delta += t;
            x->ch[1]->max += t;
            x->ch[1]->val += t;
        }
        x->delta = 0;
    }
    if (x->rev != 0){
        x->rev ^= 1;
        update(x->ch[0]);
        update(x->ch[1]);
    }
}
splay *_calloc(int val){
    splay *p = &stack[sz++];
    p->delta = p->rev = 0;
    p->size = 1, p->max = p->val = val;
    p->pre = p->ch[0] = p->ch[1] = null;
    return p;
}
void rotate(splay *x, int c){
    splay *y = x->pre;
    push_down(y), push_down(x);
    y->ch[!c] = x->ch[c];
    if (x->ch[c] != null) x->ch[c]->pre = y;
    x->pre = y->pre;
    if (y->pre != null) y->pre->ch[y->pre->ch[0] != y] = x;
    x->ch[c] = y;
    y->pre = x;
    push_up(y);
    if (y == root) root = x;
}
void splay_splay(splay *x, splay *f){
    if (x == root) return;
    for (; x->pre != f; push_down(x)){
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
    push_up(x);
}
splay *built(int l, int r){
    splay *p = null;
    if (l > r) return null;
    int mid = (l + r) >> 1;
    p = _calloc(0);
    p->ch[0] = built(l, mid - 1);
    if (p->ch[0] != null) p->ch[0]->pre = p;
    p->ch[1] = built(mid + 1, r);
    if (p->ch[1] != null) p->ch[1]->pre = p;
    push_up(p);
    return p;
}
void initialize(int l, int r){
    null = _calloc(-INF);
    null->size = 0;
    root = _calloc(-INF);
    root->ch[1] = _calloc(-INF);
    root->ch[1]->pre = root;
    splay *x = built(l, r);
    root->ch[1]->ch[0] = x;
    x->pre = root->ch[1];
    push_up(root->ch[1]);
    push_up(root);
}
splay *select(splay *x, int k){
    int t = 0;
    splay *ret = x;
    for (;;){
        push_down(ret);
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
void change(int l, int r, int c){
    splay *x = get_range(l, r);
    if (c != INF){
        x->delta += c;
        x->val += c;
        x->max += c;
    } else {
        update(x);
    }
}
void query(int l, int r){
    splay *x = get_range(l, r);
    printf("%d\n", x->max);
}
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int a, b, c, d, N, M;
    while (~scanf("%d %d", &N, &M)){
        sz = 0;
        initialize(1, N);
        while (M--){
            scanf("%d", &a);
            if (1 == a) scanf("%d %d %d", &b, &c, &d), change(b, c, d);
            else if (2 == a) scanf("%d %d", &b, &c), change(b, c, INF);
            else scanf("%d %d", &b, &c), query(b, c);
        }
    }
    return 0;
}
