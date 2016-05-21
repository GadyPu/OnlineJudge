#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 50020
#define Max_N 100020
#define A_Seed 16807
#define INF 0x7fffffff
#define Q_Seed (INF / A_Seed)
#define R_Seed (INF % A_Seed)
#define node_size(x) (((x)==NULL) ? 0 : ((x)->size))
typedef struct node_t{ int left,right,k,id,ans; }node;
node rec[N];
typedef struct treap_t{
    int pretty,fix,size;
    struct treap_t *left,*right;
}treap,*Treap;
treap _treap[Max_N<<2];
int sz,pair[Max_N];
static int seed=1;
int Redom(){
    int hi=seed / Q_Seed;
    int lo=seed % Q_Seed;
    int temp = A_Seed * lo - R_Seed * hi;
    return temp > 0 ? (seed = temp) : (seed = temp + INF);
}
void rotate_right(Treap *T){
    Treap k=(*T)->left;
    (*T)->left=k->right;
    k->right=*T;
    (*T)->size=node_size((*T)->left)+node_size((*T)->right)+1;
    k->size=node_size(k->left)+node_size(k->right)+1;
    *T=k;
}
void rotate_left(Treap *T){
    Treap k=(*T)->right;
    (*T)->right=k->left;
    k->left=*T;
    (*T)->size=node_size((*T)->left)+node_size((*T)->right)+1;
    k->size=node_size(k->left)+node_size(k->right)+1;
    *T=k;
}
void Insert(Treap *T,int pretty,int fix){
    if(*T == NULL){
        *T=&_treap[sz++];
        (*T)->left=(*T)->right=NULL;
        (*T)->pretty=pretty,(*T)->size=1,(*T)->fix=fix;
    }else if(pretty < (*T)->pretty){
        Insert(&((*T)->left),pretty,fix);
        if((*T)->left->fix < (*T)->fix)
            rotate_right(T);
        (*T)->size=node_size((*T)->left)+node_size((*T)->right)+1;
    }else if(pretty >= (*T)->pretty){
        Insert(&((*T)->right),pretty,fix);
        if((*T)->right->fix < (*T)->fix)
            rotate_left(T);
        (*T)->size=node_size((*T)->left)+node_size((*T)->right)+1;
    }
}
void Remove(Treap *T,int pretty){
    if(pretty == (*T)->pretty){
        if((*T)->left==NULL || (*T)->right==NULL){
            if((*T)->left!=NULL)
                *T=(*T)->left;
            else
                *T=(*T)->right;
        }else if((*T)->left->fix < (*T)->right->fix){
            rotate_right(T);
            (*T)->size--;
            Remove(&((*T)->right),pretty);
        }else if((*T)->left->fix > (*T)->right->fix){
            rotate_left(T);
            (*T)->size--;
            Remove(&((*T)->left),pretty);
        }
    }else if(pretty < (*T)->pretty){
        (*T)->size--;
        Remove(&((*T)->left),pretty);
    }else{
        (*T)->size--;
        Remove(&((*T)->right),pretty);
    }
}
Treap find_kth(Treap T,int k){
    int x=(T->left == NULL ? 0 : T->left->size);
    if(k < x + 1 ) return find_kth(T->left,k);
    else if(x + 1 < k) return find_kth(T->right,k-(x+1));
    return T;
}
void swap(int *a,int *b){
    int t=*a;
    *a=*b;
    *b=t;
}
int cmp(const void *a,const void *b){
    node t1=*(node *)a,t2=*(node *)b;
    return t1.left - t2.left;
}
int cmp_t(const void *a,const void *b){
    node t1=*(node *)a,t2=*(node *)b;
    return t1.id - t2.id;
}
int main()
{
#ifdef LOCAL
    freopen("in.txt","r",stdin);
	freopen("out.txt","w+",stdout);
#endif
    int i,r,l,n,m;
    while(EOF!=scanf("%d %d",&n,&m)){
        sz=0;
        Treap T=NULL;
        memset(pair,0,sizeof(pair));
        for(i=1;i<=n;i++) scanf("%d",&pair[i]);
        for(i=1;i<=m;i++){
            scanf("%d %d %d",&rec[i].left,&rec[i].right,&rec[i].k);
            if(rec[i].left > rec[i].right) swap(&rec[i].left,&rec[i].right);
            rec[i].id=i;
        }
        qsort(&rec[1],m,sizeof(rec[0]),cmp);
		l=rec[1].left,r=0;
        for(i=1;i<=m;i++){
            while(rec[i].left > l) if(l <= r) Remove(&T,pair[l++]);
            while(rec[i].right < r) Remove(&T,pair[--r]);
            if(r < l) r=l;
            while(r <= rec[i].right) Insert(&T,pair[r++],Redom());
            rec[i].ans=find_kth(T,rec[i].k)->pretty;
        }
        qsort(&rec[1],m,sizeof(rec[0]),cmp_t);
        for(i=1;i<=m;i++) printf("%d\n",rec[i].ans);
    }
    return 0;
}
