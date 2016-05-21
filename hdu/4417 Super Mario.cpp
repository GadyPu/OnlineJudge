#include<cstdio>    
#include<cstdlib>    
#include<cstring>    
#include<algorithm>    
#define lc root<<1    
#define rc root<<1|1    
const int Max_N = 100100;  
struct SBT{  
    int v, s, c;  
    SBT *ch[2];  
    inline void set(int _v = 0){  
        v = _v, c = s = 1;  
        ch[0] = ch[1] = null;  
    }  
    inline void push_up(){  
        s = ch[0]->s + ch[1]->s + c;  
    }  
    inline int cmp(int x) const{  
        return v == x ? -1 : x > v;  
    }  
}*null, stack[Max_N << 3], *ptr[Max_N << 2];  
int sz = 0, sum = 0, arr[Max_N];  
void init(){  
    null = &stack[sz++];  
    null->v = null->s = null->c = 0;  
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
        x->set(v);  
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
int sbt_rank(SBT *x, int key){  
    int t, cur;  
    for (t = cur = 0; x != null;){  
        t = x->ch[0]->s;  
        if (key < x->v) x = x->ch[0];  
        else if (key >= x->v) cur += x->c + t, x = x->ch[1];  
    }  
    return cur;  
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
int main(){  
#ifdef LOCAL  
    freopen("in.txt", "r", stdin);  
    freopen("out.txt", "w+", stdout);  
#endif  
    int i, t, n, m, a, b, c, k = 1;  
    scanf("%d", &t);  
    while (t--){  
        sz = 0, init();  
        scanf("%d %d", &n, &m);  
        printf("Case %d:\n", k++);  
        for (i = 1; i <= n; i++) scanf("%d", &arr[i]);  
        seg_built(1, 1, n);  
        while (m--){  
            scanf("%d %d %d", &a, &b, &c);  
            sum = 0;  
            seg_rank(1, 1, n, a + 1, b + 1, c);  
            printf("%d\n", sum);  
        }  
    }  
    return 0;  
}
