#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define node_size(T) (((T)!=NULL) ? ((T)->size) : 0)
#define _size(T) (node_size((T)->left) + node_size((T)->right) + 1)
typedef struct _treap{
    int val, size, fix;
    struct _treap *left, *right;
}treap, *Treap;
treap node[8010];
int sz, ans[8010];
int _random(){
    static int x = 1364684679;
    x += (x << 2) + 1;
    return x;
}
void rotate_left(Treap *T){
    Treap k = (*T)->right;
    (*T)->right = k->left;
    k->left = *T;
    (*T)->size = _size(*T);
    k->size = _size(k);
    *T = k;
}
void rotate_right(Treap *T){
    Treap k = (*T)->left;
    (*T)->left = k->right;
    k->right = *T;
    (*T)->size = _size(*T);
    k->size = _size(k);
    *T = k;
}
void insert(Treap *T, int val, int fix){
    if (*T == NULL){
        *T = &node[sz++];
        memset(*T, 0, sizeof(treap));
        (*T)->size = 1, (*T)->val = val, (*T)->fix = fix;
    } else if (val < (*T)->val){
        (*T)->size++;
        insert(&((*T)->left), val, fix);
        if ((*T)->left->fix < (*T)->fix)
            rotate_right(T);
    } else if (val >(*T)->val){
        (*T)->size++;
        insert(&((*T)->right), val, fix);
        if ((*T)->right->fix < (*T)->fix)
            rotate_left(T);
    }
}
void _remove(Treap *T, int val){
    if ((*T)->val == val){
          if ((*T)->left == NULL || (*T)->right == NULL){
            *T = (*T)->left != NULL ? (*T)->left : (*T)->right;
        } else if ((*T)->left->fix < (*T)->right->fix){
            rotate_right(T);
            (*T)->size--;
            _remove(&((*T)->right), val);
        } else {
            rotate_left(T);
            (*T)->size--;
            _remove(&((*T)->left), val);
        }
    } else if (val < (*T)->val){
        (*T)->size--;
        _remove(&((*T)->left), val);
    } else {
        (*T)->size--;
        _remove(&((*T)->right), val);
    }
}
Treap find_kth(Treap T, int k){
    int x = node_size(T->left);
    if (k < x + 1) return find_kth(T->left, k);
    else if (k > x + 1) return find_kth(T->right, k - (x + 1));
    else return T;
}
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, i;
    Treap root = NULL;
    while (~scanf("%d", &n)){
        sz = 0, root = NULL;
        for (i = 1; i <= n; i++) insert(&root, i, _random());
        for (i = 0; i < n - 1; i++) scanf("%d", &ans[i]);
        for (i = n - 2; i >= 0; i--){
            ans[i] = find_kth(root, ans[i] + 1)->val;
            _remove(&root, ans[i]);
        }
        printf("%d\n", root->val);
        for (i = 0; i < n - 1; i++) printf("%d\n", ans[i]);
    }
    return 0;
}
