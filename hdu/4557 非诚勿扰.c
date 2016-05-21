#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Max_N 10000
#define _size(T) (((T)==NULL) ? 0 : ((T)->size))
#define node_size(T) (_size((T)->left) + _size((T)->right) + (T)->cnt)
typedef char st[50];
struct _node{
    int idx, val;
    st name;
}node[Max_N];
typedef struct treap_t{
    int val, size, cnt, fix;
    struct treap_t *left, *right;
}treap, *Treap;
treap _treap[200000];
int sz = 0;
int _random(){
    static int x = 1364684679;
    x += (x << 2) + 1;
    return x;
}
void rotate_right(Treap *T){
    Treap k = (*T)->left;
    (*T)->left = k->right;
    k->right = *T;
    (*T)->size = node_size(*T);
    k->size = node_size(k);
    *T = k;
}
void rotate_left(Treap *T){
    Treap k = (*T)->right;
    (*T)->right = k->left;
    k->left = *T;
    (*T)->size = node_size(*T);
    k->size = node_size(k);
    *T = k;
}
void insert(Treap *T, int val, int fix){
    if (*T == NULL){
        *T = &_treap[sz++];
        memset(*T, 0, sizeof(treap));
        (*T)->size = 1, (*T)->cnt = 1, (*T)->val = val, (*T)->fix = fix;
    }
    else if (val < (*T)->val){
        (*T)->size++;
        insert(&((*T)->left), val, fix);
        if ((*T)->left->fix < (*T)->fix)
            rotate_right(T);
    }
    else if (val >(*T)->val){
        (*T)->size++;
        insert(&((*T)->right), val, fix);
        if ((*T)->right->fix < (*T)->fix)
            rotate_left(T);
    }
    else {
        ++(*T)->cnt;
        ++(*T)->size;
    }
}
void treap_remove(Treap *T, int val){
    if ((*T)->val == val){
        if ((*T)->cnt>1){
            (*T)->size--, (*T)->cnt--;
        }
        else if ((*T)->left == NULL || (*T)->right == NULL){
            (*T) = ((*T)->left != NULL ? (*T)->left : (*T)->right);
        }
        else if ((*T)->left->fix < (*T)->right->fix){
            rotate_right(T);
            (*T)->size--;
            treap_remove(&((*T)->right), val);
        } else if ((*T)->right->fix < (*T)->left->fix){
            rotate_left(T);
            (*T)->size--;
            treap_remove(&((*T)->left), val);
        }
    } else if (val < (*T)->val){
        (*T)->size--;
        treap_remove(&((*T)->left), val);
    } else {
        (*T)->size--;
        treap_remove(&((*T)->right), val);
    }
}
Treap find_kth(Treap T, int k){
    if (T == NULL) return NULL;
    int x = _size(T->left);
    if (k < x + 1) return find_kth(T->left, k);
    else if (k > x + T->cnt) return find_kth(T->right, k - (x + T->cnt));
    else return T;
}
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    st s1, s2;
    int t, n, k, val, i = 1;
    char rev[200];
    scanf("%d", &t);
    while (t--){
        printf("Case #%d:\n", i++);
        sz = k = 0;
        memset(node, 0, sizeof(node));
        Treap root = NULL;
        scanf("%d\n", &n);
        while (n--){
            gets(rev);
            sscanf(rev, "%s", s1);
            if (0 == strcmp(s1, "Add")){
                sscanf(rev, "%s %s %d", s1, s2, &val);
                insert(&root, val, _random());
                node[k].val = val;
                node[k].idx = k;
                strcpy(node[k++].name, s2);
                printf("%d\n", root->size);
            } else if (0 == strcmp(s1, "Find")){
                sscanf(rev, "%s %d", s1, &val);
                Treap ret = NULL;
                int p = 1, m = _size(root), flag = 0;
                for (p; p <= m; p++){
                    ret = find_kth(root, p);
                    if (ret != NULL && ret->val >= val){
                        flag = 1;
                        break;
                    }
                }
                if (flag && ret->cnt >= 1){
                    for (p = 0; p < k; p++){
                        if (node[p].val != -1 && node[p].val == ret->val){
                            node[p].val = -1;
                            treap_remove(&root, ret->val);
                            printf("%s\n", node[p].name);
                            break;
                        }
                    }
                } else {
                    printf("WAIT...\n");
                }
            }
        }
    }
    return 0;
}
