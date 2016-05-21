#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#define Max_N 30020  
#define A_Seed 16807  
#define INF 0x7fffffff  
#define Q_Seed (INF / A_Seed)  
#define R_Seed (INF % A_Seed)  
static int seed=1;  
int pair[Max_N],res[Max_N];  
typedef struct treap_t{  
    int data,fix,size;  
    struct treap_t *left,*right;  
}treap,*Treap;  
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
    (*T)->size=((*T)->left!=NULL ? (*T)->left->size : 0)+((*T)->right!=NULL ? (*T)->right->size : 0)+1;  
    k->size=(k->left!=NULL ? k->left->size : 0)+(k->right!=NULL ? k->right->size : 0)+1;  
    *T=k;  
}  
void rotate_left(Treap *T){  
    Treap k=(*T)->right;  
    (*T)->right=k->left;  
    k->left=*T;  
    (*T)->size=((*T)->left!=NULL ? (*T)->left->size : 0)+((*T)->right!=NULL ? (*T)->right->size : 0)+1;  
    k->size=(k->left!=NULL ? k->left->size : 0)+(k->right!=NULL ? k->right->size : 0)+1;  
    *T=k;  
}  
void Insert(Treap *T,int data,int fix){  
    if(*T == NULL){  
        *T=(Treap)malloc(sizeof(treap));  
        (*T)->left=(*T)->right=NULL;  
        (*T)->data=data,(*T)->size=1,(*T)->fix=fix;  
    }else if(data < (*T)->data){  
        Insert(&((*T)->left),data,fix);  
        if((*T)->left->fix < (*T)->fix)  
            rotate_right(T);  
        (*T)->size=((*T)->left!=NULL ? (*T)->left->size : 0)+((*T)->right!=NULL ? (*T)->right->size : 0)+1;  
    }else if(data >= (*T)->data){  
        Insert(&((*T)->right),data,fix);  
        if((*T)->right->fix < (*T)->fix)  
            rotate_left(T);  
        (*T)->size=((*T)->left!=NULL ? (*T)->left->size : 0)+((*T)->right!=NULL ? (*T)->right->size : 0)+1;  
    }  
}  
Treap find_kth(Treap T,int k){  
    int x=(T->left == NULL ? 0 : T->left->size);  
    if(k < x + 1 ) return find_kth(T->left,k);  
    else if(x + 1 < k) return find_kth(T->right,k-(x+1));  
    return T;  
}  
int main()  
{  
    #ifdef LOCAL  
    freopen("input.txt","r",stdin);  
    #endif  
    int i,j,u,n,m,t=0;  
    while(EOF!=scanf("%d %d",&n,&m)){  
        Treap T=NULL;  
        memset(pair,0,sizeof(pair));  
        for(i=1;i<=n;i++) scanf("%d",&pair[i]);  
        for(i=1;i<=m;i++){  
            scanf("%d",&u);  
            for(j=t+1;j<=u;j++) Insert(&T,pair[j],Redom());  
            res[i]=find_kth(T,i)->data;  
            t=u;  
        }  
        for(i=1;i<=m;i++) printf("%d\n",res[i]);  
    }  
    return 0;  
}  
