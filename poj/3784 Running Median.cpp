#include<iostream>  
#include<algorithm>  
const int Max_N = 10000;  
struct SBT *null;  
struct SBT{  
    int val, size;  
    struct SBT *ch[2];  
    inline void push_up(){  
        size = ch[0]->size + ch[1]->size + 1;  
    }  
}stack[Max_N << 2], *root;  
int sz = 0;  
void init(){  
    null = &stack[sz++];  
    null->val = -1, null->size = 0;  
    root = null;  
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
    } else{  
        return;  
    }  
    Maintain(x, 0), Maintain(x, 1);  
}  
void insert(SBT* &x, int val){  
    if (x == null){  
        x = &stack[sz++];  
        x->val = val, x->size = 1;  
        x->ch[0] = x->ch[1] = null;  
    } else {  
        int d = val > x->val;  
        insert(x->ch[d], val);  
        x->push_up();  
        Maintain(x, d);  
    }  
}  
int find_kth(SBT *x, int k){  
    int t = 0;  
    for (; x != null;){  
        t = x->ch[0]->size;  
        if (k == t + 1) break;  
        else if (k <= t) x = x->ch[0];  
        else k -= t + 1, x = x->ch[1];  
    }  
    return x->val;  
}  
int main(){  
#ifdef LOCAL  
    freopen("in.txt", "r", stdin);  
    freopen("out.txt", "w+", stdout);  
#endif  
    init();  
    int i, t, n, q, val, cnt;  
    scanf("%d", &t);  
    while (t--){  
        sz = cnt = 0;  
        init();  
        scanf("%d %d", &q, &n);  
        printf("%d %d\n", q, (n + 1) >> 1);  
        for (i = 1; i <= n; i++){  
            scanf("%d", &val);  
            insert(root, val);  
            if (i % 2 != 0){  
                printf("%d ", find_kth(root, ((root->size) >> 1) + 1));  
                cnt++;  
            }  
            if (cnt && cnt % 10 == 0) cnt = 0, printf("\n");  
        }  
        printf("\n");  
    }  
    return 0;  
} 
