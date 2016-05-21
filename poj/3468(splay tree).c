#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
typedef long long ll;  
#define Max_N 150000  
#define _size(T) ((T)==null ? 0 : (T)->size)  
typedef struct _spt{  
    ll val, size, sum, addMark;  
    struct _spt *pre, *ch[2];  
}splay;  
splay *null, *root, stack[Max_N];  
ll sz = 0, arr[Max_N];  
void pushup(splay *x){  
    if (x == null) return;  
    x->size = _size(x->ch[0]) + _size(x->ch[1]) + 1;  
    x->sum = x->addMark + x->val + x->ch[0]->sum + x->ch[1]->sum;  
}  
void pushdown(splay *x){  
    ll ret = 0;  
    if (x == null) return;  
    if (x->addMark != 0){  
        ret = x->addMark;  
        x->val += ret;  
        if (x->ch[0] != null){  
            x->ch[0]->addMark += ret;  
            x->ch[0]->sum += ret * x->ch[0]->size;  
        }  
        if (x->ch[1] != null){  
            x->ch[1]->addMark += ret;  
            x->ch[1]->sum += ret * x->ch[1]->size;  
        }  
        x->addMark = 0;  
    }  
}  
splay *_calloc(ll val){  
    splay *p = &stack[sz++];  
    p->val = p->sum = val;  
    p->size = 1, p->addMark = 0;  
    p->pre = p->ch[0] = p->ch[1] = null;  
    return p;  
}  
void rotate(splay *x, int c){  
    splay *y = x->pre;  
    pushdown(y), pushdown(x);  
    y->ch[!c] = x->ch[c];  
    x->pre = y->pre;  
    if (x->ch[c] != null) x->ch[c]->pre = y;  
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
splay *built(ll l, ll r){  
    ll mid = 0;  
    splay *p = null;  
    if (l > r) return null;  
    mid = (l + r) >> 1;  
    p = _calloc(arr[mid]);  
    p->ch[0] = built(l, mid - 1);  
    if (p->ch[0] != null) p->ch[0]->pre = p;  
    p->ch[1] = built(mid + 1, r);  
    if (p->ch[1] != null) p->ch[1]->pre = p;  
    pushup(p);  
    return p;  
}  
void initialize(ll l, ll r){  
    null = _calloc(-1);  
    null->size = null->sum = 0;  
    root = _calloc(-1);  
    root->ch[1] = _calloc(-1);  
    root->ch[1]->pre = root;  
    splay *x = built(l, r);  
    root->ch[1]->ch[0] = x;  
    x->pre = root->ch[1];  
    pushup(root->ch[1]);  
    pushup(root);  
}  
splay *select(splay *x, ll k){  
    ll t = 0;  
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
void get_range(ll l, ll r){  
    splay_splay(select(root, l - 1), null);  
    splay_splay(select(root, r + 1), root);  
}  
void update(ll l, ll r, ll add){  
    get_range(l, r);  
    splay *x = root->ch[1]->ch[0];  
    x->addMark += add;  
    x->sum += x->size * add;  
}  
void query(ll l, ll r){  
    get_range(l, r);  
    splay *x = root->ch[1]->ch[0];  
    printf("%lld\n", x->sum);  
}  
int main(){  
#ifdef LOCAL  
    freopen("in.txt", "r", stdin);  
    freopen("out.txt", "w+", stdout);  
#endif  
    char ch;  
    ll i, a, b, c, N, Q;  
    while (~scanf("%lld %lld", &N, &Q)){  
        for (i = 1; i <= N; i++) scanf("%lld", &arr[i]);  
        initialize(1, N);  
        while (Q--){  
            getchar();  
            scanf("%c", &ch);  
            if ('Q' == ch){  
                scanf("%lld %lld", &a, &b);  
                query(a, b);  
            } else {  
                scanf("%lld %lld %lld", &a, &b, &c);  
                update(a, b, c);  
            }  
        }  
    }  
    return 0;  
} 
