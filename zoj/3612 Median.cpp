#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
typedef long long ll;  
#define Max_N 10100  
#define size(_) ((_)==NULL ? 0 : (_)->size)  
typedef struct sbt{  
    ll key;  
    int cnt, size;  
    struct sbt *ch[2];  
}BSTNode, *SBT;  
BSTNode stack[Max_N];  
int sz = 0;  
void rotate(SBT *x, int d){  
    SBT k = (*x)->ch[!d];  
    (*x)->ch[!d] = k->ch[d];  
    k->ch[d] = *x;  
    k->size = size(*x);  
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
void insert(SBT *x, ll key){  
    if (*x == NULL){  
        *x = &stack[sz++];  
        (*x)->ch[0] = (*x)->ch[1] = NULL;  
        (*x)->key = key, (*x)->size = (*x)->cnt = 1;  
    } else {  
        (*x)->size++;  
        if (key == (*x)->key){  
            (*x)->cnt++;  
            return;  
        }  
        insert(&((*x)->ch[key > (*x)->key]), key);  
        Maintain(x, key > (*x)->key);  
    }  
}  
ll find_kth(SBT x, int k){  
    int t = 0;  
    for (; x != NULL;){  
        t = size(x->ch[0]);  
        if (t + 1 <= k && k <= t + x->cnt) break;  
        else if (k < t + 1) x = x->ch[0];  
        else k -= t + x->cnt, x = x->ch[1];  
    }  
    return x->key;  
}  
void _delete(SBT *x, ll key){  
    SBT t = NULL;  
    if (*x == NULL) return;  
    (*x)->size--;  
    if ((*x)->key == key){  
        if ((*x)->cnt > 1){  
            (*x)->cnt--;  
        } else {  
            if (!(*x)->ch[0] || !(*x)->ch[1]){  
                *x = (*x)->ch[0] ? (*x)->ch[0] : (*x)->ch[1];  
            } else {  
                t = (*x)->ch[1];  
                for (; t->ch[0] != NULL; t = t->ch[0]);  
                _delete(&((*x)->ch[1]), (*x)->key = t->key);  
            }  
        }  
    } else {  
        _delete(&((*x)->ch[key > (*x)->key]), key);  
    }  
}  
SBT search(SBT root, ll x){  
    if (root == NULL) return NULL;  
    else if (root->key == x) return root;  
    else return search(root->ch[x > root->key], x);  
}  
void query(SBT root, ll x){  
    int t;  
    ll v1, v2;  
    SBT ret = NULL;  
    if (!size(root)){  
        printf("Empty!\n");  
        return;  
    } else {  
        t = size(root);  
        if (t % 2 != 0){  
            printf("%lld\n", find_kth(root, (t >> 1) + 1));  
        } else {  
            v1 = find_kth(root, t >> 1);  
            v2 = find_kth(root, (t >> 1) + 1);  
            if ((v1 + v2) % 2 == 0){  
                printf("%1ld\n", (v1 + v2) >> 1);  
            } else {  
                printf("%.1lf\n", (double)(v1 + v2) / 2.0);  
            }  
        }  
    }  
}  
int main(){  
#ifdef LOCAL  
    freopen("in.txt", "r", stdin);  
    freopen("out.txt", "w+", stdout);  
#endif  
    ll x;  
    int T, n;  
    char buf[20];  
    SBT root = NULL;  
    scanf("%d", &T);  
    while (T--){  
        sz = 0, root = NULL;  
        scanf("%d", &n);  
        while (n--){  
            scanf("%s %lld", buf, &x);  
            if (buf[0] == 'a'){  
                insert(&root, x);  
                query(root, x);  
            } else {  
                if (!root || !search(root, x)){  
                    printf("Wrong!\n");  
                    continue;  
                }  
                _delete(&root, x);  
                query(root, x);  
            }  
        }  
    }  
    return 0;  
} 
