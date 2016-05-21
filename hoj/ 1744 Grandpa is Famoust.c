#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#define Size 250100  
int data[Size] = { 0 };  
int buf[Size] = { 0 };  
typedef struct menber  
{  
    int count;  
    int score;  
    struct menber *pNext;  
}Node, *pNode;  
int cmp(const void *a, const void *b)  
{  
    return *(int *)a - *(int *)b;  
}  
int cmp1(const void *a, const void *b)  
{  
    if (*(int *)a == *(int *)b)  
        return 0;  
    return *(int *)a > *(int *)b ? -1 : 1;  
}  
pNode Add_New_Node(int score)  
{  
    pNode NewNode = (pNode)malloc(sizeof(Node));  
    NewNode->score = score;  
    NewNode->count = 1;  
    NewNode->pNext = NULL;  
    return NewNode;  
}  
void Create_List(pNode *pHead, int score)  
{  
    if (*pHead == NULL)  
    {  
        *pHead = Add_New_Node(score);  
    }  
    else  
    {  
        int flag = 1;  
        pNode p = *pHead, p1 = NULL;  
        while (p != NULL)  
        {  
            p1 = p;  
            if (p->score == score)  
            {  
                p->count++;  
                flag = 0;  
            }  
            p = p->pNext;  
        }  
        if (flag)  
            p1->pNext = Add_New_Node(score);  
    }  
}  
void Result(pNode pHead)  
{  
    pNode p = pHead; int j = 0;  
    memset(buf, 0, sizeof(buf));  
    while (p != NULL)  
    {  
        buf[j++] = p->count;  
        p = p->pNext;  
    }  
    if (1 == j)  
    {  
        printf("%d\n", pHead->score);  
    }  
    else  
    {  
        qsort(buf, j, sizeof(buf[0]), cmp1);  
        p = pHead;  
        while (p != NULL)  
        {  
            if (p->count == buf[1])  
                printf("%d ", p->score);  
            p = p->pNext;  
        }  
        printf("\n");  
    }  
}  
void FreeAll(pNode *pHead)  
{  
    pNode p1,p = *pHead;  
    p1 = p->pNext;  
    while (p1!= NULL)  
    {  
        p = p1;  
        p1 = p1->pNext;  
        free(p);  
    }  
    free(*pHead);  
}  
int main()  
{  
    int i, j, n, m;  
    while (scanf("%d %d", &n, &m) != EOF && 0 != n && 0 != m)  
    {  
        int k = 0;  
        pNode Head = NULL;  
        memset(data, 0, sizeof(data));  
        for (i = 0; i < n; i++)  
        {  
            for (j = 0; j < m; j++)  
                scanf("%d", &data[k++]);  
        }  
        qsort(data, n * m, sizeof(data[0]), cmp);  
        for (i = 0; i < n * m; i++)  
        {  
            Create_List(&Head, data[i]);  
        }  
        Result(Head);  
        FreeAll(&Head);  
    }  
    return 0;  
}  
