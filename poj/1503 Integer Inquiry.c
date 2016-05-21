#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#define Max_N 200  
char rev[Max_N];  
int _a[Max_N], res[Max_N];  
void reversal(char *src){  
    int i, j = strlen(src) - 1;  
    for (i = 0; i < j; i++, j--){  
        char t = src[i];  
        src[i] = src[j];  
        src[j] = t;  
    }  
}  
void solve(char *src, int flag){  
    int i, n = strlen(src);  
    if (!flag){  
        memset(res, 0, sizeof(res));  
        for (i = 0; i < n; i++) res[i] = src[i] - '0';  
    } else if (1 == flag) {  
        memset(_a, 0, sizeof(_a));  
        for (i = 0; i < n; i++) _a[i] = src[i] - '0';  
        for (i = 0; i < Max_N; i++) res[i] += _a[i];  
        for (i = 0; i < Max_N - 1; i++){  
            if (res[i] > 9){  
                res[i + 1] += res[i] / 10;  
                res[i] %= 10;  
            }  
        }  
    } else {  
        i = Max_N - 1;  
        while (!res[i]) i--;  
        for (; i >= 0; i--) printf("%d", res[i]);  
    }  
}  
int main(){  
#ifdef LOCAL  
    freopen("in.txt", "r", stdin);  
    freopen("out.txt", "w+", stdout);  
#endif  
    int flag = 0;  
    while (~scanf("%s", rev) && strcmp(rev, "0")!=0){  
        reversal(rev);  
        solve(rev, flag);  
        if (0 == flag) flag = 1;  
    }  
    flag = 2;  
    solve(rev, flag);  
    return 0;  
} 
