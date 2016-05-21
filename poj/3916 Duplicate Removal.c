#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#define Max_N 102  
typedef struct node_t{ int data,index; }node;  
node rec[Max_N];  
int cmp(const void *a,const void *b){  
    node t=*(node *)a,t1=*(node *)b;  
    return t.index-t1.index;  
}  
int main()  
{  
    int i,n,temp;  
    while(EOF!=scanf("%d",&n) && 0!=n){  
        memset(rec,-1,sizeof(rec));  
        for(i=1;i<=n;i++){  
            scanf("%d",&temp);  
            if(-1 ==rec[temp].data) { rec[temp].data=temp; rec[temp].index=i; }  
            else if(rec[temp].data > -1 && 1 == i - rec[temp].index) rec[temp].index=i;  
            else { rec[i].data=temp; rec[i].index=i; }  
        }  
        qsort(rec,Max_N,sizeof(rec[0]),cmp);  
        for(i=0;i<Max_N;i++){ if(-1!=rec[i].index) printf("%d ",rec[i].data); }  
        printf("$\n");  
    }  
    return 0;  
}  
