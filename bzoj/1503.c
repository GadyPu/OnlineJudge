#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define node_size(T) (((T)!=NULL) ? ((T)->size) : 0)
#define _size(T) (node_size((T)->left) + node_size((T)->right) + (T)->cnt)
typedef struct _treap{
    int val, size, cnt, fix;
    struct _treap *left, *right;
}treap, *Treap;
treap node[100010];
int min, i, sz, cur, temp[100010];
int random(){
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
        (*T)->cnt = (*T)->size = 1, (*T)->val = val, (*T)->fix = fix;
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
    } else {
        (*T)->size++, (*T)->cnt++;
    }
}
void _remove(Treap *T, int val){
    if ((*T)->val == val){
        if ((*T)->cnt>1){
            (*T)->size--, (*T)->cnt--;
        } else if ((*T)->left == NULL || (*T)->right == NULL){
            Treap k = *T;
            *T = (*T)->left != NULL ? (*T)->left : (*T)->right;
        } else if ((*T)->left->fix < (*T)->right->fix){
            (*T)->size--;
            rotate_right(T);
            _remove(&((*T)->right), val);
        } else {
            (*T)->size--;
            rotate_left(T);
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
    else if (k>x + T->cnt) return find_kth(T->right, k - (x + T->cnt));
    else return T;
}
void update(Treap T, int num){
    if (T != NULL){
        update(T->left, num);
        T->val += num;
        if (T->val < min){
            int t = T->cnt;
            while (t >= 1){
                temp[i++] = T->val; 
                t--;
            }
        }
        update(T->right, num);
    }
}
int main(){
#ifdef LOCAL
    freopen("10in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    char ch;
    Treap root = NULL, res = NULL;
    int n, j, k;
    while (~scanf("%d %d\n", &n, &min)){
        cur = sz = i = 0;
        while (n--){
            scanf("%c %d\n", &ch, &k);
            switch (ch){
                case 'I':
                    if (k < min) continue;
                    insert(&root, k, random());
                    break;
                case 'A':
                    update(root, k);
                    break;
                case 'S' :
                    j = i;
                    update(root, -k);
                    for (j = 0; j < i; j++){
                        cur++;
                        _remove(&root, temp[j]);
                    }
                    i = 0;
                    break;
                case 'F':
                    if (k > node_size(root)){
                        printf("-1\n");
                        continue;
                    } else {
                        res = find_kth(root, node_size(root) - k + 1);
                        if (res == NULL) printf("-1\n");
                        else printf("%d\n", res->val);
                    }
            }
        }
        printf("%d\n", cur);
    }
    return 0;
}
