#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
typedef char State[16];  
typedef struct node  
{  
    State name;  
    struct node *pNext;  
}Node,*pNode;  
pNode AddNewNode(char *name)  
{  
    pNode NewNode=(pNode)malloc(sizeof(Node));  
    strcpy(NewNode->name,name);  
    NewNode->pNext=NULL;  
    return NewNode;  
}  
void Init(pNode *pHead,char *name)  
{  
    if(*pHead==NULL)  
        *pHead=AddNewNode(name);  
    else  
    {  
        pNode p=*pHead;  
        while(p->pNext!=NULL) p=p->pNext;  
        p->pNext=AddNewNode(name);  
    }  
}  
void solve(pNode pHead,int w,int s)  
{  
    int i,count=1;  
    pNode p=pHead,start=pHead;  
    while(p->pNext!=NULL) p=p->pNext;  
    p->pNext=pHead;  
    while(count++ < w) start=start->pNext;  
    p=start;  
    if(1 == s)  
    {  
        printf("%s\n",start->name);  
        p=start->pNext;  
        start->pNext=NULL;  
        while(p->pNext!=NULL)  
        {  
            printf("%s\n",p->name);  
            p=p->pNext;  
        }  
        return;  
    }  
    while(p->pNext!=p)  
    {  
        pNode p1=NULL;  
        for(i=1;i < s - 1;i++)  
            p=p->pNext;  
        p1=p->pNext;  
        p->pNext=p1->pNext;  
        p=p1->pNext;  
        printf("%s\n",p1->name);  
        free(p1);  
    }  
    printf("%s\n",p->name);  
}  
int main()  
{  
    #ifdef LOCAL  
    freopen("input.txt","r",stdin);  
    #endif  
    int t=0,w=0,s=0;  
    State buf;  
    pNode Head=NULL;  
    scanf("%d",&t);  
    while(t--)  
    {  
        scanf("%s",buf);  
        Init(&Head,buf);  
    }  
    scanf("%d,%d",&w,&s);  
    solve(Head,w,s);  
    return 0;  
}  
