#include<cstdio>  
#include<cstdlib>  
#include<cstring>  
#include<algorithm>  
#define lc root<<1  
#define rc root<<1|1  
#define INF 0x3f3f3f3f  
#define _max(a,b) ((a)>(b)?(a):(b))  
#define _min(a,b) ((a)>(b)?(b):(a))  
const int Max_N = 50100;  
struct SBT *null;  
struct SBT{  
    int v, s, c;  
    SBT *ch[2];  
    SBT(int _v = 0) : v(_v){  
        c = s = 1;  
        ch[0] = ch[1] = null;  
    }  
    inline void push_up(){  
        s = ch[0]->s + ch[1]->s + c;  
    }  
    inline int cmp(int x) const{  
        return v == x ? -1 : x > v;  
    }  
}stack[Max_N << 5], *ptr[Max_N << 2];  
int sz = 0, sum = 0, arr[Max_N];  
void init(){  
    null = &stack[sz++];  
    null->s = null->c = 0;  
}  
inline void rotate(SBT* &x, int d){  
    SBT *k = x->ch[!d];  
    x->ch[!d] = k->ch[d];  
    k->ch[d] = x;  
    k->s = x->s;;  
    x->push_up();  
    x = k;  
}  
void Maintain(SBT* &x, int d){  
    if (x->ch[d] == null) return;  
    if (x->ch[d]->ch[d]->s > x->ch[!d]->s){  
        rotate(x, !d);  
    } else if (x->ch[d]->ch[!d]->s > x->ch[d]->s){  
        rotate(x->ch[d], d), rotate(x, !d);  
    } else {  
        return;  
    }  
    Maintain(x, 0), Maintain(x, 1);  
}  
void insert(SBT* &x, int v){  
    if (x == null){  
        x = &stack[sz++];  
        x->v = v;  
        x->ch[0] = x->ch[1] = null;  
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
void del(SBT* &x, int v){  
    if (x == null) return;  
    int d = x->cmp(v);  
    x->s--;  
    if (-1 == d){  
        if (x->c > 1){  
            x->c--;  
        } else if (x->ch[0] == null || x->ch[1] == null){  
            x = x->ch[0] != null ? x->ch[0] : x->ch[1];  
        } else {  
            SBT *ret = x->ch[1];  
            for (; ret->ch[0] != null; ret = ret->ch[0]);  
            del(x->ch[1], x->v = ret->v);  
        }  
    } else {  
        del(x->ch[d], v);  
    }  
    if (x != null) x->push_up();  
}  
int sbt_rank(SBT *x, int v){  
    int t = 0, cur = 0;  
    for (; x != null;){  
        t = x->ch[0]->s;  
        if (v == x->v) return cur + t;  
        else if (v < x->v) x = x->ch[0];  
        else cur += t + x->c, x = x->ch[1];  
    }  
    return cur;  
}  
int sbt_pred(SBT *x, int v){  
    int t = -1;  
    for (; x != null;){  
        if (x->v < v){  
            t = x->v;  
            x = x->ch[1];  
        }  
        else x = x->ch[0];  
    }  
    return t == -1 ? -INF : t;  
}  
int sbt_succ(SBT *x, int v){  
    int t = -1;  
    for (; x != null;){  
        if (x->v > v){  
            t = x->v;  
            x = x->ch[0];  
        }  
        else x = x->ch[1];  
    }  
    return t == -1 ? INF : t;  
}  
void seg_built(int root, int l, int r){  
    ptr[root] = null;  
    for (int i = l; i <= r; i++) insert(ptr[root], arr[i]);  
    if (l == r) return;  
    int mid = (l + r) >> 1;  
    seg_built(lc, l, mid);  
    seg_built(rc, mid + 1, r);  
}  
void seg_rank(int root, int l, int r, int x, int y, int v){  
    if (x > r || y < l) return;  
    if (x <= l && y >= r){  
        sum += sbt_rank(ptr[root], v);  
        return;  
    }  
    int mid = (l + r) >> 1;  
    seg_rank(lc, l, mid, x, y, v);  
    seg_rank(rc, mid + 1, r, x, y, v);  
}  
void seg_modify(int root, int l, int r, int pos, int v){  
    if (pos > r || pos < l) return;  
    del(ptr[root], arr[pos]);  
    insert(ptr[root], v);  
    if (l == r) return;  
    int mid = (l + r) >> 1;  
    seg_modify(lc, l, mid, pos, v);  
    seg_modify(rc, mid + 1, r, pos, v);  
}  
int seg_pred(int root, int l, int r, int x, int y, int v){  
    if (x > r || y < l) return -INF;  
    if (x <= l && y >= r) return sbt_pred(ptr[root], v);  
    int mid = (l + r) >> 1;  
    int v1 = seg_pred(lc, l, mid, x, y, v);  
    int v2 = seg_pred(rc, mid + 1, r, x, y, v);  
    return _max(v1, v2);  
}  
int seg_succ(int root, int l, int r, int x, int y, int v){  
    if (x > r || y < l) return INF;  
    if (x <= l && y >= r) return sbt_succ(ptr[root], v);  
    int mid = (l + r) >> 1;  
    int v1 = seg_succ(lc, l, mid, x, y, v);  
    int v2 = seg_succ(rc, mid + 1, r, x, y, v);  
    return _min(v1, v2);  
}  
void gogo(int n, int a, int b, int k){  
    int mid, l = 0, r = 100000000;  
    while (l < r){  
        sum = 0;  
        mid = (l + r) >> 1;  
        seg_rank(1, 1, n, a, b, mid);  
        if (sum < k) l = mid + 1;  
        else r = mid;  
    }  
    printf("%d\n", l - 1);  
}  
int main(){  
#ifdef LOCAL  
    freopen("in.txt", "r", stdin);  
    freopen("out.txt", "w+", stdout);  
#endif  
    init();  
    int i, n, m, a, b, c, d;  
    scanf("%d %d", &n, &m);  
    for (i = 1; i <= n; i++) scanf("%d", &arr[i]);  
    seg_built(1, 1, n);  
    while (m--){  
        scanf("%d", &a);  
        switch (a){  
            case 1:  
                sum = 1;  
                scanf("%d %d %d", &b, &c, &d);  
                seg_rank(1, 1, n, b, c, d);  
                printf("%d\n",sum);  
                break;  
            case 2:  
                scanf("%d %d %d", &b, &c, &d);  
                gogo(n, b, c, d);  
                break;  
            case 3:  
                scanf("%d %d", &b, &c);  
                seg_modify(1, 1, n, b, c), arr[b] = c;  
                break;  
            case 4:  
                scanf("%d %d %d", &b, &c, &d);  
                printf("%d\n", seg_pred(1, 1, n, b, c, d));  
                break;  
            case 5:  
                scanf("%d %d %d", &b, &c, &d);  
                printf("%d\n", seg_succ(1, 1, n, b, c, d));  
                break;  
        }  
    }  
    return 0;  
} 
