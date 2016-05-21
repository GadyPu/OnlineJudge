#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#define DataType int  
char buffer[20];  
char *Table[] = { "add", "query", "delete" };  
typedef struct Queue  
{  
    DataType data;  
    int Priroity;  
    struct Queue *pNext;  
}Queue, *Que;  
Que CreateNode(DataType data, int Pri)  
{  
    Que NewNode = (Que)malloc(sizeof(Queue));  
    NewNode->data = data;  
    NewNode->Priroity = Pri;  
    NewNode->pNext = NULL;  
    return NewNode;  
}  
void InsertEnQueue(Que *Qhead, DataType data, int Pri)  
{  
    Que NewNode = CreateNode(data, Pri);  
    if (*Qhead == NULL)  
    {  
        *Qhead = NewNode;  
    }  
    else  
    {  
        if (NewNode->Priroity < (*Qhead)->Priroity)  
        {  
            Que temp = *Qhead;  
            *Qhead = NewNode;  
            (*Qhead)->pNext = temp;  
        }  
        else  
        {  
            Que p = *Qhead;;  
            while (p->pNext != NULL)  
            {  
                p = p->pNext;  
            }  
            if (NewNode->Priroity >= p->Priroity)  
            {  
                p->pNext = NewNode;  
            }  
            else  
            {  
                Que p1, p2;  
                p1 = p2 = NULL;  
                p1 = *Qhead;  
                while (p1->pNext != NULL)  
                {  
                    p2 = p1->pNext;  
                    if (p1->Priroity <= NewNode->Priroity && p2->Priroity >= NewNode->Priroity)  
                    {  
                        p1->pNext = NewNode;  
                        NewNode->pNext = p2;  
                        break;  
                    }  
                    p1 = p1->pNext;  
                }  
            }  
  
        }  
    }  
}  
void DeQueue(Que *Qhead)  
{  
    if (*Qhead == NULL)  
    {  
        return;  
    }  
    else  
    {  
        Que p = *Qhead;  
        *Qhead = p->pNext;  
        free(p);  
    }  
}  
int ReturnNum(char *str)  
{  
    char temp[20] = { 0 };  
    int j, i = strchr(str, ' ') - str;  
    i++, j = 0;  
    for (; i < strlen(str); i++)  
    {  
        temp[j++] = str[i];  
    }  
    temp[j] = '\0';  
    return atoi(temp);  
}  
int main()  
{  
    Que Head = NULL;  
    int i, m, temp;  
    scanf("%d\n", &m);  
    while (m--)  
    {  
        fgets(buffer, sizeof(buffer), stdin);  
        for (i = 0; i < 3; i++)  
        {  
            if (strstr(buffer, Table[i]))  
            {  
                switch (i)  
                {  
                case 0:  
                    temp = ReturnNum(buffer);  
                    InsertEnQueue(&Head, temp, temp);  
                    break;  
                case 1:  
                    if (Head == NULL)  
                        break;  
                    else  
                        printf("%d\n", Head->data);  
                    break;  
                case 2:  
                    DeQueue(&Head);  
                    break;  
                }  
            }  
        }  
    }  
    return 0;  
}  
