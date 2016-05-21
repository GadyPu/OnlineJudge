#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
char buf[40602] = { 0 };  
void Calc(int n)  
{  
    int i, j, k = 0, len = strlen(buf);  
    char  **Arr = (char **)malloc(sizeof(char *) * ( len / n ));  
    for (i = 0; i < len / n; i++)  
        Arr[i] = (char *)malloc(sizeof(char) * n);  
    for (i = 0; i < len / n; i++)  
    {  
        for (j = 0; j < n; j++)  
        {  
            if (1 == i % 2)  
            {  
                Arr[i][n - j - 1] = buf[k++];  
            }  
            else  
                Arr[i][j] = buf[k++];  
        }  
    }  
    char *temp = (char *)malloc(sizeof(char)*(len + 2));  
    k = 0;    
    for (j = 0; j < n; j++)  
    {  
        for (i = 0; i < len / n; i++)  
        {  
            temp[k++] = Arr[i][j];  
        }  
    }  
    temp[k] = '\0';  
    printf("%s\n", temp);  
    for (i = 0; i < len / n; i++)  
        free(Arr[i]);  
    free(Arr);  
    free(temp);  
}  
int main()  
{  
    int n;  
    while (scanf("%d", &n) != EOF && 0 != n)  
    {  
        scanf("%s", buf);  
        Calc(n);  
    }  
    return 0;  
}  
