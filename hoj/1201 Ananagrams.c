#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include<ctype.h>  
#include<memory.h>  
#define Max_Szie 1000 + 2  
#define Word_Size 30  
char temp[Max_Szie][Word_Size];  
typedef struct node  
{  
    char word[Word_Size];  
    int index;  
    int flag;  
}table;  
table WordTable[Max_Szie], tp[Max_Szie];  
int index[Max_Szie];  
int cmp_char(const void *a, const void *b)  
{  
    return *(char *)a - *(char *)b;  
}  
int cmp_string(const void *a, const void *b)  
{  
    return strcmp((char *)a, (char *)b);  
}  
void solve(int count)  
{  
    int i, j, k;  
    memset(index, 0, sizeof(index));  
    memcpy(tp, WordTable, sizeof(WordTable));  
    for (i = 0; i < count; i++)  
    {  
        int len = strlen(tp[i].word);  
        for (j = 0; j < len; j++)  
            tp[i].word[j] = tolower(tp[i].word[j]);  
        qsort(tp[i].word, len, sizeof(tp[i].word[0]), cmp_char);  
    }  
    for (i = 0; i < count; i++)  
    {  
        for (j = 0; j < count; j++)  
        {  
            if (i != j && 0 == strcmp(tp[i].word, tp[j].word))  
                tp[i].flag = 1;  
        }  
    }  
    k = 0;  
    for (i = 0; i < count; i++)  
    {  
        if (!tp[i].flag)  
            index[k++] = tp[i].index;  
    }  
    for (i = 0; i < count; i++)  
    {  
        for (j = 0; j < k; j++)  
        {  
            if (index[j] == WordTable[i].index)  
                strcpy(temp[j], WordTable[i].word);  
        }  
    }  
    qsort(temp, k, sizeof(temp[0]), cmp_string);  
    for (j = 0; j < k; j++)  
        printf("%s\n", temp[j]);  
}  
int main()  
{  
    int n = 0;  
    memset(WordTable, 0, sizeof(WordTable));  
    char buf[Word_Size];  
    while (1 == scanf("%s", buf))  
    {  
        if (0 == strcmp(buf, "#"))  
            break;  
        int i = n;  
        strcpy(WordTable[i].word, buf);  
        WordTable[i].index = i;  
        n++;  
    }  
    solve(n);  
    return 0;  
}
