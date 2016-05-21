#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#define Max_N 300100  
#define size(_) ((_)==null ? 0 : (_)->size)  
typedef struct spt{  
    int val, size, rev;  
    struct spt *pre, *ch[2];  
}splay;  
splay *root, *null, stack[Max_N];  
int sz = 0, arr[Max_N];  
splay *_calloc(int val){  
    splay *p = &stack[sz++];  
    p->pre = p->ch[0] = p->ch[1] = null;  
    p->val = val, p->size = 1, p->rev = 0;  
    return p;  
}  
void push_up(splay *x){  
    if (x == null) return;  
    x->size = size(x->ch[0]) + size(x->ch[1]) + 1;  
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
    if (x == null) return;  
    if (x->rev != 0){  
        x->rev ^= 1;  
        update(x->ch[0]);  
        update(x->ch[1]);  
    }  
}  
void rotate(splay *x, int d){  
    splay *y = x->pre;  
    push_down(y), push_down(x);  
    y->ch[!d] = x->ch[d];  
    if (x->ch[d] != 0) x->ch[d]->pre = y;  
    x->pre = y->pre;  
    if (y->pre != null) y->pre->ch[y->pre->ch[0] != y] = x;  
    x->ch[d] = y;  
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
    int mid = 0;  
    splay *p = null;  
    if (l > r) return null;  
    mid = (l + r) >> 1;  
    p =  _calloc(arr[mid]);  
    p->ch[0] = built(l, mid - 1);  
    if (p->ch[0] != null) p->ch[0]->pre = p;  
    p->ch[1] = built(mid + 1, r);  
    if (p->ch[1] != null) p->ch[1]->pre = p;  
    push_up(p);  
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
    push_up(root->ch[1]);  
    push_up(root);  
}  
splay *_select(splay *x, int k){  
    int t = 0;  
    for (; x != null;){  
        push_down(x);  
        t = size(x->ch[0]);  
        if (k == t) break;  
        else if (k < t) x = x->ch[0];  
        else k -= t + 1, x = x->ch[1];  
    }  
    return x;  
}  
splay *get_range(int l, int r){  
    splay *x = _select(root, l - 1);  
    splay_splay(x, null);  
    x = _select(root, r + 1);  
    splay_splay(x, root);  
    return root->ch[1]->ch[0];  
}  
void reverse(int l, int r){  
    splay *ret = get_range(l, r);  
    update(ret);  
}  
void travle(splay *x){  
    if (x != null){  
        push_down(x);  
        travle(x->ch[0]);  
        travle(x->ch[1]);  
    }  
}  
void gogo(){  
    int t, cnt = 0;  
    for (; (t = _select(root, 1)->val)!= 1; cnt++){  
        reverse(1, t);  
        if (cnt > 100000){  
            printf("-1\n");  
            return;  
        }  
    }  
    printf("%d\n", cnt);  
}  
int main(){  
#ifdef LOCAL  
    freopen("in.txt", "r", stdin);  
    freopen("out.txt", "w+", stdout);  
#endif  
    int i, n;  
    while (~scanf("%d", &n)){  
        sz = 0;  
        for (i = 1; i <= n; i++) scanf("%d", &arr[i]);  
        initialize(1, n);  
        gogo();  
    }  
    return 0;  
}  
