#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include<math.h>  
#define Max_Size 128  
char buf1[20], buf2[20];  
int res[Max_Size];  
void calc(int n, int m, int cur)  
{  
    int i, j;  
    memset(res, 0, sizeof(res));  
    res[0] = 1;  
    for (i = 1; i <= n; i++)  
    {  
        int v = 0;  
        for (j = 0; j < Max_Size; j++)  
        {  
            int temp = res[j] * m + v;  
            res[j] = temp % 10;  
            v = temp / 10;  
        }  
    }  
    int k =(int)(n * log10(m)) + 1;  
    int count = 0;  
    if (cur > k)  
    {  
        printf(".");  
        for (j = 1; j <= cur - k; j++)  
            printf("0");  
        j = Max_Size - 1;  
        while (!res[j])  
            j--;  
        for (; j >= 0; j--)  
            printf("%d", res[j]);  
    }  
    else  
    {  
        j = Max_Size - 1;  
        while (!res[j])  
            j--;  
        for (; j >= 0; j--)  
        {  
            if (count == k-cur)  
                printf(".");  
            printf("%d", res[j]);  
            count++;  
        }  
    }  
    printf("\n");  
}  
void solve()  
{  
    int i, k, flag = 1, m = 0, n = 0, count = 0;  
    if (strchr(buf1, '.') != NULL)  
    {  
        k = strchr(buf1, '.') - buf1;  
        i = strlen(buf1) - 1;  
        while ('0' == buf1[i])  
            i--;  
        count = i - k;  
    }  
    else  
        flag = 0;  
    int c = strlen(buf1) - 1;  
    while (0!=flag && '0' == buf1[c])  
        c--;  
    for (i = 0; i <= c; i++)  
    {  
        if ('.' == buf1[i])  
            continue;  
        m = m * 10 + buf1[i] - '0';  
    }  
    n = atoi(buf2);  
    calc(n, m, count * n);  
}  
int main()  
{  
    while (EOF != scanf("%s %s", buf1, buf2))  
        solve();  
    return 0;  
}  
