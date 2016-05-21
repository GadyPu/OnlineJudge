#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#define N 1000+2  
char Str[N];  
char str[N * 3] = { 0 };  
void Look_and_Say(char *S)  
{  
    int i, j, k, p, count;  
    int len = strlen(S);  
    k = 0;  
    for (i = 0; i < len; i++)  
    {  
        count = 0;  
        for (j = i; j < len; j++)  
        {  
            if (S[i] == S[j])  
            {  
                count++;  
            }  
            else  
            {  
                if (count>1)  
                    i += count - 1;  
                break;  
            }  
        }  
        if (count >= 10)  
        {  
            char temp[10] = { 0 };  
            sprintf(temp, "%d", count);  
            for (p = 0; p < strlen(temp); p++)  
            {  
                str[k++] = temp[p];  
            }  
            str[k++] = S[i];  
        }  
        else  
        {  
            str[k++] = count + '0';  
            str[k++] = S[i];  
        }  
        if (j == len)  
        {  
            i = len;  
        }  
    }  
    str[k] = '\0';  
    printf("%s\n", str);  
}  
  
int main()  
{  
    int m;  
    scanf("%d\n", &m);  
    while (m--)  
    {  
        gets(Str);  
        Look_and_Say(Str);  
    }  
    return 0;  
}  
