#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#define Max_N 100000  
#define A_Seed 16807  
#define INF 0x7fffffff  
#define Q_Seed (INF / A_Seed)  
#define R_Seed (INF % A_Seed)  
static int seed=1;  
int Redom()  
{  
    int hi=seed / Q_Seed;  
    int lo=seed % Q_Seed;  
    int temp = A_Seed * lo - R_Seed * hi;  
    return temp > 0 ? (seed = temp) : (seed = temp + INF);  
}  
typedef struct treap_t  
{  
    int client,priority,size,fix;  
    struct treap_t *left,*right;  
}treap,*Treap;  
void rotate_left(Treap *T)  
{  
    Treap k=(*T)->right;  
    (*T)->right=k->left;  
    k->left=*T;  
    *T=k;  
    (*T)->size=1;  
    k=(*T)->left;  
    if(k!=NULL)  
    {  
        k->size=1;  
        if(k->left!=NULL) k->size+=k->left->size;  
        if(k->right!=NULL) k->size+=k->right->size;  
        (*T)->size+=k->size;  
    }  
    if((*T)->right!=NULL) (*T)->size+=(*T)->right->size;  
}  
void rotate_right(Treap *T)  
{  
    Treap k=(*T)->left;  
    (*T)->left=k->right;  
    k->right=*T;  
    *T=k;  
    (*T)->size=1;  
    k=(*T)->right;  
    if(k!=NULL)  
    {  
        k->size=1;  
        if(k->left!=NULL) k->size+=k->left->size;  
        if(k->right!=NULL) k->size+=k->right->size;  
        (*T)->size+=k->size;  
    }  
    if((*T)->left!=NULL) (*T)->size+=(*T)->left->size;  
}  
void Insert(Treap *T,int client,int priority,int fix)  
{  
    if(*T==NULL)  
    {  
        *T=(Treap)malloc(sizeof(treap));  
        (*T)->left=(*T)->right=NULL;  
        (*T)->fix=fix,(*T)->size=1;  
        (*T)->client=client,(*T)->priority=priority;  
    }  
    else if(priority < (*T)->priority)  
    {  
        (*T)->size++;  
        Insert(&((*T)->left),client,priority,fix);  
        if((*T)->left->fix < (*T)->fix)  
            rotate_right(T);  
    }  
    else if(priority > (*T)->priority)  
    {  
        (*T)->size++;  
        Insert(&((*T)->right),client,priority,fix);  
        if((*T)->right->fix < (*T)->fix)  
            rotate_left(T);  
    }  
}  
void Remove(Treap *T,int priority)  
{  
    if((*T)->priority == priority)  
    {  
        if((*T)->left==NULL || (*T)->right==NULL)  
        {  
            Treap k=*T;  
            if((*T)->left!=NULL)  
                *T=(*T)->left;  
            else  
                *T=(*T)->right;  
            free(k);  
        }  
        else if((*T)->left->fix < (*T)->right->fix)  
        {  
            rotate_right(T);  
            Remove(T,priority);  
        }  
        else if((*T)->left->fix > (*T)->right->fix)  
        {  
            rotate_left(T);  
            Remove(T,priority);  
        }  
    }  
    else if(priority < (*T)->priority)  
    {  
        (*T)->size--;  
        Remove(&((*T)->left),priority);  
    }  
    else  
    {  
        (*T)->size--;  
        Remove(&((*T)->right),priority);  
    }  
}  
Treap find_kth(Treap T,int k)  
{  
    if(T==NULL) return NULL;  
    int x=(T->left==NULL ? 0 : T->left->size);  
    if(k < x+1)  
        return find_kth(T->left,k);  
    else if(k > x+1)  
        return find_kth(T->right,k-(x+1));  
    else return T;  
}  
int main()  
{  
    #ifdef LOCAL  
    freopen("input.txt","r",stdin);  
    #endif  
    char buf[20];  
    Treap T=NULL,res=NULL;  
    while(gets(buf) && '0'!=buf[0])  
    {  
        int tmp,a,b,c;  
        if(1 == strlen(buf))  
        {  
            tmp=atoi(buf);  
            if(tmp == 2 && T!=NULL) res=find_kth(T,T->size);  
            else if(tmp==3 && T!=NULL) res=find_kth(T,1);  
            if(res == NULL || T==NULL) printf("0\n");  
            else {  
                printf("%d\n",res->client);  
                Remove(&T,res->priority);  
            }  
        }  
        else  
        {  
            sscanf(buf,"%d %d %d",&a,&b,&c);  
            Insert(&T,b,c,Redom());  
        }  
    }  
    return 0;  
}  
