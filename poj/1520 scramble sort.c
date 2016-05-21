#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#define Max_Size 102  
int index = 0;  
char buf[Max_Size] = { 0 };  
typedef struct node  
{  
    int index;  
    char data[20];  
    struct node *pNext;  
}Node,*pNode;  
pNode pS[Max_Size], pN[Max_Size];  
int pSt = 0, pNt = 0;  
pNode Add_New_Node(int index,char *data)  
{  
    pNode NewNode = (pNode)malloc(sizeof(Node));  
    NewNode->index = index;  
    strcpy(NewNode->data, data);  
    NewNode->pNext = NULL;  
    return NewNode;  
}  
void ListInertNum(pNode *pHead, int index, char *data)  
{  
    if (*pHead == NULL)  
    {  
        *pHead = Add_New_Node(index, data);  
        pN[pNt++] = *pHead;  
    }  
    else  
    {  
        pNode p = *pHead;  
        while (p->pNext != NULL)  
        {  
            p = p->pNext;  
        }  
        p->pNext = pN[pNt++] = Add_New_Node(index, data);  
    }  
}  
void ListInertStr(pNode *pHead, int index, char *data)  
{  
    if (*pHead == NULL)  
    {  
        *pHead = Add_New_Node(index, data);  
        pS[pSt++] = *pHead;  
    }  
    else  
    {  
        pNode p = *pHead;  
        while (p->pNext != NULL)  
        {  
            p = p->pNext;  
        }  
        p->pNext = pS[pSt++] = Add_New_Node(index, data);  
    }  
}  
int MyStrcmp(const char *_str1, const char *_str2)  
{  
    while (*_str1!= '\0' && *_str2!= '\0')  
    {  
        char c1 = *_str1;  
        char c2 = *_str2;  
        if (c1 >= 'A' && c1 <= 'Z')  
        {  
            c1 += 'a' - 'A';  
        }  
        if (c2 >= 'A' && c2 <= 'Z')  
        {  
            c2 += 'a' - 'A';  
        }  
        if (c1 != c2)  
            return c1 > c2 ? 1 : -1;  
        _str1++, _str2++;  
    }  
    if (*_str1 == '\0' && *_str2 == '\0')  
        return 0;  
    return *_str1 > *_str2 ? 1 : -1;  
}  
void SortListByStr(pNode pHead)  
{  
    int i, j;  
    for (i = 0; i < pSt - 1; i++)  
    {  
        for (j = i + 1; j < pSt; j++)  
        {  
            if (-1 == MyStrcmp(pS[j]->data, pS[i]->data))  
            {  
                pNode temp = pS[i];  
                pS[i] = pS[j];  
                pS[j] = temp;  
  
                int t = pS[i]->index;  
                pS[i]->index = pS[j]->index;  
                pS[j]->index = t;  
            }  
        }  
    }  
}  
void SortListByNum(pNode pHead)  
{  
    int i, j;  
    for (i = 0; i < pNt - 1; i++)  
    {  
        for (j = i + 1; j < pNt; j++)  
        {  
            if (atoi(pN[i]->data) > atoi(pN[j]->data))  
            {  
                pNode temp = pN[i];  
                pN[i] = pN[j];  
                pN[j] = temp;  
  
                int t = pN[i]->index;  
                pN[i]->index = pN[j]->index;  
                pN[j]->index = t;  
            }  
        }  
    }  
}  
char *GetInfo(char *dest,char *str)  
{  
    int i, n;  
    if (strchr(str, ',')!= NULL)  
        n = strchr(str, ',') - str;  
    else  
        n = strchr(str, '.') - str;  
    memset(dest, 0, (strlen(dest)+1) * sizeof(char));  
    for (i = 0; i < n; i++)  
        dest[i] = *str++;  
    dest[i] = '\0';  
    return str;  
}  
void solve(char *source,pNode *pStr,pNode *pNum)  
{  
    char *p = source, temp[30] = { 0 };  
    while (*p != '.')  
    {  
        if ((*p >= '0' && *p <= '9') || *p == '-')  
        {  
            p = GetInfo(temp, p);  
            ListInertNum(&(*pNum), index++, temp);  
        }  
        else if ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'z'))  
        {  
            p = GetInfo(temp, p);  
            ListInertStr(&(*pStr), index++, temp);  
        }  
        else if (*p == ',' || *p == ' ')  
        {  
            p++;  
        }  
    }  
}  
void PrintResult(pNode pStr,pNode pNum)  
{  
    int i, j, k;  
    SortListByStr(pStr), SortListByNum(pNum);  
    pNode p = (pStr == NULL ? pNum : pStr);  
    while (p->pNext != NULL)  
        p = p->pNext;  
    p->pNext = (pStr == NULL ? pStr : pNum);  
    k = 0;  
    for (i = 0; i < index; i++)  
    {  
        p = (pStr == NULL ? pNum : pStr);  
        while (p != NULL)  
        {  
            if (p->index == i)  
            {  
                for (j = 0; j < strlen(p->data); j++)  
                {  
                    buf[k++] = p->data[j];  
                }  
                if (i < index - 1)  
                {  
                    buf[k++] = ',';  
                    buf[k++] = ' ';  
                }  
                else  
                    buf[k++] = '.';  
            }  
            p = p->pNext;  
        }  
    }  
    buf[k] = '\0';  
    printf("%s\n", buf);  
}  
void FreeList(pNode *pStr, pNode *pNum)  
{  
    pNode p = (*pStr == NULL ? *pNum :* pStr), p1 = NULL;  
    p1 = p->pNext;  
    while (p1 != NULL)  
    {  
        p = p1;  
        p1 = p1->pNext;  
        free(p);  
    }  
    free(*pStr == NULL ? *pNum : *pStr);  
}  
int main()  
{  
    while (1)  
    {  
        index = 0 ,pSt = 0 ,pNt = 0;  
        gets(buf);  
        if (0 == strcmp(buf, "."))  
            break;  
        pNode pStr = NULL, pNum = NULL;  
        solve(buf, &pStr, &pNum);  
        PrintResult(pStr, pNum);  
        FreeList(&pStr,&pNum);  
    }  
    return 0;  
}  
