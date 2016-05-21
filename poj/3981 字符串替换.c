#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#define N 1000 + 2  
typedef char State[15];  
typedef struct node  
{  
    State word;  
    struct node *pNext;  
}Node;  
char buf[N];  
Node *AddNewNode(char* word)  
{  
    Node *NewNode = (Node *)malloc(sizeof(Node));  
    strcpy(NewNode->word,word);  
    NewNode->pNext=NULL;  
    return NewNode;  
}  
void CreatelinkList(Node **pHead,char *word)  
{  
    if(*pHead==NULL)  
        *pHead=AddNewNode(word);  
    else  
    {  
        Node *p=*pHead;  
        while(p->pNext!=NULL) p=p->pNext;  
        p->pNext=AddNewNode(word);  
    }  
}  
void PrintList(Node *pHead)  
{  
    Node *p=pHead;  
    printf("%s",p->word);  
    p=p->pNext;  
    while(p!=NULL)  
    {  
        printf(" %s",p->word);  
        p=p->pNext;  
    }  
    printf("\n");  
}  
void rec(Node **pHead)  
{  
    buf[strlen(buf)]=' ';  
    buf[strlen(buf)]='\0';  
    char *p=buf,*p1=buf;  
    State temp;  
    while(*p!='\0')  
    {  
        int i=0,n=0;  
        p1=strchr(p,' ');  
        if(p1!=NULL)  
        {  
            n = p1 - p;  
            while(i<n) temp[i++]=*p++;  
            temp[i]='\0';  
            if(0 == strcmp(temp,"you"))  
                CreatelinkList(pHead,"we");  
            else  
                CreatelinkList(pHead,temp);  
            p=++p1;  
        }  
        else  
            break;  
    }  
}  
int main()  
{  
    Node *Head;  
    while(gets(buf))  
    {  
        Head=NULL;  
        rec(&Head);  
        PrintList(Head);  
        memset(buf,0,sizeof(buf));  
    }  
    return 0;  
}  
