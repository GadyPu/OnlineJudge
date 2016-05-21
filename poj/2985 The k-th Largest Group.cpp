#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#define Max_N 300100  
#define size(_) ((_)==NULL ? 0 : (_)->size)  
typedef struct sbt{  
    int key, size, cnt;  
    struct sbt *ch[2];  
}SBTNode, *SBT;  
SBTNode *root = NULL, stack[Max_N];  
int sz = 0, rank[Max_N], par[Max_N], count[Max_N];  
void rotate(SBT *x, int d){  
    SBT k = (*x)->ch[!d];  
    (*x)->ch[!d] = k->ch[d];  
    k->ch[d] = *x;  
    k->size = (*x)->size;  
    (*x)->size = size((*x)->ch[0]) + size((*x)->ch[1]) + (*x)->cnt;  
    *x = k;  
}  
void Maintain(SBT *x, int d){  
    if ((*x)->ch[d] == NULL) return;  
    if (size((*x)->ch[d]->ch[d]) > size((*x)->ch[!d])){  
        rotate(x, !d);  
    } else if (size((*x)->ch[d]->ch[!d]) > size((*x)->ch[!d])){  
        rotate(&((*x)->ch[d]), d), rotate(x, !d);  
    } else {  
        return;  
    }  
    Maintain(x, 0), Maintain(x, 1);  
}  
void insert(SBT *x, int key){  
    if (*x == NULL){  
        *x = &stack[sz++];  
        (*x)->ch[0] = (*x)->ch[1] = NULL;  
        (*x)->key = key, (*x)->size = (*x)->cnt = 1;  
    } else {  
        int d = key > (*x)->key;  
        (*x)->size++;  
        if ((*x)->key == key){  
            (*x)->cnt++;  
            return;  
        }  
        insert(&((*x)->ch[d]), key);  
        Maintain(x, d);  
    }  
}  
void _delete(SBT *x, int key){  
    if (*x == NULL) return;  
    (*x)->size--;  
    if ((*x)->key == key){  
        if ((*x)->cnt > 0){  
            (*x)->cnt--;  
        } else if (!(*x)->ch[0] || !(*x)->ch[1]){  
            *x = (*x)->ch[0] ? (*x)->ch[0] : (*x)->ch[1];  
        } else {  
            SBT ret = (*x)->ch[1];  
            for (; ret->ch[0] != NULL; ret = ret->ch[0]);  
            _delete(&((*x)->ch[1]), (*x)->key = ret->key);  
        }  
    } else {  
        _delete(&((*x)->ch[key > (*x)->key]), key);  
    }  
}  
int find_kth(SBT x, int k){  
    int t = 0;  
    for (; x != NULL;){  
        t = size(x->ch[0]);  
        if (t + 1 <= k && k <= t + x->cnt) break;  
        else if (k <= t) x = x->ch[0];  
        else k -= t + x->cnt, x = x->ch[1];  
    }  
    return x->key;  
}  
void init(int n){  
    int i;  
    for (i = 1; i <= n; i++){  
        par[i] = i;  
        rank[i] = 0;  
        count[i] = 1;  
        insert(&root, 1);  
    }  
}  
int find(int x){  
    while (x != par[x]){  
        x = par[x] = par[par[x]];  
    }  
    return x;  
}  
int same(int x, int y){  
    x = find(x), y = find(y);  
    return x == y;  
}  
void unite(int x, int y){  
    x = find(x), y = find(y);  
    if (x == y) return;  
    if (rank[x] < rank[y]){  
        par[x] = y;  
        _delete(&root, count[y]), _delete(&root, count[x]);  
        count[y] += count[x];  
        count[x] = 0;  
        insert(&root, count[y]);  
    } else {  
        par[y] = x;  
        _delete(&root, count[y]), _delete(&root, count[x]);  
        count[x] += count[y];  
        count[y] = 0;  
        insert(&root, count[x]);  
        if (rank[x] == rank[y]) rank[x]++;  
    }  
}  
int main(){  
#ifdef LOCAL  
    freopen("in.txt", "r", stdin);  
    freopen("out.txt", "w+", stdout);  
#endif  
    int n, m, a, b, c;  
    while (~scanf("%d %d", &n, &m)){  
        sz = 0, root = NULL;  
        init(n);  
        while (m--){  
            scanf("%d", &a);  
            if (!a){  
                scanf("%d %d", &b, &c);  
                unite(b, c);  
            } else {  
                scanf("%d", &b);  
                printf("%d\n", find_kth(root, root->size - b + 1));  
            }  
        }  
    }  
    return 0;  
}  
