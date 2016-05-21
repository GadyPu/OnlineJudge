#include<stdio.h>  
#include<string.h>  
#include<stdlib.h>  
int buf[10] = { 0 };  
void solve(int n)  
{  
    if ( 0 == n || 1 == n)  
    {  
        if (0 == n)  
            printf("%d\n", 10);  
        else  
            printf("%d\n", 1);  
        return;  
    }  
    int i = 9, j;  
    memset(buf, 0, sizeof(buf));  
    while (i > 1)  
    {  
        if (0 == n % i)  
        {  
            buf[i]++;  
            n /= i;  
        }  
        else  
            i--;  
    }  
    if (n != 1)  
    {  
        printf("-1\n");  
        return;  
    }  
    for (i = 2; i < 10; i++)  
    {  
        if (buf[i])  
        {  
            for (j = 0; j < buf[i]; j++)  
                printf("%d", i);  
        }  
    }  
    printf("\n");  
}  
int main()  
{  
    int n;  
    while (EOF != scanf("%d", &n))  
        solve(n);  
    return 0;  
}  
