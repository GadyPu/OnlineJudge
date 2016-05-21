#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#define Max_N 100002  
int heap[Max_N],sz;  
void push(int x){  
    int i=sz++;  
    while(i>0){  
        int p=(i-1)>>1;  
        if(heap[p]<=x) break;  
        heap[i]=heap[p];  
        i=p;  
    }  
    heap[i]=x;  
}  
int pop(){  
    int x,i=0,ret=heap[0];  
    x=heap[--sz];  
    while((i<<1)+1<sz){  
        int a=(i<<1)+1,b=(i<<1)+2;  
        if(b<sz && heap[a]>heap[b]) a=b;  
        if(heap[a]>=x) break;  
        heap[i]=heap[a];  
        i=a;  
    }  
    heap[i]=x;  
    return ret;  
}  
int main()  
{  
    int i,n,ret;  
    while(EOF!=scanf("%d",&n)){  
        sz=0;  
        for(i=0;i<n;i++){  
            scanf("%d",&ret);  
            push(ret);  
        }  
        for(i=0; i < n>>1;i++) pop();  
        printf("%d\n",pop());  
    }  
    return 0;  
}  
