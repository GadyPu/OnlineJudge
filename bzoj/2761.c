#define LOCAL
#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct _node{
    int val, fix;
    struct _node *ch[2];
}treap, *Treap;
treap stack[50010];
int flag = 1, sz = 0;;
int _random(){
    static int x = 1840828537;
    x += (x << 2) | 1;
    return x;
}
void rotate(Treap *T, int c){
    Treap k = (*T)->ch[c];
    (*T)->ch[c] = k->ch[!c];
    k->ch[!c] = *T;
    *T = k;
}
void insert(Treap *T, int val, int fix){
    if (*T == NULL){
        *T = &stack[sz++];
        (*T)->ch[0] = (*T)->ch[1] = NULL;
        (*T)->val = val, (*T)->fix = fix;
    } else if (val < (*T)->val){
        insert(&((*T)->ch[0]), val, fix);
        if ((*T)->ch[0]->fix < (*T)->fix)
            rotate(T, 0);
    } else if (val > (*T)->val){
        insert(&((*T)->ch[1]), val, fix);
        if ((*T)->ch[1]->fix < (*T)->fix)
            rotate(T, 1);
    } else {
        flag = 0;
        return;
    }
}
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int i, t, n, k;
    Treap root = NULL;
    scanf("%d", &t);
    while (t--){
        sz = 0, flag = 1, root = NULL;
        scanf("%d %d", &n, &k);
        insert(&root, k, _random());
        if (flag) printf("%d", k);
        for (i = 1; i < n; i++){
            flag = 1;
            scanf("%d", &k);
            insert(&root, k, _random());
            if (flag) printf(" %d", k);
        }
        printf("\n");
    }
    return 0;
}
