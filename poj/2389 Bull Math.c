#include<stdio.h>  
#include<string.h>  
#define Max_N 100  
int res[Max_N];  
char rev1[Max_N], rev2[Max_N];  
void reversal(char *src){  
    int i, j = strlen(src) - 1;  
    for (i = 0; i < j; i++, j--){  
        char t = src[i];  
        src[i] = src[j];  
        src[j] = t;  
    }  
}  
void calc(){  
    memset(res, 0, sizeof(res));  
    int i, j, n = strlen(rev1), m = strlen(rev2);  
    reversal(rev1), reversal(rev2);  
    for (i = 0; i < m; i++){  
        for (j = 0; j < n; j++){  
            res[i + j] += (rev2[i]-'0') * (rev1[j]-'0');  
        }  
    }  
    for (i = 0; i < Max_N - 1; i++){  
        if (res[i] > 9){  
            res[i + 1] += res[i] / 10;  
            res[i] %= 10;  
        }  
    }  
    j = Max_N - 1;  
    while (!res[j]) j--;  
    for (; j >= 0; j--) printf("%d", res[j]);  
}  
int main(){  
#ifdef LOCAL  
    freopen("in.txt", "r", stdin);  
    freopen("out.txt", "w+", stdout);  
#endif  
    scanf("%s %s", rev1, rev2);  
    calc();  
    return 0;  
}  
