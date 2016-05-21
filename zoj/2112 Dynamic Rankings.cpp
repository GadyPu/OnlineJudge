#include<cstdio>  
#include<cstdlib>  
#include<cstring>  
#include<algorithm>  
#define lc root<<1  
#define rc root<<1|1  
#define INF 0x3f3f3f3f  
const int Max_N = 50010;  
struct SBT{  
    int key, size, cnt;  
    SBT *ch[2];  
    inline void push_up(){  
        size = ch[0]->size + ch[1]->size + cnt;  
    }  
    int cmp(int v) const{  
        if (v == key) return -1;  
        return v > key;  
    }  
}*null, stack[Max_N * 18], *ptr[Max_N << 2];  
int sz = 0, sum = 0, arr[Max_N];  
void init(){  
    null = &stack[sz++];  
    null->key = null->size = null->cnt = 0;  
}  
void rotate(SBT* &x, int d){  
    SBT *k = x->ch[!d];  
    x->ch[!d] = k->ch[d];  
    k->ch[d] = x;  
    k->size = x->size;  
    x->push_up();  
    x = k;  
}  
void Maintain(SBT* &x, int d){  
    if (x->ch[d] == null) return;  
    if (x->ch[d]->ch[d]->size > x->ch[!d]->size){  
        rotate(x, !d);  
    } else if (x->ch[d]->ch[!d]->size > x->ch[!d]->size){  
        rotate(x->ch[d], d), rotate(x, !d);  
    } else {  
        return;  
    }  
    Maintain(x, 0), Maintain(x, 1);  
}  
void insert(SBT* &x, int key){  
    if (x == null){  
        x = &stack[sz++];  
        x->ch[0] = x->ch[1] = null;  
        x->key = key, x->size = x->cnt = 1;  
    } else {  
        int d = x->cmp(key);  
        x->size++;  
        if (-1 == d){  
            x->cnt++;  
            return;  
        }  
        insert(x->ch[d], key);  
        x->push_up();  
        Maintain(x, d);  
    }  
}  
void del(SBT* &x, int key){  
    if (x == null) return;  
    int d = x->cmp(key);  
    x->size--;  
    if (-1 == d){  
        if (x->cnt > 1){  
            x->cnt--;  
        } else if (x->ch[0] == null || x->ch[1] == null){  
            x = x->ch[0] != null ? x->ch[0] : x->ch[1];  
        } else {  
            SBT *ret = x->ch[1];  
            for (; ret->ch[0] != null; ret = ret->ch[0]);  
            del(x->ch[1], x->key = ret->key);  
        }  
    } else {  
        del(x->ch[d], key);  
    }  
    if (x != null) x->push_up();  
}  
int sbt_rank(SBT *x, int key){  
    int t, cur;  
    for (t = cur = 0; x != null;){  
        t = x->ch[0]->size;  
        if (key < x->key) x = x->ch[0];  
        else if (key >= x->key) cur += x->cnt + t, x = x->ch[1];  
    }  
    return cur;  
}  
void seg_built(int root, int l, int r){  
    for (int i = l; i <= r; i++) insert(ptr[root], arr[i]);  
    if (l == r) return;  
    int mid = (l + r) >> 1;  
    seg_built(lc, l, mid);  
    seg_built(rc, mid + 1, r);  
}  
void seg_query(int root, int l, int r, int x, int y, int val){  
    if (x > r || y < l) return;  
    if (x <= l && y >= r){  
        sum += sbt_rank(ptr[root], val);  
        return;  
    }  
    int mid = (l + r) >> 1;  
    seg_query(lc, l, mid, x, y, val);  
    seg_query(rc, mid + 1, r, x, y, val);  
}  
void seg_del(int root, int l, int r, int pos, int val){  
    if (pos > r || pos < l) return;  
    del(ptr[root], val);  
    if (l == r) return;  
    int mid = (l + r) >> 1;  
    seg_del(lc, l, mid, pos, val);  
    seg_del(rc, mid + 1, r, pos, val);  
}  
void seg_insert(int root, int l, int r, int pos, int val) {  
    if (pos > r || pos < l) return;  
    insert(ptr[root], val);  
    if (l == r) return;  
    int mid = (l + r) >> 1;  
    seg_insert(lc, l, mid, pos, val);  
    seg_insert(rc, mid + 1, r, pos, val);  
}  
void gogo(int n, int a, int b, int k){  
    int l = 0, r = INF;  
    while (l < r){  
        sum = 0;  
        int mid = (l + r) >> 1;  
        seg_query(1, 1, n, a, b, mid);  
        if (sum < k) l = mid + 1;  
        else r = mid;  
    }  
    printf("%d\n", l);  
}  
int main(){  
#ifdef LOCAL  
    freopen("in.txt", "r", stdin);  
    freopen("out.txt", "w+", stdout);  
#endif  
    char ch;  
    int t, n, m, a, b, k;  
    scanf("%d", &t);  
    while (t--){  
        sz = 0, init();  
        scanf("%d %d", &n, &m);  
        for (int i = 1; i <= n; i++) scanf("%d", &arr[i]);  
        std::fill(ptr, ptr + (n << 2), null);  
        seg_built(1, 1, n);  
        while (m--){  
            getchar();  
            scanf("%c", &ch);  
            if (ch == 'Q'){  
                scanf("%d %d %d", &a, &b, &k);  
                gogo(n, a, b, k);  
            }  
            else {  
                scanf("%d %d", &a, &b);  
                seg_del(1, 1, n, a, arr[a]);  
                seg_insert(1, 1, n, a, arr[a] = b);  
            }  
        }  
    }  
    return 0;  
}  
